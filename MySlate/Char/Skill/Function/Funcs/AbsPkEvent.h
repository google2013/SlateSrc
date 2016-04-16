// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbsPkEvent.generated.h"

class UPkMsg;
class UAbsBuff;

UCLASS()
class UAbsPkEvent : public UObject
{
	GENERATED_BODY()

public:
	struct PkInfo
	{
		PkInfo(int32 attId, int sId, int32 targetId, UAbsBuff* buff)
			:attUniqueId(attId)
			, skillId(sId)
			, targetUniqueId(targetId)
			, buffer(buff)
		{
		}

		uint32_t attUniqueId;	//buffer�ͷ���
		int skillId;			//�ͷ�buffer�ļ���
		uint32_t targetUniqueId;//buffer������
		UAbsBuff* buffer;	//buffer
	};

public:
	// Sets default values for this character's properties
	UAbsPkEvent();
	virtual ~UAbsPkEvent();

	virtual UAbsPkEvent* Clone();

	virtual void RunBeforeSkill(UPkMsg* msg) {}
	virtual void RunBeforePk(UPkMsg* msg) {}
	virtual void RunBeforeEvns(UPkMsg* msg) {}
	virtual void RunEndEvns(UPkMsg* msg) {}
	virtual void RunEndPk(UPkMsg* msg) {}
	virtual void RunEndSkill(UPkMsg* msg) {}

	virtual void Paser(const TArray<FString>& _params) {}//��������

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mKey;

};
