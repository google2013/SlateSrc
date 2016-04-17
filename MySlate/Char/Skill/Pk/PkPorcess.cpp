// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkPorcess.h"

#include "PkMsg.h"
#include "char/MyChar.h"
#include "../Filter/AbsFilter.h"
#include "../Template/SkillTemplate.h"

// Sets default values
UPkPorcess::UPkPorcess() : Super()
{
	//UE_LOG(SkillDataMgrLogger, Warning, TEXT("--- USkillDataMgr::Tick:%f"), 0.2f);
}

UPkPorcess::~UPkPorcess()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkPorcess::~UPkPorcess"));
	if (mPkMsg != nullptr)
	{
		mPkMsg->ExeNullDlg(); // �����߲����������ͷţ�USkillFunction�оͲ��ͷ��ˣ�����ָ��Ϊnull 
		mPkMsg->RemoveFromRoot();
	}
}

void UPkPorcess::SetMsg(UPkMsg* _pkMsg)
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
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
		//targetActor = targets[i].
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

void UPkPorcess::RunBeforePk()
{
}

void UPkPorcess::RunBeforeSkill()
{
}

void UPkPorcess::PkLogic()
{
}

void UPkPorcess::RunEndSkill()
{

}

void UPkPorcess::RunEndPk()
{

}

void UPkPorcess::PkPrice()
{

}
