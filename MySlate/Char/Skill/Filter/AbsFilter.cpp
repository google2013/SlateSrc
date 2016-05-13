
#include "MySlate.h"
#include "AbsFilter.h"

#include "../../BpFuncLib/GolbalFunc.h"
#include "../../MyChar.h"
#include "../../Comp/MyCharDataComp.h"
#include "../../CharMgr.h"
#include "../Pk/PkMsg.h"

UAbsFilter::UAbsFilter() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UAbsFilter::~UAbsFilter()
{

}

void UAbsFilter::BeginDestroy()
{

	Super::BeginDestroy();
}

void UAbsFilter::Reset()
{
	mKey = "";
	mSelectType = ESelectType::Enemy; //Ĭ�ϵз�
	mCount = -1; //��������
}

void UAbsFilter::Filter(UPkMsg* _msg, EFilterType _filterType /* = EFilterType::Locked */, float _radius /* = 0.f */, const FVector& _boxSize /* = FVector::ZeroVector */)
{
	mDestChars.Empty();
	if (_filterType == EFilterType::Locked)
	{
		return;
	}

	AMyChar* target = _msg->GetTarget();
	FVector targetLoc = FVector::ZeroVector;
	if (target != nullptr) 
	{
		targetLoc = target->GetActorLocation();
	}
	else //�����ص�,���� "����Ŀ��"�ĵص�
	{
		targetLoc = _msg->GetTargetLoc();
	}

	if (targetLoc.SizeSquared() > 0.f)
	{
		//TArray<AMyChar*> ignoreChars; 
		//ETeam ignoreTeam = gGetCharMgr()->GetIgnoreTeam(_msg->GetAttackerTeam(), mSelectType);
		//gGetCharMgr()->GetIgnoreCharsByTeam(ignoreTeam, ignoreChars);

		TArray<AActor*> ignoreActors;
		//gGetCharMgr()->ConvertCharsToActors(ignoreChars, ignoreActors);

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

		ETeam dstTeam = gGetCharMgr()->GetDestTeam(_msg->GetAttackerTeam(), mSelectType);

		//Ϊ���ٶ�α�����ֱ����cast�����pkMsgĿ�꼯����
		AMyChar* tmpTarget = nullptr;
		int32 tmpTargetId = 0;
		int32 counter = mCount;
		//��ѡ�е��˶���pkMsgĿ�꼯����
		for (AActor* dstTarget : destActors)
		{
			if (mCount > 0)//����������
			{
				if (counter == 0)
				{
					break; //ѡ�������Ѿ��ﵽ
				}
			}

			tmpTarget = Cast<AMyChar>(dstTarget);
			if (tmpTarget && tmpTarget->IsAlive() && tmpTarget->GetDataComp()->GetTeamType() == dstTeam) //����ʱ����������Death, Ѫ��û��
			{

				if (target != nullptr && target == tmpTarget)
				{
					_msg->AddTarget(tmpTarget, true);// ��������actor
					UE_LOG(FilterLogger, Warning, TEXT("--- UAbsFilter::Filter, locked targetId:%d"),target->GetUuid());
				}
				else
				{
					_msg->AddTarget(tmpTarget);

				}

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
