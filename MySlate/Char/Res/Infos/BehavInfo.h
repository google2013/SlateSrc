
#pragma once

#include "Engine/DataTable.h"
#include "../../Skill/SkillTypes.h"
#include "BehavInfo.generated.h"

USTRUCT(Blueprintable)
struct FEffElemInfo : public FTableRowBase		//��Ч
{
	GENERATED_USTRUCT_BODY()
public:
	FEffElemInfo();
	virtual ~FEffElemInfo();

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mResId;					//������Դid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;				//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EFollowType	mFollowType;			//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FString		mBindPoint;				//�󶨹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		float		mDelayTime;				//��ʱʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mLoc;					//������Ϣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FRotator	mRotate;
};

USTRUCT(Blueprintable)
struct FShakeInfo : public FTableRowBase		//��
{
	GENERATED_USTRUCT_BODY()
public:
	FShakeInfo();
	virtual ~FShakeInfo();

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mA;						//���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mW;						//���ٶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mTime;					//����ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		bool		mIsX;					//X����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;				//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		float		mDelayTime;				//��ʱʱ��
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

	//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mAtkEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mAtkShkVec;

	//�ӵ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mBltEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mBltShkVec;

	//�ܻ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mTarEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mTarShkVec;

	//����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mSceEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mSceShkVec;
};
