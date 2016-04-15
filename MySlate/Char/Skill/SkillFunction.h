// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillTypes.h"
#include "SkillFunction.generated.h"

class USkillTemplate;
class UPkMsg;

UCLASS()
class USkillFunction : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillFunction();
	virtual ~USkillFunction();


public:
	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		virtual void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		SetSkillTemplate(USkillTemplate* _skillTemp);

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		ShootBegin(); //�����ͷ�ǰ����

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		ShootEnd(); //���ܽ���������

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		int32			mSkillId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		USkillTemplate*	mSkillTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		ESkillType		mType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		UPkMsg*			mPkMsg; //���pk���ݣ����ﴴ����Ҫԭ�����ӵ����й����У����������������
};
