
#pragma once

#include "Char/Skill/SkillTypes.h"
#include "Char/GameTypes.h"

#include "PkMsg.generated.h"

class AMyChar;
class USkillTemplate;
class UFightData;

UCLASS()
class UParam : public UObject
{
	GENERATED_BODY()
public:
	UParam();
	virtual ~UParam();
	virtual void BeginDestroy() override;

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
	UPkMsg();
	virtual ~UPkMsg();
	void virtual BeginDestroy() override;

	void	SetData(USkillTemplate* _skillTemp, AMyChar* _attacker, AMyChar* _target, const FVector& _targetLoc);
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
	void	SetTargetLoc(const FVector& _Loc) { mTargetLoc = _Loc; } //���ñ�������Loc
	const FVector&	GetTargetLoc() const { return mTargetLoc; }
	int32	GetTargetId() const { return mTargetId; }
	void	SetTargetId(int32 _id) { mTargetId = _id; }
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
