// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbsFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS(Abstract)
class UAbsFilter : public UObject
{
	GENERATED_BODY()

public:
	UAbsFilter();
	virtual ~UAbsFilter();

	virtual void Filter(UPkMsg* msg);//���ǿ�ѡactor
	virtual UAbsFilter* Clone();
	virtual void Paser(const TArray<FString>& _params);//��������

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mKey;

};
