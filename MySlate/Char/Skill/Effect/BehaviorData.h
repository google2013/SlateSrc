// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorData.generated.h"

UENUM()
enum class SkillEffectType : uint8 //��Ч����
{
	SelfFollow = 0,
	SelfUnfollow,
	TargetFollow,
	TargetUnfollow,
	Bullet,
	SceneCamera,
	Count,
};

UCLASS()
class UEffectDataElement : public UObject
{
	GENERATED_BODY()
public:
	UEffectDataElement();
	virtual ~UEffectDataElement();

	int32		mEffectID;//��Чid
	SkillEffectType	mEffectType;//��Ч����
	FString		mBindPoint; //�󶨹���
	float		mDelayTime;//��ʱʱ��
	FVector		mOffset;
	FVector		mScale;
};

UCLASS()
class UBehaviorData : public UObject
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	UBehaviorData();
	virtual ~UBehaviorData();

private:

};
