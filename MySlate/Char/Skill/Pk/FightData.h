// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "../Utils/CommonDef.h"
#include "FightData.generated.h"

UCLASS()
class UFightData : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UFightData();
	virtual ~UFightData();
	virtual void BeginDestroy() override;

	UFightData* Clone();
	void Copy(UFightData* _fightData);
	void Reset();

	float GetAttackPhy() const { return mAttackPhy; }
	float GetLv() const { return mLv; }

public:
	//ԭʼ����
	float		mAttackPhy;		//������

public:
	//�ɳ����
	int			mLv;			//�ȼ�

public:
};
