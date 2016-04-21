// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameTypes.h"
#include "MyBaseComp.h"
#include "MyCharDataComp.generated.h"

class UCoolDown;
class AMyChar;
class UFightData;
class UCharData;

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
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void DestroyComponent(bool bPromoteChildren = false);
	// End UActorComponent Interface.

	void		SetFightData(UFightData* _data) { mFightData = _data; }
	UFightData*	GetFigthData() const { return mFightData; }

	void		SetCharData(UCharData* _data);
	UCharData*	GetCharhData() const { return mCharData; }

	const ETeam& GetTeamType() const { return mTeam; }

	void		SetHealth(float _value) { mHealth = _value; }
	float		GetHealth() const { return mHealth; }
	void		SetHealthMax(float _value) { mHealthMax = _value; }
	float		GetHealthMax() const { return mHealthMax; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		UFightData*		mFightData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		UCharData*		mCharData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		EGroup			mGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		ETeam			mTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		float			mHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		float			mHealthMax;
};