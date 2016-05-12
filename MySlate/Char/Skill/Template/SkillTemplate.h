
#pragma once

#include "../../../Common/CommonHeader.h"
#include "../SkillTypes.h"
#include "../Utils/CommonDef.h"
#include "../../Object/ObjInter.h"
#include "SkillTemplate.generated.h"

class UAbsPkEvent;
class UAbsFilter;

USTRUCT(Blueprintable)
struct FBulletMeshData
{
	GENERATED_USTRUCT_BODY()
public:
	FBulletMeshData() {}
	FBulletMeshData(int32 _resId, FVector _loc, FVector _scale, FRotator _rot);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletMeshData")
		int32			mResId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletMeshData")
		FVector			mLoc;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletMeshData")
		FVector			mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletMeshData")
		FRotator		mRotate;
};

UCLASS(BlueprintType)
class UBulletElem : public UObject, public IObjInterface //�ӵ�����
{
	GENERATED_BODY()
public:
	UBulletElem();
	virtual ~UBulletElem();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		int32			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		ELockedType		mLockedType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		FString			mAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		int32			mTolerance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		int32			mBulletSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		int32			mFlyDist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		FVector			mLoc;					//������Ϣ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		FVector			mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBulletElem")
		FRotator		mRotate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		TArray<FBulletMeshData>		mMeshVec;
};

UCLASS(Blueprintable, BlueprintType)
class USkillTemplate : public UObject
{
	GENERATED_BODY()

public:
	USkillTemplate();
	virtual ~USkillTemplate();
	virtual void BeginDestroy() override;

	void ReleaseArray(TArray<UAbsPkEvent*>& _arr);
public:
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	int32			GetId() { return mId; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetName() { return mName; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetDescr() { return mDescr; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	float			GetCoolDown() { return mCoolDown; }

public:
	//before�� ���Ǹ���������������������buff����������func
	const TArray<UAbsPkEvent*>& GetBeforeSkill();
	const TArray<UAbsPkEvent*>& GetBeforePk();
	const TArray<UAbsPkEvent*>& GetBeforeEvns();
	const TArray<UAbsPkEvent*>& GetEndEvns();
	const TArray<UAbsPkEvent*>& GetEndPk();
	const TArray<UAbsPkEvent*>& GetEndSkill();
	UAbsFilter*	GetFilter();

	void ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr);
	void ParseFilterStr(const FString& _filterStr);
public:
	TArray<UAbsPkEvent*> mBeforeSkill;
	TArray<UAbsPkEvent*> mBeforePk;
	TArray<UAbsPkEvent*> mBeforeEvns;
	TArray<UAbsPkEvent*> mEndEvns;
	TArray<UAbsPkEvent*> mEndPk;
	TArray<UAbsPkEvent*> mEndSkill;
	UAbsFilter*		mFilter;
public:
	//��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mAttackDist; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		ESkillType		mSkillType;	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		EAnimType		mAnimType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mBehavId; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mFilterStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforeSkillStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforeEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndPkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndSkillStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		UBulletElem*	mBltElem;
};
