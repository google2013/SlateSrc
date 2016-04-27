
#pragma once

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
	void		Remove() { mIsRemove = true; }
	bool		IsRemoeve() const { return mIsRemove; }

	int32		GetBuffId() const { return mBuffId; }
	void		SetAttacker(AMyChar* _char);
	void		SetBuffTemp(UBufflTemplate* _buffTemp);

private:
	int32		mBuffId;		//
	int32		mOwnerId;		//������
	AMyChar*	mOwnerChar;		//������ptr
	int32		mAttackerId;	//�ͷ���
	AMyChar*	mAttacker;		//�ͷ���ptr
	UBufflTemplate*	mBuffTemp;

	float		mTimer;		//������
	float		mTotalTime;	//��ʱ��
	int32		mLessTimes;	//ʣ�����
	bool		mIsRemove;
};
