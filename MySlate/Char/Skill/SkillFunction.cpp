// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

#include "Template/SkillTemplate.h"
#include "Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"
#include "../Comp/MyCharDataComp.h"
#include "CoolDown/CoolDown.h"
#include "Function/Funcs/AbsPkEvent.h"

USkillFunction::USkillFunction() : Super()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
	mBullet = nullptr;
	mAttacker = nullptr;
	mTargetId = 0;
	mTargetLoc = FVector::ZeroVector;
	mCanAttack = false;
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction"));
}

void USkillFunction::BeginDestroy()
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg->ConditionalBeginDestroy();
		mPkMsg = nullptr;
	}

	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::BeginDestroy:%d"), mSkillId);
	Super::BeginDestroy();
}

void USkillFunction::Tick(float DeltaSeconds)
{
	if (!mCanAttack)
	{
		mCanAttack = CanAttack();
	}

	if (mCanAttack)
	{
		if (mAttacker->GetState() != CharState::Attack)
		{
			mAttacker->ChangeState(CharState::Attack);
			//�������
			AMyChar* target = mTargetId > 0 ? UCharMgr::GetInstance()->GetChar(mTargetId) : nullptr;
			FVector targetLoc = target != nullptr ? target->GetActorLocation() : mTargetLoc;
			mAttacker->FaceToTargetLoc(targetLoc);
		}
	}
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
	return true; //for test

	AMyChar* target = mTargetId > 0 ? UCharMgr::GetInstance()->GetChar(mTargetId) : nullptr;
	float DistSq = 0.f;
	if (target) //����Ŀ��
	{
		DistSq = (target->GetActorLocation() - mAttacker->GetActorLocation()).SizeSquared();
	}
	else //�����ص�
	{
		DistSq = (mTargetLoc - mAttacker->GetActorLocation()).SizeSquared();
	}
	float atkDist = mSkillTemplate->mAttackDist;
	return FMath::Pow(atkDist, 2) > DistSq ? true : false;
}

void USkillFunction::SkillBegin()
{
	if (mPkMsg != nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mPkMsg != nullptr before"));
	}

	mOwnerCD->Restart();

	UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
	pkMsg->AddToRoot();
	mPkMsg = pkMsg;

	pkMsg->SetData(mSkillTemplate, mAttacker->GetUuid(), mTargetId, mTargetLoc);

	UFightData* attackerData = mAttacker->GetDataComp()->GetFigthData()->Clone();//�������ߵ�ս�����ݿ����� �½���ս�����ݶ�����
	attackerData->AddToRoot();//��pkMsg�������������ͷ��������
	pkMsg->SetAttackerData(attackerData);
	pkMsg->SetAttackerTeam(mAttacker->GetDataComp()->GetTeamType());
	//step1 - ���м���ǰ��func, ����˲���ƶ�
	const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetBeforeSkill();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunBeforeSkill(mPkMsg);
	}

	//step2 - ����buffǰ���¼� һ�����ڷż���ǰҪbuff�����и��������Լ���buff��func
	const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforePk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunBeforePk(mPkMsg);
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
		 //TODO: �����ӵ�,����pk��Ϣ, �󶨵������ĳ��socket��λ��
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		mBullet = GWorld->SpawnActor<AMyBullet>(mAttacker->BulletClass, SpawnInfo);
		mBullet->SetPkMsg(mPkMsg);
		mBullet->SetSkillTemplate(mSkillTemplate);
		mBullet->SetTargetAndLoc(mTargetId, mTargetLoc);  
		mBullet->SetSpeed(mSkillTemplate->mBulletSpeed);
		mBullet->SetFly(false);

		if (mSkillTemplate->mAttachPoint.Len() > 0) //�а󶨲�λ
		{
			//TODO: ��������, ���þ�����Ϣtransform
			mBullet->AttachRootComponentTo(mAttacker->GetMesh(), FName(*mSkillTemplate->mAttachPoint));
			mBullet->SetActorRelativeLocation(FVector::ZeroVector);
			mBullet->SetActorRelativeRotation(FRotator::ZeroRotator);
			mBullet->SetActorRelativeScale3D(FVector(1.f, 1.f, 1.f));
		}
		else
		{
			mBullet->SetActorLocation(mAttacker->GetActorLocation());
			mBullet->SetActorRotation(mAttacker->GetActorRotation());
		}
	}
}

void USkillFunction::BulletShoot()
{
	if (mBullet != nullptr && mPkMsg != nullptr)
	{
		//step3 - ���и��������Լ�������������func
		const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforeEvns();
		for (UAbsPkEvent* func : functions)
		{
			func->RunBeforeEvns(mPkMsg);
		}

		//TODO: ���������󶨵㣬��Ŀ����У�����ײ�����ײ�¼�
		//mBullet->GetRootComponent()->DetachFromParent();
		mBullet->DetachRootComponentFromParent();

		mBullet->SetFly(true);
		mBullet->CollisionComp->OnComponentBeginOverlap.AddDynamic(mBullet, &AMyBullet::OnMyCollisionCompBeginOverlap);

		mBullet = nullptr;//�����ȥ���ӵ���pkMsg�ÿգ����ӵ�ȥ�ͷ�pkMsg
		mPkMsg = nullptr;
	}
	else
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletShoot, mBullet or mPkMsg is nullptr"));
	}
}

void USkillFunction::SkillEnd()
{
	//�л�״̬��ʹ���еļ����ÿ�
	if (mAttacker)
	{
		//step6 - ���м��ܺ���func, ����˲���ƶ��ƻ�ԭ��
		const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetEndSkill();
		for (UAbsPkEvent* func : functions2)
		{	//issue mPkMsg is nullptr befor
			func->RunEndSkill(mPkMsg);
		}

		mAttacker->ChangeState(CharState::IdleRun);
		mAttacker->SetUsingSkillNull();
		mCanAttack = false;

		ReleaseData();
	}
}

void USkillFunction::ReleaseData()
{
	mAttacker->SetUsingSkillNull();
	mCanAttack = false;

	//�����ͷ��ڴ�
	if (mBullet != nullptr) //�����ӵ���û�����ȥ�����ܾͱ���ϣ���Ҫ�����ӵ�,pkMsg��������������
	{
		mBullet->DestroyBullet();
		mBullet = nullptr;
		mPkMsg = nullptr;
	}
	else //��û�д����ӵ����ͱ�����������pkMsg
	{
		if (mPkMsg != nullptr)
		{
			mPkMsg->RemoveFromRoot();
			mPkMsg->ConditionalBeginDestroy();
			mPkMsg = nullptr;
		}
	}
}

