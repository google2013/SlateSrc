// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircleFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS()
class UCircleFilter : public UAbsFilter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCircleFilter();
	virtual ~UCircleFilter();

	virtual void Filter(UPkMsg* msg) override;
	virtual UAbsFilter* Clone() override;
	virtual void Parser(const TArray<FString>& _params);

	static UCircleFilter* CreateFilter(const FString& _key);

public:
	//int32		mCenterType;	//���ĵ� -- 1:�����ߣ�-1:�ܻ���
	int32		mSelectType;	//ѡ�� -- 1:��������-1:�ܻ���
	int32		mCount;			//ѡ������
	int32		mRadius;		//ѡ�˰뾶
};
