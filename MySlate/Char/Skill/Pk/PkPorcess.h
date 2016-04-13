// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SkillTypes.h"
#include "PkPorcess.generated.h"

class UPkMsg;
struct DamageInfo;

DECLARE_DELEGATE_OneParam(PkProcessCallBack, TArray<DamageInfo>&);
DECLARE_DELEGATE_OneParam(RunSkillBeforeCallBack, UPkMsg*);

struct DamageInfo
{
	int32 targetUniqueId = 0;//Ŀ��Ψһid
	ESkillAttackType type;				//�˺����� (�����˺���ħ���˺������ơ���Ѫ)
	float value = 0;			//�˺�ֵ
	bool isDodge = false;		//����
	bool isCrit = false;		//����
	bool isPhyDmgImmunity = false;//��������
	bool isMagDmgImmunity = false;//ħ������
};

UCLASS()
class UPkPorcess : public UObject
{
	GENERATED_BODY()
public:


public:
	UPkPorcess();
	virtual ~UPkPorcess();

public:
	void SetMsg(UPkMsg* _pkMsg);
	void Run();

private:
	bool CheckCanPk();//�ж��ܷ�pk
	void FilterVS();//ѡȡ���������߼�

	void RunBeforePk();// ��һ��ѭ�� ����buffǰ���¼� һ�����ڷż���ǰҪbuff
	void RunBeforeSkill(); //pk�߼����ǰ�����߼�
	void PkLogic();// pk�߼����㣬֮ǰ�ķ����ѰѶ������ĵ�ֵ��ã����ﲻ���ټ��㣬ֱ�ӽ����߼����㼴��
	void RunEndSkill();//pk�߼���ɺ����߼�������Ѫ��������
	void RunEndPk();//������buff�����¼�
	void PkPrice();//�������䣬��֯Э�飬�Ƿ�ս���ѽ���

private:
	UPkMsg* mPkMsg;
	PkProcessCallBack m_callBack;
	RunSkillBeforeCallBack m_runSkillBeforeCallBack;
};
