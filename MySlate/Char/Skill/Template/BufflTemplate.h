// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/CommonHeader.h"

#include "BufflTemplate.generated.h"

class UAbsPkEvent;

UCLASS(Blueprintable)
class UBufflTemplate : public UObject
{
	GENERATED_BODY()

public:
	UBufflTemplate();
	virtual ~UBufflTemplate();
	virtual void BeginDestroy() override;

	TArray<UAbsPkEvent*>& GetAttrs();
	TArray<UAbsPkEvent*>& GetBeforePk();
	TArray<UAbsPkEvent*>& GetEndPk();

	void ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr);

public:
	TArray<UAbsPkEvent*> mAttrs;
	TArray<UAbsPkEvent*> mBeforePk;
	TArray<UAbsPkEvent*> mEndPk;

public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mBuffTime; //����ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		bool			mCanDisperse; //�Ƿ���ɢ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		bool			mCanAdd; //�ɷ�׺��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		bool			mDurable; //�Ƿ��ǳ�����buff
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBindPos; //��Ч�󶨵�

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mAttrsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndPkStr;
};
