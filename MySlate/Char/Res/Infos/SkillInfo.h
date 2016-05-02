
#pragma once

#include "Engine/DataTable.h"
#include "SkillInfo.generated.h"

USTRUCT(Blueprintable)
struct FSkillInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FSkillInfo();
	virtual ~FSkillInfo();

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mLockedType; //TODO: �������� ���� ��or��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mAttackDist; //TODO: ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mTolerance; //TODO: �������� //�ӵ���targetLoc���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mBulletSpeed; //TODO: ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mFlyDist; //TODO: �������� �ӵ����о���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mSkillType;	//TODO: ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mAttachPoint;//TODO: �������� �ӵ��󶨵�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mAnimType;//TODO: �������� ��ͬ���Ͷ����Ĳ�ͬ����ö��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mFilterStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mBeforeSkillStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mBeforeEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mEndEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mEndPkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mEndSkillStr;
};
