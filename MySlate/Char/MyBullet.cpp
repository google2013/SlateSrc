// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Char/MyChar.h"
#include "Char/Comp/MyCharDataComp.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Kismet/KismetMathLibrary.h"
#include "CharMgr.h"

DECLARE_LOG_CATEGORY_EXTERN(BulletLogger, Log, All);
DEFINE_LOG_CATEGORY(BulletLogger)

// Sets default values for this component's properties
AMyBullet::AMyBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(1.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->MaxSpeed = 300.f;
	MovementComp->InitialSpeed = 300.f;

	//TODO: mesh component
	//MeshComp->

	bInitialized = false;
	mAttackerId = 0;
	mTargetId = 0;
	mSkillTemp = nullptr;
	MovementComp->InitialSpeed = 0.f;
	mTargetLoc = FVector(0.f, 0.f, 0.f);
	mLastTargetLoc = FVector(0.f, 0.f, 0.f);
	RemainingDamage = 50.f;
}

AMyBullet::~AMyBullet()
{

}

// Called when the game starts
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyBullet::OnCollisionCompBeginOverlap);//����ײ�����ײ�¼�
}

void AMyBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//TODO: ���Կ��ǹ��������������ӵ���Ȼ��Ч����Ҫ�ӵ�����ʱ���ϣ�����������
	AMyChar* attacker = UCharMgr::GetInstance()->GetChar(mAttackerId);
	if (attacker == nullptr) //�����������������ӵ�
	{
		DestroyBullet();
		return;
	}

	if (mTargetId > 0) //��Ŀ�꣬ÿ֡������Ŀ��ķ��з���
	{
		AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
		if (target != nullptr)
		{
			FVector targetLoc = target->GetActorLocation();
			if (mLastTargetLoc != targetLoc)
			{
				FVector bulletLoc = GetActorLocation();
				FRotator rota = UKismetMathLibrary::FindLookAtRotation(bulletLoc, targetLoc);
				SetActorRotation(rota);
				MovementComp->Velocity = MovementComp->GetMaxSpeed() * (targetLoc - bulletLoc).GetSafeNormal(); //�ӵ��ƶ�����
				mLastTargetLoc = targetLoc;
			}
		}
		else//�ܻ��������������ӵ�
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- Bullet flying, but target death, destroy bullet"));
			DestroyBullet();
			return;
		}
	}

}

void AMyBullet::InitProjectile(const FVector& Direction, uint8 InTeamNum, int32 ImpactDamage, float InLifeSpan)
{
	MovementComp->OnProjectileStop.AddDynamic(this, &AMyBullet::OnHit);
	MovementComp->Velocity = MovementComp->InitialSpeed * Direction;


	RemainingDamage = ImpactDamage;
	bInitialized = true;
}

void AMyBullet::SetSpeed(float _speed)
{
	MovementComp->InitialSpeed = _speed;
	MovementComp->MaxSpeed = _speed;
}

void AMyBullet::SetTargetLoc(UPARAM(ref) const FVector& _targetLoc)
{
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _targetLoc));

	//����Ŀ��㣬������������t = s / v;
	mTargetLoc = _targetLoc;
	
	if (mSkillTemp)
		mDist = mSkillTemp->mAttackDist;

	if (MovementComp->MaxSpeed > 0.f && mDist > 0.f)
		SetLifeSpan(mDist / MovementComp->MaxSpeed);
	else
	{
		UE_LOG(BulletLogger, Warning, TEXT("--- MovementComp->MaxSpeed or mDist , == 0"));
	}
}

void AMyBullet::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemp = _skillTemp;
}

void AMyBullet::OnHit(const FHitResult& HitResult)
{
	DealDamage(HitResult);
	OnProjectileHit(HitResult.Actor.Get(), HitResult.ImpactPoint, HitResult.ImpactNormal);

	if (RemainingDamage <= 0)
		DestroyBullet();
}

void AMyBullet::DestroyBullet()
{
	OnProjectileDestroyed();
	Destroy();
}

void AMyBullet::OnCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (mTargetId == 0)//û���ܻ��ߣ�������ײ���
	{
		return;
	}

	AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
	if (target == nullptr)
	{
		UE_LOG(BulletLogger, Error, TEXT("--- Bullet Overlap, mTargetId > 0, but target ptr == null"));
		return;
	}

	AMyChar* OtherChar = Cast<AMyChar>(OtherActor);

	if (target != nullptr) //�����Ŀ���������ײ���Ķ���ΪĿ����󣬿�ʼ����
	{
		if (target == OtherChar)

			//TODO: �������ܻ����֣����㣬�����ӵ�
			DestroyBullet();
	}

	//if (!bInitialized)
	//	return;

	//AMyChar* OtherChar = Cast<AMyChar>(OtherActor);
	////if (!OtherChar || !mAttackActor)
	////	return;

	//if (mTargetActor != nullptr) //�����Ŀ�������ײ����Ŀ�����ֱ�ӷ���
	//{
	//	if (OtherChar == mTargetActor)
	//		DestroyBullet();
	//}


	////add enemy
	//if (mAttackActor->mDataComp->mTeam != OtherChar->mDataComp->mTeam)
	//{
	//	FHitResult PawnHit;
	//	PawnHit.Actor = OtherChar;
	//	PawnHit.Component = OtherChar->GetCapsuleComponent();
	//	PawnHit.bBlockingHit = true;
	//	PawnHit.Location = PawnHit.ImpactPoint = GetActorLocation();
	//	PawnHit.Normal = PawnHit.ImpactNormal = -MovementComp->Velocity.GetSafeNormal();

	//	OnHit(PawnHit);
	//}
}

void AMyBullet::DealDamage(FHitResult const& HitResult)
{
	//const AStrategyChar* HitChar = Cast<AStrategyChar>(HitResult.Actor.Get());
	//const float PrevHealth = HitChar ? HitChar->Health : 0.0f;

	////UGameplayStatics::ApplyPointDamage(HitResult.Actor.Get(), RemainingDamage, -HitResult.ImpactNormal, HitResult, NULL, this, UDamageType::StaticClass());

	//if (HitChar && !ConstantDamage)
	//{
	//	RemainingDamage -= FMath::TruncToInt(PrevHealth - HitChar->Health);
	//}
}