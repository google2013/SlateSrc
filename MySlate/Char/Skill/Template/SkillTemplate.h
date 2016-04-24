// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/CommonHeader.h"
#include "Char/Skill/SkillTypes.h"
#include "../Utils/CommonDef.h"

#include "SkillTemplate.generated.h"

class UAbsPkEvent;
class UAbsFilter;

UENUM()
enum class EAnimType : uint8 //���ܶ���
{
	None = 0,
	Skill_1,
	Skill_2,
	Skill_3,
	Skill_4,
	Skill_5,
	Skill_6,
	Skill_7,
	Injure_1,
	Injure_2,
	Victory_1,
	Victory_2,
	Victory_3,
	Count,
};

UCLASS(Blueprintable, BlueprintType)
class USkillTemplate : public UObject
{
	GENERATED_BODY()

public:
	USkillTemplate();
	virtual ~USkillTemplate();
	virtual void BeginDestroy() override;

	void ReleaseArray(TArray<UAbsPkEvent*>& _arr);
public:
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	int32			GetId() { return mId; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetName() { return mName; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetDescr() { return mDescr; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	float			GetCoolDown() { return mCoolDown; }

public:
	//before�� ���Ǹ���������������������buff����������func
	const TArray<UAbsPkEvent*>& GetBeforeSkill();
	const TArray<UAbsPkEvent*>& GetBeforePk();
	const TArray<UAbsPkEvent*>& GetBeforeEvns();
	const TArray<UAbsPkEvent*>& GetEndEvns();
	const TArray<UAbsPkEvent*>& GetEndPk();
	const TArray<UAbsPkEvent*>& GetEndSkill();
	UAbsFilter*	GetFilter();

	void ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr);
	void ParseFilterStr(const FString& _filterStr);
public:
	TArray<UAbsPkEvent*> mBeforeSkill;
	TArray<UAbsPkEvent*> mBeforePk;
	TArray<UAbsPkEvent*> mBeforeEvns;
	TArray<UAbsPkEvent*> mEndEvns;
	TArray<UAbsPkEvent*> mEndPk;
	TArray<UAbsPkEvent*> mEndSkill;
	UAbsFilter*		mFilter;
public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		ELockedType		mLockedType; //TODO: �������� ���� ��or��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mAttackDist; //TODO: ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mTolerance; //TODO: �������� //�ӵ���targetLoc���������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mBulletSpeed; //TODO: ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mFlyDist; //TODO: �������� �ӵ����о���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		ESkillType		mSkillType;	//TODO: ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mAttachPoint;//TODO: �������� �ӵ��󶨵�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		EAnimType		mAnimType;//TODO: �������� ��ͬ���Ͷ����Ĳ�ͬ����ö��

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mFilterStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforeSkillStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforeEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndPkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndSkillStr;
};
