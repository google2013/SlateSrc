// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkPorcess.h"

#include "PkMsg.h"
#include "char/MyChar.h"
#include "../Filter/AbsFilter.h"
#include "../Function/Funcs/AbsPkEvent.h"
#include "../Template/SkillTemplate.h"
#include "../Buff/BuffMgr.h"

UPkPorcess::UPkPorcess() : Super()
{

}

UPkPorcess::~UPkPorcess()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkPorcess::~UPkPorcess"));
}

void UPkPorcess::BeginDestroy()
{
	if (mPkMsg != nullptr)
	{
		//mPkMsg->ExeNullDlg(); // �����߲����������ͷţ�USkillFunction�оͲ��ͷ��ˣ�����ָ��Ϊnull 
		mPkMsg->RemoveFromRoot();
		mPkMsg->ConditionalBeginDestroy();
		mPkMsg = nullptr;
	}

	UE_LOG(PkLogger, Warning, TEXT("--- UPkPorcess::BeginDestroy"));
	Super::BeginDestroy();
}

void UPkPorcess::SetMsg(UPkMsg* _pkMsg)
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg->ConditionalBeginDestroy();
	}
	mPkMsg = _pkMsg;
	mPkMsg->AddToRoot();
}

void UPkPorcess::Run()
{
	AMyChar* targetActor = nullptr;
	
	Filter();
	const TArray<UParam*>& targets = mPkMsg->GetTargets();
	for (int32 i = 0; i < targets.Num(); ++i)
	{
		targetActor = targets[i]->mTarget;

		RunEndEvns();
	}

	RunEndPk(); //�������߼�buff
	PkPrice();
}

bool UPkPorcess::CheckCanPk()
{
	return false;
}

void UPkPorcess::Filter()
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

void UPkPorcess::RunEndEvns()
{
	//step5 - ���ж�Ŀ�꼯�е�ÿ�������func��pk�߼���ɺ����߼�������Ѫ��������
	const TArray<UAbsPkEvent*>& functions2 = mPkMsg->GetSkillTemp()->GetEndEvns();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunEndEvns(mPkMsg);
	}
}

void UPkPorcess::PkLogic()
{
	//ս���˺�ֵ
	float dmg = mPkMsg->GetAttackerData()->GetAttackPhy();
	mPkMsg->SetAttackDmgValue(dmg, -1, false);
}

void UPkPorcess::RunEndPk()
{
	//step4 - ���ж�Ŀ�꼯�е�ÿ�������func
	USkillTemplate* skillTemp = mPkMsg->GetSkillTemp();
	const TArray<UAbsPkEvent*> functions = skillTemp->GetEndPk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunEndPk(mPkMsg);
	}

	UBuffMgr::GetInstance()->RunEndPkBuffs(mPkMsg->GetAttackerId(), mPkMsg);
}

void UPkPorcess::PkPrice()
{
	TArray<FDamageInfo> dmgArr;

	mCallBack.ExecuteIfBound(dmgArr);
}
