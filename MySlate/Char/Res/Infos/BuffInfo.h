
#pragma once

#include "Engine/DataTable.h"
#include "BuffInfo.generated.h"

USTRUCT(Blueprintable)
struct FBuffInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FBuffInfo();
	virtual ~FBuffInfo();

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mBuffTime; //����ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		bool			mCanDisperse; //�Ƿ���ɢ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		bool			mCanAdd; //�ɷ�׺��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mInterType; //buff������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		float			mInterTime; //buff������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mBehavDataId; //��������id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mAttrsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mEndPkStr;
};
