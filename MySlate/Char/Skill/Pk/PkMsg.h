// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"

#include "PkMsg.generated.h"

class AMyChar;
class UFightData;

UCLASS()
class UPkMsg : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPkMsg();
	virtual ~UPkMsg();

private:
	bool			mCanLog;
	int32			mSkillId;						//����id
	ESkillAttackType	mSkillLogicType;				//�����߼����� SKILL_ATTACK_TYPE
	int32			mAttackerId;					//������ Ψһid
	int32			mTargetId;						//����Ŀ���� Ψһid
	AMyChar*		mAttackerPtr;					//������
	AMyChar*		mTargetPtr;						//����Ŀ����
};
