
#include "MySlate.h"
#include "PkProcess.h"

#include "./PkMsg.h"
#include "../../MyChar.h"
#include "../Filter/AbsFilter.h"
#include "../Function/Funcs/AbsPkEvent.h"
#include "../Template/SkillTemplate.h"
#include "../Buff/BuffMgr.h"
#include "./FightData.h"
#include "./PkMsg.h"
#include "../SkillMgr.h"
#include "../../Object/ObjMgr.h"

UDamageInfo::UDamageInfo() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UDamageInfo::~UDamageInfo()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UDamageInfo::~UDamageInfo"));
}

void UDamageInfo::BeginDestroy()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UDamageInfo::BeginDestroy"));
	Super::BeginDestroy();
}

void UDamageInfo::Reset()
{
	mTargetId = 0;
	mTarget = nullptr;
	mValue = 0.f;
	mIsDodge = false;
	mIsCrit = false;
	mIsPhyDmgImmunity = false;
	mIsMagDmgImmunity = false;
}

//-------------------------------- UPkProcess Begin
UPkProcess::UPkProcess() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UPkProcess::~UPkProcess()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkProcess::~UPkProcess"));
}

void UPkProcess::BeginDestroy()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkProcess::BeginDestroy"));
	Super::BeginDestroy();
}

void UPkProcess::Reset()
{
	mPkMsg = nullptr;
	mCallBack = nullptr;
}

void UPkProcess::Recycle()
{
	IObjInterface::Recycle();
}

void UPkProcess::SetMsg(UPkMsg* _pkMsg)
{
	mPkMsg = _pkMsg;
}

void UPkProcess::Run()
{
	UParam* currtarge = nullptr;
	
	Filter();
	const TArray<UParam*>& targets = mPkMsg->GetTargets();
	for (UParam* param : targets)
	{
		currtarge = param;
		mPkMsg->SetCurrTarget(currtarge);

		PkLogicEvns();//pk�߼����㣬֮ǰ�ķ����ѰѶ������ĵ�ֵ���,�����Ƿ����ܺͱ����ȣ����ﲻ���ټ��㣬ֱ�ӽ����߼����㼴��
		RunEndEvns(); //ÿ���ܻ��߼�buff
	}

	RunEndPk(); //�������߼�buff
	PkPrice();
	mPkMsg->ClearTargets();
}

bool UPkProcess::CheckCanPk()
{
	return false;
}

void UPkProcess::Filter()
{
	UAbsFilter* filter = nullptr;
	USkillTemplate* skillTemp = mPkMsg->GetSkillTemp();
	if (skillTemp)
	{
		filter = skillTemp->GetFilter();
	}

	if ( filter != nullptr)
	{
		filter->Filter(mPkMsg);
	}
}

void UPkProcess::RunEndEvns()
{
	const TArray<UAbsPkEvent*>& functions2 = mPkMsg->GetSkillTemp()->GetEndEvns();
	for (UAbsPkEvent* func : functions2)
	{

		//step4 - ���ж�Ŀ�꼯�е�ÿ�������func
		func->RunEndEvns(mPkMsg);
	}
}

//TODO: ����ÿ����λ�ĸ���ս�����ݣ����ܣ��������˺��ȣ���ʱ�ȼ����˺�
void UPkProcess::PkLogicEvns()
{
	float val = USkillMgr::GetInstance()->FormulaPk(mPkMsg, EFormulaPkType::Dodge);
	mPkMsg->SetDodge(val > 0.5f ? true : false);

	val = USkillMgr::GetInstance()->FormulaPk(mPkMsg, EFormulaPkType::Damage);
	mPkMsg->SetAttackDmgValue(val, -1, false);
}

void UPkProcess::RunEndPk()
{
	//step5 - �����ͷ���pk�����¼�
	USkillTemplate* skillTemp = mPkMsg->GetSkillTemp();
	const TArray<UAbsPkEvent*> functions = skillTemp->GetEndPk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunEndPk(mPkMsg);
	}

	//UBuffMgr::GetInstance()->RunEndPkBuffs(mPkMsg->GetAttackerId(), mPkMsg);
}

//���ݼ���õ����ݣ������Ƿ񸶳�����
void UPkProcess::PkPrice()
{
	TArray<UDamageInfo*> dmgArr;

	const TArray<UParam*>& targets = mPkMsg->GetTargets();
	for (UParam* param : targets)
	{
		if (param->mDodge)
		{
			continue;
		}

		UDamageInfo* info1 = GetObjMgr()->GetObj<UDamageInfo>(GetObjMgr()->mDmgInfoCls);
		info1->mTarget = param->mTarget;
		info1->mValue = param->mDmgPhyVal;
		dmgArr.Add(info1);
	}

	mCallBack.ExecuteIfBound(dmgArr);
}

//���մ���
void UPkProcess::PkDamage(TArray<UDamageInfo*> _dmgVec)
{

}
