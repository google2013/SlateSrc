// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameTypes.h"
#include "MyBaseComp.h"
#include "MyCharDataComp.generated.h"

class UCoolDown;
class AMyChar;

UCLASS()
class UMyCharDataComp : public UMyBaseComp
{
	GENERATED_BODY()

public:
	UMyCharDataComp();
	virtual ~UMyCharDataComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //�����new��ʱ����������
	virtual void BeginDestroy() override; //������gc��ʱ����ã���������������
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// End UActorComponent Interface.

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		EGroup			mGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		ETeam			mTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		float			mHealth;
};