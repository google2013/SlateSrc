// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "MyAttachment.generated.h"

UCLASS(Blueprintable)
class USMyAttachment : public USkeletalMeshComponent
{
	GENERATED_UCLASS_BODY()
public:
	USMyAttachment();

	/** Attach point on pawn */
	UPROPERTY(EditDefaultsOnly, Category = Attachment)
		FName AttachPoint; //Ŀ��󶨵㣬�ṩ����ͼ�༭
};