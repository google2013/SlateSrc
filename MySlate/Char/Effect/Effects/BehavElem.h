
#pragma once

#include "../../Skill/SkillTypes.h"
#include "BehavElem.generated.h"

class UBehavElem;
class IBehavInterface;

DECLARE_DELEGATE_OneParam(FBehavElemDlg, UBehavElem*);

UENUM()
enum class EElemState : uint8 //��Ч״̬
{
	Idle = 0,
	Start,
	Delay,
	Ticking,
	Over,
};

UCLASS(BlueprintType)
class UBehavElem : public UObject //��Ԫ�أ�����Ч�༭���༭������
{
	GENERATED_BODY()
public:
	UBehavElem();
	virtual ~UBehavElem();
	virtual void BeginDestroy() override;

	virtual void Tick(float DeltaTime);
	virtual void Start();
	virtual void SetActor(IBehavInterface* _actor);

	void AddOverDlg(FBehavElemDlg _dlg);
	void MyDestroy(bool _needNotify = true);

public:
	int32		mGroupId;		//��Ч��id��ÿһ��behav������һ��mGroupId���Ա�����ɾ��

protected:
	IBehavInterface*	mTarget;				//����
	float		mDelayer;
	float		mDelayTime;
	EElemState	mState;
	FBehavElemDlg	mOverDlg;
};

UCLASS(BlueprintType)
class UShakeElem : public UBehavElem //��Ԫ�أ�����Ч�༭���༭������
{
	GENERATED_BODY()
public:
	UShakeElem();
	virtual ~UShakeElem();
	virtual void BeginDestroy() override;

	virtual void Tick(float DeltaTime) override;
	virtual void Start() override;

	UShakeElem* Clone();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mA;						//���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mW;						//���ٶ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mTime;					//����ʱ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		bool		mIsX;					//X����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;				//������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mDelayTime;				//��ʱʱ��

private:
		AActor*		mTarget;				//����
		FVector		mLoc;
		FVector		mDtLoc;
		float		mRunTimer;
};

UCLASS(BlueprintType)
class UEffDataElem : public UBehavElem //��ЧԪ�أ�����Ч�༭���༭������
{
	GENERATED_BODY()
public:
	UEffDataElem();
	virtual ~UEffDataElem();
	virtual void BeginDestroy() override;
	
	virtual void Tick(float DeltaTime) override;
	virtual void Start() override;

	void SetData(UParticleSystemComponent* _psComp);
	void OnCompleted(UParticleSystemComponent* _psComp);
	UEffDataElem* Clone();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		int32		mResId;					//������Դid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EFollowType	mFollowType;
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

private:
	UParticleSystemComponent*	mPsComp;
};