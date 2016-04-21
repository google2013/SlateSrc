// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CircleFilter.h"

#include "../Pk/PkMsg.h"
#include "Char/MyChar.h"

UCircleFilter::UCircleFilter() : Super()
{

}

UCircleFilter::~UCircleFilter()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- UCircleFilter::~UCircleFilter"));
}
 
void UCircleFilter::BeginDestroy()
{

	UE_LOG(FilterLogger, Warning, TEXT("--- UCircleFilter::BeginDestroy"));
	Super::BeginDestroy();
}

void UCircleFilter::Filter(UPkMsg* msg)
{
	//SphereOverlapActors_NEW
	int32 targetId = msg->GetTargetId();
	AMyChar* target = targetId > 0 ? UCharMgr::GetInstance()->GetChar(targetId) : nullptr;
	FVector targetLoc = FVector(0.f, 0.f, 0.f);
	if (target != nullptr) //����Ŀ�꣬�п��ܷ�����Ŀ������������ȥChar���������ñȽϿ���
	{
		targetLoc = target->GetActorLocation();
	}
	else //�����ص�,���� "����Ŀ��"�ĵص�
	{
		targetLoc = msg->GetTargetLoc();
	}

	if (targetLoc.SizeSquared() > 0.f)
	{
		TArray<AMyChar*> ignoreChars;
		ETeam ignoreTeam = UCharMgr::GetInstance()->GetIgnoreTeam(msg->GetAttackerTeam(), mSelectType);
		UCharMgr::GetInstance()->GetIgnoreCharsByTeam(ignoreTeam, ignoreChars);

		TArray<AActor*> ignoreActors = UCharMgr::GetInstance()->ConvertCharsToActors(ignoreChars);

		TArray<FHitResult> destChars;
		//���� �Լ������Լ��ϣ��򵥵���ײ���
		/*TArray<TEnumAsByte<EObjectTypeQuery>>  destObjectTypes;
		TArray<AActor*> destActors;
		UKismetSystemLibrary::SphereOverlapActors_NEW(GWorld, targetLoc, mRadius, destObjectTypes, AMyChar::StaticClass(), ignoreChars, destActors);*/
		UKismetSystemLibrary::SphereTraceMulti_NEW(GWorld, targetLoc, targetLoc + 1.f, mRadius, TraceTypeQuery1, false, ignoreActors, EDrawDebugTrace::ForOneFrame, destChars, true);

		//��ֻĿ�꼯�ϵ�pkMsg��
		for (auto& destTarget : destChars)
		{
			//destTarget.Actor
		}
	}
	else
	{
		UE_LOG(FilterLogger, Error, TEXT("--- UCircleFilter::Filter, targetLoc.SizeSquared() == 0.f"));
	}
}

UAbsFilter* UCircleFilter::Clone()
{
	return CreateFilter(mKey);
}

void UCircleFilter::Parser(const TArray<FString>& _params)
{
	//mCenterType = -1;
	mSelectType = -1;
	mCount = -1;
	mRadius = 100;
	if (_params.Num() > 2)
	{
		//mCenterType = FCString::Atoi(*_params[0]);
		mSelectType = FCString::Atoi(*_params[0]);
		mCount = FCString::Atoi(*_params[1]);
		mRadius = FCString::Atoi(*_params[2]);
	}
	else
	{
		UE_LOG(FilterLogger, Error, TEXT("--- UCircleFilter::Parser, _params.Num() = %d"), _params.Num());
	}
}

UCircleFilter* UCircleFilter::CreateFilter(const FString& _key)
{
	UCircleFilter* circleFilter = NewObject<UCircleFilter>(UCircleFilter::StaticClass());
	circleFilter->SetKey(_key);
	return circleFilter;
}
