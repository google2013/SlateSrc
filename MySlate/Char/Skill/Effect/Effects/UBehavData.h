
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

UCLASS(BlueprintType)
class UEffDataElem : public UObject //��ЧԪ�أ�����Ч�༭���༭������
{
	GENERATED_BODY()
public:
	UEffDataElem();
	virtual ~UEffDataElem();
	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		int32		mId;					//Ԫ��id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		int32		mResId;					//������Դid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		ESkillEffectType	mEffectType;	//��Ч����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FString		mBindPoint;				//�󶨹���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mDelayTime;			//��ʱʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FVector		mLoc;					//������Ϣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FVector		mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		int32		mId;//��Чid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UEffDataElem*>	mEffElems; //��Ч��
};
