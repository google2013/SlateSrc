// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkProcess.h"

#include "PkMsg.h"
#include "char/MyChar.h"
#include "../Filter/AbsFilter.h"
#include "../Function/Funcs/AbsPkEvent.h"
#include "../Template/SkillTemplate.h"
#include "../Buff/BuffMgr.h"

UPkProcess::UPkProcess() : Super()
{

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

void UPkProcess::SetMsg(UPkMsg* _pkMsg)
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg->ConditionalBeginDestroy();
	}
	mPkMsg = _pkMsg;
	mPkMsg->AddToRoot();
}

void UPkProcess::Run()
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
	//step5 - ���ж�Ŀ�꼯�е�ÿ�������func��pk�߼���ɺ����߼�������Ѫ��������
	const TArray<UAbsPkEvent*>& functions2 = mPkMsg->GetSkillTemp()->GetEndEvns();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunEndEvns(mPkMsg);
	}
}

void UPkProcess::PkLogic()
{
	//ս���˺�ֵ
	float dmg = mPkMsg->GetAttackerData()->GetAttackPhy();
	mPkMsg->SetAttackDmgValue(dmg, -1, false);
}

void UPkProcess::RunEndPk()
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

void UPkProcess::PkPrice()
{
	TArray<FDamageInfo> dmgArr;

	mCallBack.ExecuteIfBound(dmgArr);
}
