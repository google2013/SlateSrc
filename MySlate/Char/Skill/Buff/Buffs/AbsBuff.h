
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

	TArray<UAbsPkEvent*>	GetBuffAttrs();
	AMyChar*	GetOwnerChar();
	void		Remove() { mIsRemove = true; }
	bool		IsRemoeve() const { return mIsRemove; }

	int32		GetBuffId() const { return mBuffId; }

private:
	int32		mBuffId;		//
	int32		mOwnerId;		//������
	int32		mAttackerId;	//�ͷ���
	UBufflTemplate*	mBuffTemp;

	float		mTimer;		//������
	float		mTotalTime;	//��ʱ��
	int32		mLessTimes;	//ʣ�����
	bool		mIsRemove;
};
