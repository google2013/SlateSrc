// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"
#include "FightData.h"
#include "Char/GameTypes.h"

#include "PkMsg.generated.h"

class AMyChar;
class USkillTemplate;

DECLARE_DELEGATE(FSetNullDlg);

UCLASS()
class UParam : public UObject
{
	GENERATED_BODY()
public:
	UParam();
	virtual ~UParam();
	void Init();

	UFightData*		mFightData;			//ս������
	AMyChar*		mTarget;			//Ŀ��

};

UCLASS()
class UPkMsg : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPkMsg();
	virtual ~UPkMsg();

	void	SetData(USkillTemplate* _skillTemp, const FVector& _targetLoc, int32 _attackerId, int32 _targetId = 0);
	const TArray<UParam*>& GetTargets() const { return mTargetArr; }
	void	AddTarget(AMyChar* _char);
	USkillTemplate*	GetSkillTemp() const { return mSkillTemp; }

	void	SetNullDlg(FSetNullDlg _dlg) { mSetNullDlg = _dlg; }
	void	ExeNullDlg();
	void	SetAttackerData(UFightData* _data) { mAttackerData = _data; }

private:
	bool			mCanLog;
	int32			mSkillId;						//����id
	USkillTemplate*	mSkillTemp;		
	ESkillAttackType	mSkillLogicType;				//�����߼����� SKILL_ATTACK_TYPE
	int32			mAttackerId;					//������ Ψһid
	int32			mTargetId;						//����Ŀ���� Ψһid
	AMyChar*		mTarget;
	TArray<UParam*>	mTargetArr;						//Ŀ�꼯
	UFightData*		mAttackerData;					//�����߲���
	FVector			mTargetLoc;						//Ŀ��λ��
	ETeam			mTeamType;						//���ѱ��

	FSetNullDlg		mSetNullDlg;		//���ñ��ͷŶ���ʱ��֪֮ͨǰ�����ĵط�set null
};
