
#pragma once

#include "../SkillTypes.h"
#include "../../Object/ObjInter.h"
#include "PkProcess.generated.h"

class UPkMsg;
struct FDamageInfo;
class AMyChar;

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
		mTarget = nullptr;
		mValue = 0.f;
		mIsDodge = false;
		mIsCrit = false;
		mIsPhyDmgImmunity = false;
		mIsMagDmgImmunity = false;
	}

	int32	mTargetId;			//Ŀ��Ψһid
	AMyChar*	mTarget;		//Ŀ��
	ESkillAttackType	type;	//�˺����� (�����˺���ħ���˺������ơ���Ѫ)
	float	mValue;				//�˺�ֵ
	bool	mIsDodge;			//����
	bool	mIsCrit;			//����
	bool	mIsPhyDmgImmunity;	//��������
	bool	mIsMagDmgImmunity;	//ħ������
};

UCLASS()
class UPkProcess : public UObject, public IObjInterface
{
	GENERATED_BODY()
public:
	UPkProcess();
	virtual ~UPkProcess();
	virtual void BeginDestroy() override;
	virtual void Reset() override;
	virtual void Recycle() override;

public:
	void SetMsg(UPkMsg* _pkMsg);
	void Run();
	FPkOverDlg&	GetPkOverDlg() { return mCallBack; }
	void SetPkOverDlg(const FPkOverDlg& _dlg) { mCallBack = _dlg; }

private:
	bool CheckCanPk();//�ж��ܷ�pk
	void Filter();//ѡȡ���������߼�
	void RunEndEvns(); 

	void PkLogicEvns();// pk�߼����㣬֮ǰ�ķ����ѰѶ������ĵ�ֵ��ã����ﲻ���ټ��㣬ֱ�ӽ����߼����㼴��
	void RunEndPk();//
	void PkPrice();//�������䣬��֯Э�飬�Ƿ�ս���ѽ���

private:
	UPkMsg* mPkMsg;
	FPkOverDlg mCallBack; //������Ļص�
	RunSkillBeforeCallBack m_runSkillBeforeCallBack;
};
