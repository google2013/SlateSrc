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

	virtual void filter(UPkMsg* msg);//���ǿ�ѡactor
	virtual UAbsFilter* clone();
	virtual void paser(TArray<FString> _params);//��������

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mFilterKey;

};
