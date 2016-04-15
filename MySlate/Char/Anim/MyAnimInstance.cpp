// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyAnimInstance.h"

#include "../MyChar.h"
#include "../MyBullet.h"

UMyAnimInstance::UMyAnimInstance()
{
	mOwnerChar = nullptr;
	mSpeed = 0.f;
	mCharState = CharState::IdleRun;
}

UMyAnimInstance::~UMyAnimInstance()
{

}

bool UMyAnimInstance::IsMoving()
{
	return GetOwnerChar()->GetVelocity().Size() > 0.f ? true : false;
}

AMyChar* UMyAnimInstance::GetOwnerChar()
{
	if (!mOwnerChar)
	{
		APawn* owner = TryGetPawnOwner();
		mOwnerChar = owner ? Cast<AMyChar>(owner) : nullptr;
	}
	return mOwnerChar;
}

void UMyAnimInstance::AnimNotify_BulletCreate(UAnimNotify * Notify)
{
	
	if (mOwnerChar)
	{
		UE_LOG(AnimLogger, Warning, TEXT("--- AnimNotify_BulletCreate"));


	}
}

void UMyAnimInstance::AnimNotify_BulletShoot(UAnimNotify * Notify)
{
	if (mOwnerChar)
	{
		//UE_LOG(MyAnimInstLogger, Warning, TEXT("--- AnimNotify_BulletShoot"));
	
	}
	
}

void UMyAnimInstance::AnimNotify_AttackOver(UAnimNotify * Notify)
{
	if (mOwnerChar) //�������л�����״̬
	{
		if (mOwnerChar->mCharState == CharState::Attack)
		{
			mOwnerChar->mCharState = CharState::IdleRun;
		}
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!mOwnerChar)
	{
		mOwnerChar = GetOwnerChar();
	}

	if (mOwnerChar)
	{
		mSpeed = mOwnerChar->GetVelocity().Size(); //�����ٶ�
		mCharState = mOwnerChar->mCharState; //���ö���״̬
	}
}
