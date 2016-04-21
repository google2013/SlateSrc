// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SkillTypes.h"
#include "PkPorcess.generated.h"

class UPkMsg;
struct FDamageInfo;

DECLARE_DELEGATE_OneParam(FPkOverDlg, TArray<FDamageInfo>&);
DECLARE_DELEGATE_OneParam(RunSkillBeforeCallBack, UPkMsg*);

USTRUCT()
struct FDamageInfo
{
	GENERATED_BODY()

public:
	FDamageInfo()
	{
		mTargetId = 0;
		mValue = 0.f;
		mIsDodge = false;
		mIsCrit = false;
		mIsPhyDmgImmunity = false;
		mIsMagDmgImmunity = false;
	}

	int32	mTargetId;//Ŀ��Ψһid
	ESkillAttackType	type;		//�˺����� (�����˺���ħ���˺������ơ���Ѫ)
	float	mValue;				//�˺�ֵ
	bool	mIsDodge;			//����
	bool	mIsCrit;			//����
	bool	mIsPhyDmgImmunity;	//��������
	bool	mIsMagDmgImmunity;	//ħ������
};

UCLASS()
class UPkPorcess : public UObject
{
	GENERATED_BODY()
public:
	UPkPorcess();
	virtual ~UPkPorcess();
	virtual void BeginDestroy() override;

public:
	void SetMsg(UPkMsg* _pkMsg);
	void Run();
	FPkOverDlg&	GetPkOverDlg() { return mCallBack; }

private:
	bool CheckCanPk();//�ж��ܷ�pk
	void Filter();//ѡȡ���������߼�
	void RunEndEvns(); 

	void PkLogic();// pk�߼����㣬֮ǰ�ķ����ѰѶ������ĵ�ֵ��ã����ﲻ���ټ��㣬ֱ�ӽ����߼����㼴��
	void RunEndPk();//
	void PkPrice();//�������䣬��֯Э�飬�Ƿ�ս���ѽ���

private:
	UPkMsg* mPkMsg;
	FPkOverDlg mCallBack; //������Ļص�
	RunSkillBeforeCallBack m_runSkillBeforeCallBack;
};
