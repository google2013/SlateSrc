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
	mTargetLoc = FVector::ZeroVector;
	mCanAttack = false;
	mMoving = false;
	mIsOver = false;
	mTarget = nullptr;
	mTargetId = 0;
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
			FVector targetLoc = mTarget != nullptr ? mTarget->GetActorLocation() : mTargetLoc;
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

void USkillFunction::UseSkill(AMyChar* _target, const FVector& _targetLoc)
{
	if (_target != nullptr)
	{
		mTarget = _target;
		mTargetId = _target->GetUuid();
		mTargetLoc = _target->GetActorLocation();

		//�����ص�
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mTarget = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- USkillFunction::UseSkill, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};


		mTarget->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}
	else
	{
		mTargetLoc = _targetLoc;
	}

}

bool USkillFunction::CanAttack()
{
	float DistSq = 0.f;
	AMyChar* target = mTarget;
	if (target != nullptr) //����Ŀ�꣬δ��
	{
		DistSq = (target->GetActorLocation() - mAttacker->GetActorLocation()).SizeSquared();
	}
	else if (mTargetId > 0) //����Ŀ�꣬����
	{
		if (mMoving) //�ƶ�����Ҫȡ���ƶ�
		{
			mAttacker->GetController()->StopMovement();
		}
		CancelSkill();
		return false;
	}
	else //�����ص�
	{
		DistSq = (mTargetLoc - mAttacker->GetActorLocation()).SizeSquared();
	}
	float atkDist = mSkillTemplate->mAttackDist;
	bool ret = FMath::Pow(atkDist, 2) > DistSq ? true : false;

	if (ret)
	{
		if (mMoving) //�ƶ�����Ҫȡ���ƶ�
		{
			mAttacker->GetController()->StopMovement();
			UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, stop moving, atkDist > DistSq, %f > %f"), atkDist, FMath::Sqrt(DistSq));
		}
		else
		{
			UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, dont need move, atkDist > DistSq, %f > %f"), atkDist, FMath::Sqrt(DistSq));
		}
		mMoving = false;
	}
	else
	{
		if (!mMoving)
		{
			if (target != nullptr) 
			{
				UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, move to target"));
				UNavigationSystem::SimpleMoveToActor(mAttacker->GetController(), target);
			}
			else
			{
				UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, move to location"));
				UNavigationSystem::SimpleMoveToLocation(mAttacker->GetController(), mTargetLoc);
			}
			mMoving = true;
		}
	}
	return ret;
}

void USkillFunction::CancelSkill()
{
	//��������Ŀ�걼��ʱ��Ŀ��������ȡ������
	mTargetId = 0;
	mTarget = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mAttacker->ChangeState(CharState::IdleRun);
	mAttacker->SetUsingSkillNull();
	mCanAttack = false;
	mMoving = false;
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CancelSkill"));
}

void USkillFunction::SkillBegin()
{
	if (mPkMsg != nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mPkMsg != nullptr before"));
	}

	//TODO: ��������, �����ܱ���
	mAttacker->TempNotifyA();
	mIsOver = false;

	mOwnerCD->Restart();

	UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
	pkMsg->AddToRoot();
	mPkMsg = pkMsg;

	pkMsg->SetData(mSkillTemplate, mAttacker, mTarget, mTargetLoc);

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
		mBullet->SetTargetAndLoc(mPkMsg->GetTarget(), mPkMsg->GetTargetLoc());
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
		mBullet->DetachRootComponentFromParent();
		mBullet->SetFly(true);

		UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::BulletShoot, mBullet = nullptr"));
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
	//step6 - ���м��ܺ���func, ����˲���ƶ��ƻ�ԭ��
	const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetEndSkill();
	for (UAbsPkEvent* func : functions2)
	{	//issue mPkMsg is nullptr befor
		func->RunEndSkill(mPkMsg);
	}

	mIsOver = true;
	CancelSkill();
	ReleaseData();
}

void USkillFunction::ReleaseData()
{
	if (!mIsOver)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::ReleaseData, mIsOver == false"));

		CancelSkill();

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
}

