// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"
#include "FunctionFactory.generated.h"

class UAbsPkEvent;
class UAbsFilter;

UCLASS()
class UFunctionFactory : public UObject, public USingleton<UFunctionFactory>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UFunctionFactory();
	virtual ~UFunctionFactory();

private:
	void registerFunction(UAbsPkEvent* _object);//ע��Function
	void registerFilter(UAbsFilter* _object);//ע��ѡ��

	UAbsFilter* createFilter(const FString& _str);//���������������(ѡ��)

private:
	TMap<FString, UAbsPkEvent*>	mFunctionMap;
	TMap<FString, UAbsFilter*>	mFilterMap;
};
