// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

#include "Template/SkillTemplate.h"
#include "Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"
#include "../Comp/MyCharDataComp.h"
#include "Function/Funcs/AbsPkEvent.h"

// Sets default values
USkillFunction::USkillFunction() : Super()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
	mBullet = nullptr;
	mAttacker = nullptr;
	mTargetId = 0;
	mTargetLoc = FVector(0.f, 0.f, 0.f);
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction:%d"), mSkillId);
	if (mPkMsg)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg = nullptr;
	}
}

void USkillFunction::Tick(float DeltaSeconds)
{

}

void USkillFunction::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = _skillTemp->mId;
	mType = _skillTemp->mSkillType;

}

void USkillFunction::UseSkill(int32 _targetId, const FVector& _targetLoc)
{
	mTargetId = _targetId;
	mTargetLoc = _targetLoc;
}



bool USkillFunction::CanAttack()
{
	AMyChar* target = mTargetId > 0 ? UCharMgr::GetInstance()->GetChar(mTargetId) : nullptr;
	if (target)
	{
		float DistSq = (target->GetActorLocation() - mAttacker->GetActorLocation()).Size();
		float atkDist = mSkillTemplate->mAttackDist;
		return atkDist > DistSq ? true : false;
	}
	return false;
}

void USkillFunction::SkillBegin()
{
	if (mPkMsg != nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mPkMsg != nullptr before"));
	}

	UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
	pkMsg->AddToRoot();

	//step1 - ���и��������Լ���buff��func
	const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforePk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunBeforePk(mPkMsg);
	}

	//step2 - ���м���ǰ��func, ����˲���ƶ�
	const TArray<UAbsPkEvent*>& functions2 =mSkillTemplate->GetBeforeSkill();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunBeforeSkill(mPkMsg);
	}
}



void USkillFunction::BulletCreate()
{
	if (mBullet != nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mBullet != nullptr before"));
	}

	if (mAttacker)
	{
		 //TODO: �����ӵ�, �󶨵������ĳ��socket��λ��
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		mBullet = GetWorld()->SpawnActor<AMyBullet>(mAttacker->BulletClass, mAttacker->GetActorLocation(), mAttacker->GetActorRotation(), SpawnInfo);
	}
}

void USkillFunction::BulletShoot()
{
	if (mBullet != nullptr)
	{
		//TODO: ���������󶨵㣬��Ŀ�����


		//TODO: ����pk��Ϣ�����Ϲ���������
		UFightData* attackerData = NewObject<UFightData>(UFightData::StaticClass());
		attackerData->AddToRoot();//��pkMsg�������������ͷ��������

		UPkMsg* pkMsg = mPkMsg;
		UFightData* dataComp = mAttacker->GetDataComp()->GetFigthData();
		dataComp->Clone(*attackerData);//�������ߵ�ս�����ݿ����� �½���ս�����ݶ�����
		pkMsg->SetAttackerData(attackerData);
		mBullet->SetPkMsg(pkMsg);

		mBullet = nullptr;//�����ȥ���ӵ���pkmsg�ÿ�
		mPkMsg = nullptr;
	}
}

void USkillFunction::SkillEnd()
{
	//�л�״̬��ʹ���еļ����ÿ�
	if (mAttacker)
	{
		mAttacker->ChangeState(CharState::IdleRun);
		mAttacker->SetUsingSkillNull();
	}
}

