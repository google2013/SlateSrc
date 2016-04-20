// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tickable.h"

#include "BuffMgr.generated.h"

class UPkMsg;
class AMyChar;

UCLASS()
class UBuffMgr : public UObject, public FTickableGameObject, public USingleton<UBuffMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UBuffMgr();
	virtual ~UBuffMgr();

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

	//=== buffer���� begin ===
	void RunBeforePkBuffs(int32 _charId, UPkMsg* msg);//bufferǰ��
	void RunEndPkBuffs(int32 _charId, UPkMsg* msg);//buffer����
	//=== buffer���� end   ===

	UFUNCTION(BlueprintCallable, Category = "UBuffMgr")
		void RemoveBuff(int32 _charId);

	UFUNCTION(BlueprintCallable, Category = "UBuffMgr")
		void CharDeathNotify(AMyChar* _char);

public:
	

private:
};
