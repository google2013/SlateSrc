/*
��ɫ��������
*/
#pragma once

#include "CharData.generated.h"

class UFightData;

UCLASS()
class UCharData : public UObject
{
	GENERATED_BODY()

public:
	UCharData();
	virtual ~UCharData();

	UFightData*	GetFightData() const { return mFightData; }

public:
	int32		mId;
	FString		mName;
	FString		mDescr;
	float		mHeath;
	UFightData*	mFightData;
};
