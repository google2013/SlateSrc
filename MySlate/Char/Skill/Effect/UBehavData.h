
#pragma once

#include "UBehavData.generated.h"

UENUM()
enum class ESkillEffectType : uint8 //��Ч����
{
	SelfFollow = 0,
	SelfUnfollow,
	TargetFollow,
	TargetUnfollow,
	Bullet,
	SceneCamera,
	Count,
};

UCLASS()
class UEffDataElem : public UObject //��ЧԪ��
{
	GENERATED_BODY()
public:
	UEffDataElem();
	virtual ~UEffDataElem();
	virtual void BeginDestroy() override;

	int32		mId;					//��Чid
	ESkillEffectType	mEffectType;	//��Ч����
	FString		mBindPoint;				//�󶨹���
	float		mDelayTime;			//��ʱʱ��
	FVector		mLoc;					//������Ϣ
	FVector		mScale;
	FRotator	mRotate;
};

UCLASS()
class UBehavData : public UObject //��Ч����
{
	GENERATED_BODY()
public:
	UBehavData();
	virtual ~UBehavData();
	virtual void BeginDestroy() override;

	void Tick(float DeltaTime);
	TArray<UEffDataElem*>&	GetEffElems() { return mEffElems; }

	void loadEffecs();
public:
	int32		mId;//��Чid
	TArray<UEffDataElem*>	mEffElems; //��Ч��
};
