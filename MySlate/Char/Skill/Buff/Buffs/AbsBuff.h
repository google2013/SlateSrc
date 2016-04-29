
#pragma once

#include "../../SkillTypes.h"
#include "AbsBuff.generated.h"

class UAbsPkEvent;
class AMyChar;
class UBufflTemplate;
class UPkMsg;

UCLASS()
class UAbsBuff : public UObject
{
	GENERATED_BODY()

public:
	UAbsBuff();
	virtual ~UAbsBuff();
	virtual void BeginDestroy() override;
	
	virtual void Tick(float DeltaSeconds);

	void BuffStart();
	void BuffOver();
	virtual void RunBeforePk(UPkMsg* msg);
	virtual void RunEndPk(UPkMsg* msg);

	AMyChar*	GetOwnerChar();
	UBufflTemplate*	GetBuffTemp() const { return mBuffTemp; }
	int32		GetBuffId() const { return mBuffId; }
	float		GetDtVal(float _value); //����ÿ֡�˺�ֵ
	void		ChangeState(EBuffState _state) { mBuffState = _state; }
	EBuffState	GetState() const { return mBuffState; }

	void		SetData(UBufflTemplate* _buffTemp, AMyChar* _attacker, AMyChar* _target, int32 _skillId);

private:
	int32		mBuffId;		//
	int32		mSkillId;		//
	//int32		mOwnerId;		//������
	AMyChar*	mOwnerChar;		//������ptr
	//int32		mAttackerId;	//�ͷ���
	AMyChar*	mAttacker;		//�ͷ���ptr //issue �ͷ���������ж������������ʱһ��
	UBufflTemplate*	mBuffTemp;

	float		mTimer;		//������
	float		mTotalTime;	//��ʱ��
	int32		mLessTimes;	//ʣ�����

	EBuffState	mBuffState;		//buff״̬

	TArray<int32>	mEffectUUids;
};
