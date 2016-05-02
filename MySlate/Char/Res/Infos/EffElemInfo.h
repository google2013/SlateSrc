
#pragma once

#include "Engine/DataTable.h"
#include "EffElemInfo.generated.h"

USTRUCT(Blueprintable)
struct FEffElemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FEffElemInfo();
	virtual ~FEffElemInfo();

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mId;					//Ԫ��id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mResId;					//������Դid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mEffectType;	//��Ч����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FString		mBindPoint;				//�󶨹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		float		mDelayTime;			//��ʱʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mLoc;					//������Ϣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FRotator	mRotate;
};
