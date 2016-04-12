// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tickable.h"
#include "Char/Skill/SkillTypes.h"

#include "CoolDownComp.generated.h"

class UCoolDown;
class AMyChar;

UCLASS()
class UCoolDownComp : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's 
	virtual ~UCoolDownComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //�����new��ʱ����������
	virtual void BeginDestroy() override; //������gc��ʱ����ã���������������
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// End UActorComponent Interface.

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		SetOwner(AMyChar* _owner) { mOwner = _owner; }

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		CreateCD(int32 _skillId, TSubclassOf<UCoolDown> _class); //���԰���ͼ�ഫ����

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		UseSkill(UCoolDown* _skill, int32 _targetId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		RestartCD(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		RemoveCDById(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		AddCD(int32 _skillId, bool _isRestartCD);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComp")
		TArray<UCoolDown*>		mCDArr;
	TArray<UCoolDown*>		mCDArr222;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComp")
		AMyChar*				mOwner;

};