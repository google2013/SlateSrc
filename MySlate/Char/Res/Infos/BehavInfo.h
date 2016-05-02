
#pragma once

#include "Engine/DataTable.h"
#include "BehavInfo.generated.h"

USTRUCT(Blueprintable)
struct FBehavInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FBehavInfo();
	virtual ~FBehavInfo();

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		int32		mId;//����id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		FString		mEffIdsStr;//��Ч��
};
