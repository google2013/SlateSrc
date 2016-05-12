
#pragma once

#include "../SkillTypes.h"
#include "../../Object/ObjInter.h"
#include "PkProcess.generated.h"

class UPkMsg;
class UDamageInfo;
class AMyChar;

DECLARE_DELEGATE_OneParam(FPkOverDlg, TArray<UDamageInfo*>);
DECLARE_DELEGATE_OneParam(RunSkillBeforeCallBack, UPkMsg*);

UCLASS()
class UDamageInfo : public UObject, public IObjInterface
{
	GENERATED_BODY()

public:
	UDamageInfo();
	virtual ~UDamageInfo();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

	int32		mTargetId;			//Ŀ��Ψһid
	AMyChar*	mTarget;		//Ŀ��
	ESkillAtkType	type;	//�˺����� (�����˺���ħ���˺������ơ���Ѫ)
	float		mValue;				//�˺�ֵ
	bool		mIsDodge;			//����
	bool		mIsCrit;			//����
	bool		mIsPhyDmgImmunity;	//��������
	bool		mIsMagDmgImmunity;	//ħ������
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
	void PkDamage(TArray<UDamageInfo*> _dmgVec);

private:
	UPkMsg* mPkMsg;
	FPkOverDlg mCallBack; //������Ļص�
	RunSkillBeforeCallBack m_runSkillBeforeCallBack;
};
