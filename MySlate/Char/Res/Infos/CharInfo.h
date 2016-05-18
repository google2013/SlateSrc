
#pragma once

#include "Engine/DataTable.h"
#include "CharInfo.generated.h"

USTRUCT()
struct FFightDataInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FFightDataInfo();
	virtual ~FFightDataInfo();

public:
	//ԭʼ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		float		mAttackPhy;		//������

public:
	//�ɳ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		int			mLv;			//�ȼ�
};

USTRUCT(Blueprintable)
struct FCharInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FCharInfo();
	virtual ~FCharInfo();

public:
	//��������
		int32		mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		FString		mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		FString		mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		float		mHeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		float		mHeathMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		float		mWarnRange;

	//----------- ս������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		FFightDataInfo	mFightInfo;


};
