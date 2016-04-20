// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBullet.h"

#include "AI/MyAIController.h"
#include "Char/MyChar.h"
#include "Char/Comp/MyCharDataComp.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "CharMgr.h"
#include "Skill/Pk/PkMsg.h"
//#include "Skill/Pk/PkPorcess.h"

AMyBullet::AMyBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	sphereComp->InitSphereRadius(1.0f);
	CollisionComp = sphereComp;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	//CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->MaxSpeed = 300.f;
	MovementComp->InitialSpeed = 0.f;

	//TODO: mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachTo(CollisionComp);

	mTargetId = 0;
	mSkillTemp = nullptr;
	mTargetLoc = FVector(0.f, 0.f, 0.f);
	mPkMsg = nullptr;
	mPkPorcess = nullptr;
	mFlying = false;
	mSpeed = 0.f;
}

AMyBullet::~AMyBullet()
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::~AMyBullet"));
}

// Called when the game starts
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();

}

void AMyBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!mFlying)
	{
		return;
	}

	if (mTargetId > 0) //����Ŀ��
	{
		AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
		if (target != nullptr) //Ŀ��δ������ÿ֡������Ŀ��ķ��з���
		{
			FVector targetLoc = target->GetActorLocation();
			if (mTargetLoc != targetLoc)
			{
				FVector bulletLoc = GetActorLocation();
				FRotator rota = UKismetMathLibrary::FindLookAtRotation(bulletLoc, targetLoc);
				SetActorRotation(rota);
				MovementComp->Velocity = MovementComp->GetMaxSpeed() * (targetLoc - bulletLoc).GetSafeNormal(); //�ӵ��ƶ�����
				mTargetLoc = targetLoc;
			}
		}
	}

	//���ﵽLoc�����㣬�ӵ�����
	if (mTargetLoc == GetActorLocation())
	{
		CreatePk();
		BulletJump();
	}
}

void AMyBullet::SetTargetId(int32 _targetId)
{
	mTargetId = _targetId;
}

void AMyBullet::SetTargetLoc(UPARAM(ref) const FVector& _targetLoc)
{
	mTargetLoc = _targetLoc;
}

void AMyBullet::SetTargetAndLoc(int32 _targetId, UPARAM(ref) const FVector& _targetLoc)
{
	mTargetId = _targetId;
	mTargetLoc = _targetLoc;
}

void AMyBullet::SetFly(bool _fly)
{
	//��ʼ���У������ƶ�����ĵ��ٶ�ʸ����������Ŀ�� or Loc
	mFlying = mFlying;

	if (mSpeed > 0.f)
	{
		if (mTargetId > 0)
		{
			AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
			if (target != nullptr)
			{
				mTargetLoc = target->GetActorLocation();
			}
		}
		MovementComp->InitialSpeed = mSpeed;
		MovementComp->MaxSpeed = mSpeed;
		MovementComp->Velocity = MovementComp->GetMaxSpeed() * (mTargetLoc - GetActorLocation()).GetSafeNormal(); //�ӵ��ƶ�����

		//����Ŀ��
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mTargetLoc));
	}
	else
	{
		UE_LOG(BulletLogger, Error, TEXT("--- AMyBullet::SetFly, mSpeed == 0.f"));
	}
}

void AMyBullet::CallbackPkOver(TArray<FDamageInfo>& _dmgArr)
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CallbackPkOver, _dmgArr size:%d"), _dmgArr.Num());

}

void AMyBullet::CreatePk()
{
	//TODO: �����ܱ��֣� ��������


	//TODO: ����
	if (mPkPorcess == nullptr)
	{
		mPkPorcess = NewObject<UPkPorcess>(UPkPorcess::StaticClass());
		mPkPorcess->AddToRoot();
		mPkPorcess->GetPkOverDlg().BindUObject(this, &AMyBullet::CallbackPkOver);

		//���ñ��ν��㱻������Ŀ��
		AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
		if (target != nullptr)
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock != null, id:%d"), target->GetUuid());
		}
		else
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock is null"));
		}
		mPkMsg->SetTarget(target);
		mPkPorcess->SetMsg(mPkMsg);
		mPkPorcess->Run();

		mPkPorcess->RemoveFromRoot();
		mPkPorcess = nullptr;
	}
}

//�ӵ���Ծ
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

	if (mPkPorcess != nullptr)
	{
		mPkPorcess->RemoveFromRoot();
		mPkPorcess = nullptr;
	}
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg = nullptr;
	}

	OnProjectileDestroyed();
	Destroy();
}

void AMyBullet::OnMyCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyChar* OtherChar = Cast<AMyChar>(OtherActor);
	//TODO�����ﲻ�������Ŀ�������㣬��Ϊ��������Ŀ���Loc���������
	//		ֻ��Է��й�������ײ����ײ����Ŀ�꣬��ʱ����
	//if (mTargetId > 0)//����Ŀ�꣬��ײ���ֻ����Ƿ�ΪĿ��
	//{
	//	AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
	//	if (target != nullptr) //�����Ŀ���������ײ���Ķ���ΪĿ����󣬿�ʼ����
	//	{
	//		if (target == OtherChar)
	//		{
	//			//TODO: �������ܻ����֣����㣬�����ӵ�
	//			CreatePk();
	//			DestroyBullet();
	//		}
	//	}
	//}
	//else
	//{
		//TODO: ����Ŀ�꣬�ӵ�����Ŀ�ĵع����У���ײ��ײ���ĵ��˶�Ӧ����һ��ս�����㣬
		if (mPkMsg->GetAttackerTeam() != OtherChar->GetDataComp()->GetTeamType()) //����ͬһ�ӵ�
		{
			//

		}
	//}

	//if (target == nullptr)
	//{
	//	UE_LOG(BulletLogger, Error, TEXT("--- Bullet Overlap, mTargetId > 0, but target ptr == null"));
	//	return;
	//}
}
