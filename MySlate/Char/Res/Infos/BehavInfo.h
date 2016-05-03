
#pragma once

#include "Engine/DataTable.h"
#include "../../Skill/SkillTypes.h"
#include "BehavInfo.generated.h"

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
		int32		mResId;					//������Դid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		ESkillEffectType		mEffectType;	//��Ч����
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

USTRUCT(Blueprintable)
struct FBehavInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FBehavInfo();
	virtual ~FBehavInfo();

public:
	//��������
		int32		mId;//����id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mEffectVec;
};
