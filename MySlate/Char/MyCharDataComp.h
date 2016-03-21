// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyCharDataComp.generated.h"

class UCoolDown;
class AMyChar;

UCLASS()
class UMyCharDataComp : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's 
	virtual ~UMyCharDataComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //�����new��ʱ����������
	virtual void BeginDestroy() override; //������gc��ʱ����ã���������������
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// End UActorComponent Interface.
};