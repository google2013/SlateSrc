// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillTypes.h"
#include "SkillFunction.generated.h"

class USkillTemplate;
class UPkMsg;
class AMyBullet;
class AMyChar;
class UCoolDown;

UCLASS()
class USkillFunction : public UObject
{
	GENERATED_BODY()

public:
	USkillFunction();
	virtual ~USkillFunction();
	virtual void BeginDestroy() override;

public:
	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		virtual void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		SetSkillTemplate(USkillTemplate* _skillTemp);

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		USkillTemplate*	GetSkillTemplate() const { return mSkillTemplate; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		UseSkill(int32 _targetId, const FVector& _targetLoc);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		CanAttack();

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		CancelSkill();

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		SkillBegin(); //�����ͷ�ǰ����, ���� ˲���ƶ� -> ����

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		BulletCreate(); //�ӵ�����

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		BulletShoot(); //�ӵ�����

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		SkillEnd(); //���ܽ���������

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		ReleaseData();

	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		void		SetAttacker(AMyChar* _char) { mAttacker = _char; }

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		void		SetCD(UCoolDown* _cd) { mOwnerCD = _cd; }

	void	SetPkMsgNull() { mPkMsg = nullptr; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		AMyChar*		mAttacker;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		int32			mTargetId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		FVector			mTargetLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		int32			mSkillId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		USkillTemplate*	mSkillTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		ESkillType		mType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		UPkMsg*			mPkMsg; //���pk���ݣ����ﴴ����Ҫԭ�����ӵ����й����У����������������

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		AMyBullet*		mBullet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		UCoolDown*		mOwnerCD;

private:
	bool	mCanAttack;
	bool	mMoving;
};
