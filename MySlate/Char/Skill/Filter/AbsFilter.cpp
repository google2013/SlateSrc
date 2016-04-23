// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsFilter.h"

#include "Char/BpFuncLib/GolbalFunc.h"
#include "Char/MyChar.h"
#include "Char/CharMgr.h"
#include "../Pk/PkMsg.h"

UAbsFilter::UAbsFilter()
{
	mKey = "";
	mSelectType = ESelectType::Enemy; //Ĭ�ϵз�
	mCount = -1; //��������
}

UAbsFilter::~UAbsFilter()
{

}

void UAbsFilter::BeginDestroy()
{

	Super::BeginDestroy();
}

void UAbsFilter::Filter(UPkMsg* _msg, EFilterType _filterType /* = EFilterType::Locked */, float _radius /* = 0.f */, const FVector& _boxSize /* = FVector::ZeroVector */)
{
	mDestChars.Empty();
	if (_filterType == EFilterType::Locked)
	{
		return;
	}

	int32 targetId = _msg->GetTargetId();
	AMyChar* target = targetId > 0 ? UCharMgr::GetInstance()->GetChar(targetId) : nullptr;
	FVector targetLoc = FVector::ZeroVector;
	if (target != nullptr) //����Ŀ�꣬�п��ܷ�����Ŀ������������ȥChar���������ñȽϿ���
	{
		targetLoc = target->GetActorLocation();
	}
	else //�����ص�,���� "����Ŀ��"�ĵص�
	{
		targetLoc = _msg->GetTargetLoc();
	}

	if (targetLoc.SizeSquared() > 0.f)
	{
		TArray<AMyChar*> ignoreChars; //�����Ŀ��Ļ�����Ŀ�꣬��Ϊ����Ŀ����Լ�����һ��
		if (target != nullptr)
		{
			ignoreChars.Add(target);
		}

		ETeam ignoreTeam = UCharMgr::GetInstance()->GetIgnoreTeam(_msg->GetAttackerTeam(), mSelectType);
		UCharMgr::GetInstance()->GetIgnoreCharsByTeam(ignoreTeam, ignoreChars);

		TArray<AActor*> ignoreActors;
		UCharMgr::GetInstance()->ConvertCharsToActors(ignoreChars, ignoreActors);

		//ignoreChars.Add(_actor);
		TArray<TEnumAsByte<EObjectTypeQuery>>  destObjectTypes; //Ŀ�����ͼ���
		destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_Pawn); //����ǿתһ�£�һһ��Ӧ��

		TArray<AActor*> destActors;
		if (_filterType == EFilterType::Circle)
		{
			UKismetSystemLibrary::SphereOverlapActors_NEW(GWorld, targetLoc, _radius, destObjectTypes, AMyChar::StaticClass(), ignoreActors, destActors);
		}
		else if (_filterType == EFilterType::Rect)
		{
			UKismetSystemLibrary::BoxOverlapActors_NEW(GWorld, targetLoc, _boxSize, destObjectTypes, AMyChar::StaticClass(), ignoreActors, destActors);
		}

		//Ϊ���ٶ�α�����ֱ����cast�����pkMsgĿ�꼯����
		AMyChar* tmpTarget = nullptr;
		int32 tmpTargetId = 0;
		int32 counter = mCount;
		//��ѡ�е��˶���pkMsgĿ�꼯����
		for (AActor* destTarget : destActors)
		{
			if (mCount > 0)//����������
			{
				if (counter == 0)
				{
					break; //ѡ�������Ѿ��ﵽ
				}
			}

			tmpTarget = Cast<AMyChar>(destTarget);
			tmpTargetId = tmpTarget != nullptr ? tmpTarget->GetUuid() : 0;
			tmpTarget = tmpTargetId > 0 ? UCharMgr::GetInstance()->GetChar(tmpTargetId) : nullptr; //��ֹ������char��ѡ��
			if (tmpTarget)
			{
				_msg->AddTarget(tmpTarget);
				mDestChars.Add(tmpTarget);
				--counter;
			}
		}
	

		//DEBUG: ����һ��ѡ�е�Ŀ�꼯���߶�
		for (AMyChar* tmpChar : mDestChars)
		{
			UGolbalFunc::DrawSegment(targetLoc, tmpChar->GetActorLocation());
		}
	}
	else
	{
		UE_LOG(FilterLogger, Error, TEXT("--- URectFilter::Filter, targetLoc.SizeSquared() == 0.f"));
	}
}

void UAbsFilter::DebugDraw(const FVector& _start, const TArray<AMyChar*>& _targets)
{
	for (AMyChar* tmp : _targets)
	{
		UGolbalFunc::DrawSegment(_start, tmp->GetActorLocation());
	}
}
