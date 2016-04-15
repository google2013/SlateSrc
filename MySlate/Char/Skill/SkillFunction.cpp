// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

#include "Template/SkillTemplate.h"
#include "Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"

// Sets default values
USkillFunction::USkillFunction() : Super()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
	mBullet = nullptr;
	mAttackerId = 0;
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction:%d"), mSkillId);
	if (mPkMsg)
	{
		mPkMsg->RemoveFromRoot();
	}
}

void USkillFunction::Tick(float DeltaSeconds)
{

}

void USkillFunction::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = _skillTemp->mId;
	mType = _skillTemp->mSkillType;

}

void USkillFunction::SkillBegin()
{
	//TODO: �����������ݣ����м���ǰ��func

	UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
	pkMsg->AddToRoot();
	FSetNullDlg dlg;
	dlg.BindUObject(this, &USkillFunction::SetDataNull);
	pkMsg->SetNullDlg(dlg);

}



void USkillFunction::BulletCreate()
{
	AMyChar* attacker = mAttackerId > 0 ? UCharMgr::GetInstance()->GetChar(mAttackerId) : nullptr;
	if (attacker)
	{
		 //�����ӵ������
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		mBullet = GetWorld()->SpawnActor<AMyBullet>(attacker->BulletClass, attacker->GetActorLocation(), attacker->GetActorRotation(), SpawnInfo);
		bullet->SetAttacker(mAttackerId);
	}
}

void USkillFunction::BulletShoot()
{
	if (mBullet != nullptr)
	{
		//����󶨵㣬��Ŀ�����
	}
}

void USkillFunction::SkillEnd()
{

}

void USkillFunction::SetDataNull()
{
	mPkMsg = nullptr;//�����ط�����֪ͨһ�������ֹ����ʱҰָ�뱼��
}

