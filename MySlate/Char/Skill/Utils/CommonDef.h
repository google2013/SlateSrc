// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CommonDef.generated.h"

//UEmptyֻ��Ϊ������������࣬����FString
UCLASS()
class UEmpty : public UObject
{
	GENERATED_BODY()

public:
	UEmpty() {}
	virtual ~UEmpty() {}
};

const FString Split_Com = TEXT(",");
const FString Split_Line = TEXT("_");
const FString Split_Pound = TEXT("#");
const FString Split_Sem = TEXT(";");