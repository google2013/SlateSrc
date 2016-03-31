// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
//#include "TestChar.h"
#include "MyChar.generated.h"

DECLARE_DELEGATE_OneParam(FMyDelegate1, int32);
//c++��bp���ʹ�õĴ�����������ֺ꣬�������������֣�abcΪ��ͼ���¼����β�
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FMyDelegate2, int32, abc);

class Test;
class USMyAttachment;
class UCoolDownComp;
class UCoolDown;
class UMyCharDataComp;

UCLASS()
class AMyChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyChar();
	virtual ~AMyChar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//---------- ����delegate�ĸ���bind
	void testDelegateUObject(int32 _num);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
	void runAllDelegate();

	TSharedPtr<Test> testSp;

	FMyDelegate1 mMyDelegate1;
	FMyDelegate1 mMyDelegate2;
	FMyDelegate1 mMyDelegate3;
	FMyDelegate1 mMyDelegate4;
	FMyDelegate1 mMyDelegate5;

	//---------- ���Ե���ָ����ͼ�������������� 
	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void runBpFunc(FString _funcName, FString _arg1, int32 _arg2);

	//---------- ����async load
	void TestAsyncLoad();

	//---------- ����ufunction
	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void TestFunction(int32 _num, FString _str);

	//---------- ������ͼ���մ���Ĺ㲥�¼�
	//��������ΪBlueprintAssignable��ֻ����ͼ���¼�
	UPROPERTY(BlueprintAssignable, Category = "MyChar")
		FMyDelegate2 OnMyDelegate2;

	//---------- ���԰�����
	/** default weapon for the char */
	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void SetWeapon1Class(TSubclassOf<USMyAttachment> InWeapon);

	UPROPERTY(EditAnywhere, Category = "MyChar")
		TSubclassOf<USMyAttachment> Weapon1Class;

	UPROPERTY(EditAnywhere, Category = "MyChar")
		USMyAttachment* Weapon1;


	UPROPERTY(EditDefaultsOnly, Category = "MyChar")
		UAnimMontage*		mMon1;

	//---------- �����Ƿ���ʵ��
		uint32 hasOnDeathImplementEvent : 1;

	UFUNCTION(BlueprintImplementableEvent, Category = "MyBehavior")
		void OnDeath(const FString& _str, int32 _num);

public:
	void OnCDFinish(UCoolDown* _cd);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UCoolDownComp*		mCDComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UMyCharDataComp*	mDataComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		int32				mUsingSkill;

public:

};
