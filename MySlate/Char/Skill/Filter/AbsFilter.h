// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbsFilter.generated.h"

/*
һ�㶨�壺
float		mValue; //��ֵ
int32		mOwner; //������ -- 1:�����ߣ�-1:�ܻ���
int32		mLimitId; //��������
*/

class AMyChar;
class UPkMsg;

UCLASS()
class UAbsFilter : public UObject
{
	GENERATED_BODY()

public:
	UAbsFilter();
	virtual ~UAbsFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* msg) {}//���ǿ�ѡactor
	virtual UAbsFilter* Clone() { return nullptr; }
	virtual void Parser(const TArray<FString>& _params) {}//��������

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mKey;

};
