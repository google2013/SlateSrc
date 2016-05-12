
#include "MySlate.h"
#include "MyBullet.h"

#include "./AI/MyAIController.h"
#include "./MyChar.h"
#include "./Comp/MyCharDataComp.h"
#include "./Skill/Template/SkillTemplate.h"
#include "./CharMgr.h"
#include "./Skill/Pk/PkMsg.h"
#include "Skill/Pk/PkProcess.h"

#include "./Object/ObjMgr.h"

AMyBullet::AMyBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComp"));
	sphereComp->InitSphereRadius(1.0f);
	CollisionComp = sphereComp;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	//CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	//sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp2"));
	//sphereComp->InitSphereRadius(2.0f);
	//MyRoot = sphereComp;
	//MyRoot->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	////CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	////CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	////CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//MyRoot->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//MyRoot->AttachTo(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MyProjectileComp"));
	MovementComp->SetUpdatedComponent(RootComponent);
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->MaxSpeed = 0.f;
	MovementComp->InitialSpeed = 0.f;

	//TODO: mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMeshComp"));
	MeshComp->AttachTo(CollisionComp);

	mTargetId = 0;
	mSkillTemp = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mPkMsg = nullptr;
	mPkProcess = nullptr;
	mFlying = false;
	mSpeed = 0;
	mStartPos = FVector::ZeroVector;
	mTarget = nullptr;
}

AMyBullet::~AMyBullet()
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::~AMyBullet"));
}

void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AMyBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	IBehavInterface::BehavTick(DeltaSeconds);

	if (!mFlying)
	{
		return;
	}


	if (mTargetId > 0) //����Ŀ��
	{
		AMyChar* target = mTarget;
		if (target != nullptr) //Ŀ��δ������ÿ֡������Ŀ��ķ��з���
		{
			FVector targetLoc = target->GetActorLocation();
			if (mTargetLoc != targetLoc)
			{
				FVector bulletLoc = GetActorLocation();
				FRotator rota = UKismetMathLibrary::FindLookAtRotation(bulletLoc, targetLoc);
				SetActorRotation(rota);
				MovementComp->Velocity = MovementComp->GetMaxSpeed() * (targetLoc - bulletLoc).GetSafeNormal(); //�ӵ��ƶ�����
				
				mPkMsg->SetTargetLoc(targetLoc); // ����Loc����Ϊ�˽���ʱĿ��������Ӱ��ѡ���߼�
				mTargetLoc = targetLoc;
			}
		}
	}

	if (mSkillTemp->mBltElem->mLockedType == ELockedType::Loc)
	{
		if (mSkillTemp->mBltElem->mFlyDist > 0)
		{
			float distSq = FVector::DistSquared(GetActorLocation(), mStartPos);
			float flyDist = FMath::Pow((float)mSkillTemp->mBltElem->mFlyDist, 2.f);

			if (distSq > flyDist)
			{
				DestroyBullet();
				UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::Tick, distSq > flyDist"));
			}
		}
	}
	else if (mSkillTemp->mBltElem->mLockedType == ELockedType::Char) //������Ŀ����������������κν���
	{
		if (mPkMsg->GetTargetId() > 0 && mPkMsg->GetTarget() == nullptr)
		{
			if (GetActorLocation().Equals(mTargetLoc, mSkillTemp->mBltElem->mTolerance))
			{
				DestroyBullet();
				UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::Tick, target death, bullet arrival"));
				//CreatePk();
				//BulletJump();
			}
		}
	}
}

void AMyBullet::Destroyed()
{
	if (MovementComp != nullptr)
	{
		MovementComp->DestroyComponent();
	}	
	//if (MyRoot != nullptr)
	//{
	//	MyRoot->DetachFromParent();
	//	MyRoot->DestroyComponent();
	//}	
	if (MeshComp != nullptr)
	{
		MeshComp->DetachFromParent();
		MeshComp->DestroyComponent();
	}
	if (CollisionComp != nullptr)
	{
		CollisionComp->DetachFromParent();
		CollisionComp->DestroyComponent();
	}
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::Destroyed"));
	Super::Destroyed();
}

void AMyBullet::SetTargetAndLoc(AMyChar* _target, const FVector& _targetLoc)
{
	mTargetLoc = _targetLoc;
	
	if (_target != nullptr)
	{
		mTarget = _target;
		mTargetId = _target->GetUuid();

		//�����ص�
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mTarget = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- AMyBullet::SetTargetAndLoc, id:%d"), _deathChar->GetUuid());
		};

		_target->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}
}

void AMyBullet::SetPkMsg(UPkMsg* _pkMsg)
{
	mPkMsg = _pkMsg;
	UE_LOG(BuffLogger, Warning, TEXT("--- AMyBullet::SetPkMsg"));
}

void AMyBullet::SetFly(bool _fly)
{
	mFlying = _fly;
	if (_fly) //��ʼ���У������ƶ�����ĵ��ٶ�ʸ����������Ŀ�� or Loc
	{
		mStartPos = GetActorLocation();//��¼һ�¿�ʼ��

		if (mTarget != nullptr)
		{
			mTargetLoc = mTarget->GetActorLocation();
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mTargetLoc));//����Ŀ��
		}

		MovementComp->InitialSpeed = (float)mSpeed;
		MovementComp->MaxSpeed = (float)mSpeed;
		MovementComp->Velocity = MovementComp->GetMaxSpeed() * (mTargetLoc - GetActorLocation()).GetSafeNormal(); //�ӵ��ƶ�����
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyBullet::OnMyCollisionCompBeginOverlap);

		//��������ص㣬�ҷ��о��� > 0������о���һ�����ڿ�ʼ����Ŀ���ľ��룬����ڰ������ļ��������һ���ľ������ʧ
		if (mSkillTemp->mBltElem->mLockedType == ELockedType::Loc && mSkillTemp->mBltElem->mFlyDist > 0)
		{
			float distSq = (mTargetLoc, mStartPos).Size();
			float flyDist = mSkillTemp->mBltElem->mFlyDist;

			if (flyDist < distSq)
			{
				UE_LOG(BulletLogger, Error, TEXT("--- AMyBullet::SetFly, flyDist < distSq, %f < %f "), flyDist, distSq);
			}
		}

		if (mSpeed == 0)
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::SetFly, bullet speed == 0 "));
		}
	}
	else
	{
		MovementComp->Velocity = FVector::ZeroVector;
	}
}

void AMyBullet::CallbackPkOver(TArray<UDamageInfo*> _dmgArr)
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CallbackPkOver, _dmgArr size:%d"), _dmgArr.Num());

}

void AMyBullet::CreatePk()
{
	//TODO: ��������, �����ܱ���
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, targetId:%d"), mPkMsg->GetTargetId());

	//���ñ��ν��㱻������Ŀ��
	AMyChar* target = mPkMsg->GetTarget();
	if (target != nullptr)
	{
		target->TempNotifyB();
	}
	//return; //for test

	//TODO: ��ʱ��������
	if (mPkProcess == nullptr)
	{
		if (target != nullptr)
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock != null, id:%d"), target->GetUuid());

			mPkProcess = GetObjMgr()->GetObj<UPkProcess>(GetObjMgr()->mPkProcessCls);
			mPkProcess->SetPkOverDlg(FPkOverDlg::CreateUObject(this, &AMyBullet::CallbackPkOver));
			mPkMsg->SetTarget(target);
			mPkProcess->SetMsg(mPkMsg);
			mPkProcess->Run();

			mPkProcess->Recycle();
			mPkProcess = nullptr;
		}
		else
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock is null"));
		}
	}
}

//�ӵ�����
void AMyBullet::BulletJump()
{
	int32 count = 0; //getBulletFunc->getcount();��ʱ������
	if (count > 0)
	{
	}
	else //������ֱ�������ӵ�
	{
		DestroyBullet();
	}
}

//void AMyBullet::OnHit(const FHitResult& HitResult)
//{
//	DealDamage(HitResult);
//	OnProjectileHit(HitResult.Actor.Get(), HitResult.ImpactPoint, HitResult.ImpactNormal);
//
//	if (RemainingDamage <= 0)
//		DestroyBullet();
//}

void AMyBullet::DestroyBullet()
{
	IBehavInterface::RemoveBehavElemAll();

	if (mPkProcess != nullptr)
	{
		mPkProcess->Recycle();
		mPkProcess = nullptr;
	}
	if (mPkMsg != nullptr) //����ӵ������ȥ�ˣ� pkMsgӦ�ø����ӵ��ͷ�
	{	
		mPkMsg->Recycle();
		mPkMsg = nullptr;
	}

	OnProjectileDestroyed();
	Destroy();
}

void AMyBullet::OnMyCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyChar* target = Cast<AMyChar>(OtherActor);
	if (target == nullptr)
	{
		return;
	}

	//TODO: ��ʱ��ֻ�Եз�,���й�������ײ����ײ����Ŀ�꣬��ʱ����
	if (mSkillTemp->mBltElem->mLockedType == ELockedType::Loc && mSkillTemp->mBltElem->mFlyDist > 0)
	{
		if (target->GetDataComp()->GetTeamType() != mPkMsg->GetAttackerTeam())
		{
			mPkMsg->SetTargetId(target->GetUuid());
			mPkMsg->SetTarget(target);
			CreatePk();
		}
	}
	else if (mSkillTemp->mBltElem->mLockedType == ELockedType::Char) //TODO: ��ʱ��ֻ�Եз�����Ŀ������˺�
	{
		int32 targetId = target->GetUuid();
		if (mPkMsg->GetTargetId() > 0 && mPkMsg->GetTarget() != nullptr)
		{
			CreatePk();
			BulletJump();
		}
	}
}
