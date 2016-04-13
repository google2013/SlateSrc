// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"
#include "FightData.h"

#include "PkMsg.generated.h"

class AMyChar;

class UParam
{
	UParam()
	{
		mFightData = NewObject<UFightData>(UFightData::StaticClass());
		mFightData->AddToRoot();
	}
	~UParam() { mFightData->RemoveFromRoot(); }

	UFightData*		mFightData;			//ս������
	int32			mTargetId;
};

UCLASS()
class UPkMsg : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPkMsg();
	virtual ~UPkMsg();

	const TArray<UParam*>& GetTargets() const { return mTargetArr; }

private:
	bool			mCanLog;
	int32			mSkillId;						//����id
	ESkillAttackType	mSkillLogicType;				//�����߼����� SKILL_ATTACK_TYPE
	int32			mAttackerId;					//������ Ψһid
	int32			mTargetId;						//����Ŀ���� Ψһid
	TArray<UParam*>	mTargetArr;						//Ŀ�꼯
	UFightData*		mAttackerData;					//�����߲���������ָ���Ƿ�ֹ�������������
};
