// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tickable.h"
#include "Char/Skill/SkillTypes.h"

#include "Char/Comp/MyBaseComp.h"
#include "CoolDownComp.generated.h"

class UCoolDown;
class AMyChar;

UCLASS()
class UCoolDownComp : public UMyBaseComp
{
	GENERATED_BODY()

public:
	// Sets default values for this character's 
	UCoolDownComp();
	virtual ~UCoolDownComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //组件被new的时候立即调用
	virtual void BeginDestroy() override; //引擎在gc的时候调用，并不是立即调用
	// End UActorComponent Interface.

	void MyTick(float DeltaTime);


	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		SetOwner(AMyChar* _owner) { mOwner = _owner; }

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		CreateCD(int32 _skillId, TSubclassOf<UCoolDown> _class); //可以把蓝图类传进来

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		USkillFunction*	CanUseSkill(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		RestartCD(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		RemoveCDById(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComp")
		void		AddCD(int32 _skillId, bool _isRestartCD);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComp")
		TArray<UCoolDown*>		mCDArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComp")
		AMyChar*				mOwner;

};