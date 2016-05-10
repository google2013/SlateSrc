/*
������
*/
#pragma once

#include "./AbsPkEvent.h"
#include "AttackPhy.generated.h"

UCLASS()
class UAttackPhy : public UAbsPkEvent
{
	GENERATED_BODY()

public:
	UAttackPhy();
	virtual ~UAttackPhy();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

public:
	static UAttackPhy* CreateFunction(const FString& _key);
	virtual UAbsPkEvent* Clone() override;
	virtual void Parser(const TArray<FString>& _params) override;

public://buff
	virtual void RunTick(float DeltaSeconds) override;
	virtual void RunStart() override;
	virtual void RunOver() override;

private://buff
	float		mDtVal; //ÿ֡�˺�ֵ
	bool		mDurable; //�Ƿ����

public:
	float		mValue;
	int32		mOwner;
	int32		mLimitId;
};
