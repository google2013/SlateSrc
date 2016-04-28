
#pragma once

#include "AbsBuff.generated.h"

class UAbsPkEvent;
class AMyChar;
class UBufflTemplate;
class UPkMsg;


UENUM()
enum class EBuffState : uint8 //buff״̬
{
	Idle = 0,
	Start,
	Break,
	Over,
};

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

	int32		GetBuffId() const { return mBuffId; }
	bool		IsDurable() const;
	float		GetDtVal(float _value); //����ÿ֡�˺�ֵ
	void		ChangeState(EBuffState _state) { mBuffState = _state; }
	EBuffState	GetState() const { return mBuffState; }

	void		SetData(UBufflTemplate* _buffTemp, AMyChar* _attacker, AMyChar* _target, int32 _skillId);

private:
	int32		mBuffId;		//
	int32		mSkillId;		//
	int32		mOwnerId;		//������
	AMyChar*	mOwnerChar;		//������ptr
	int32		mAttackerId;	//�ͷ���
	AMyChar*	mAttacker;		//�ͷ���ptr //issue �ͷ���������ж������������ʱһ��
	UBufflTemplate*	mBuffTemp;

	float		mTimer;		//������
	float		mTotalTime;	//��ʱ��
	int32		mLessTimes;	//ʣ�����

	EBuffState	mBuffState;		//buff״̬

	int32		mEffectUUid;
};
