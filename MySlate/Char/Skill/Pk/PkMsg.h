// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"
#include "FightData.h"
#include "Char/GameTypes.h"

#include "PkMsg.generated.h"

class AMyChar;
class USkillTemplate;

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

	float			mDmgPhyValue = 0.0f;						//�������˺�
	float			mDmgMagValue = 0.0f;						//�������˺�

};

UCLASS()
class UPkMsg : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPkMsg();
	virtual ~UPkMsg();

	void	SetData(USkillTemplate* _skillTemp, int32 _attackerId, int32 _targetId, const FVector& _targetLoc);
	const TArray<UParam*>& GetTargets() const { return mTargetArr; }
	void	AddTarget(AMyChar* _char);
	USkillTemplate*	GetSkillTemp() const { return mSkillTemp; }

	//void	ExeNullDlg();
	void	SetAttackerData(UFightData* _data);
	UFightData*	GetAttackerData() const { return mAttackerData; }
	void	SetAttackerId(int32 _id) { mAttackerId = _id; }
	int32	GetAttackerId() const { return mAttackerId;}
	void	SetTarget(AMyChar* _char) {  mTargetLocked = _char; } //���ñ�������Ŀ��
	AMyChar*	GetTarget() const { return mTargetLocked; }
	const FVector&	GetTargetLoc() const { return mTargetLoc; }
	int32	GetTargetId() const { return mTargetId; }
	void	SetAttackerTeam(const ETeam& _type) { mTeamType = _type; }
	const ETeam&	GetAttackerTeam() const { return mTeamType; }
	void	SetCurrTarget(UParam* _target);


	//--------------- Begin
	void SetAttackDmgValue(float _value, int _limitId = -1, bool _isAdd = true);			//�˺�����(��ֵ)(�ܻ���)

	//--------------- Begin
private:
	bool			mCanLog;
	int32			mSkillId;						//����id
	USkillTemplate*	mSkillTemp;		
	ESkillAttackType	mSkillLogicType;			//�����߼����� SKILL_ATTACK_TYPE
	int32			mAttackerId;					//������ Ψһid
	int32			mTargetId;						//����Ŀ���� Ψһid
	AMyChar*		mTargetLocked;					//����Ŀ����
	TArray<UParam*>	mTargetArr;						//Ŀ�꼯
	UParam*			mCurrTarget;					//Ŀ�꼯��ÿ��������ʱָ��
	UFightData*		mAttackerData;					//�����߲���
	UFightData*		mAttackerDataForCacul;			//�����߲���,���ڼ���
	FVector			mTargetLoc;						//Ŀ��λ��
	ETeam			mTeamType;						//�����߶�����
};
