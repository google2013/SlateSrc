
#pragma once

#include "MyAttachment.generated.h"

UCLASS(Blueprintable)
class USMyAttachment : public USkeletalMeshComponent
{
	GENERATED_UCLASS_BODY()
public:
	USMyAttachment();
	virtual ~USMyAttachment();

	/** Attach point on pawn */
	UPROPERTY(EditDefaultsOnly, Category = Attachment)
		FName AttachPoint; //目标绑定点，提供给蓝图编辑
};