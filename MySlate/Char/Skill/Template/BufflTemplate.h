// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/CommonHeader.h"

#include "BufflTemplate.generated.h"

UCLASS(Blueprintable)
class UBufflTemplate : public UObject
{
	GENERATED_BODY()

public:
	UBufflTemplate();
	virtual ~UBufflTemplate();
	virtual void BeginDestroy() override;

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		int32			mId;
};
