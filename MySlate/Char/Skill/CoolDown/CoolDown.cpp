
#include "MySlate.h"
#include "CoolDown.h"

#include "../../MyChar.h"
#include "../Utils/SkillDataMgr.h"
#include "../Template/SkillTemplate.h"
#include "../Template/BufflTemplate.h"
#include "../SkillFunction.h"
#include "../../CharMgr.h"

UCoolDown::UCoolDown() : Super()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mSkillFunc = nullptr;
	mIsOK = true;
	mCDTime = 1.f;
	mTimer = 0.f;
	mRatio = 1.f;
	mOwnerChar = nullptr;
}

UCoolDown::~UCoolDown()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UCoolDown::~UCoolDown"));
}

void UCoolDown::BeginDestroy()
{
	if (mSkillFunc != nullptr)
	{
		mSkillFunc->RemoveFromRoot();
		mSkillFunc->ConditionalBeginDestroy();
		mSkillFunc = nullptr;
	}

	UE_LOG(SkillLogger, Warning, TEXT("--- UCoolDown::BeginDestroy, skillId:%d"), mSkillId);
	Super::BeginDestroy();
}

void UCoolDown::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = mSkillTemplate->mId;
	mCDTime = (float)mSkillTemplate->mCoolDown;
	mTimer = mCDTime;
	mIsOK = true;

	USkillFunction* skillFunc = GetSkillFunc();
	if (skillFunc)
	{
		skillFunc->SetSkillTemplate(_skillTemp);
	}
}

USkillFunction* UCoolDown::GetSkillFunc()
{
	if (mSkillFunc == nullptr)
	{
		USkillFunction* skillFunc = NewObject<USkillFunction>(UCoolDown::StaticClass()); //����USkillFunction����UCoolDown����
		skillFunc->AddToRoot();
		skillFunc->SetCD(this);//ʹ�ü���ʱ��Ҫ�������cd���ʶ���thisָ��
		mSkillFunc = skillFunc;
	}
	return mSkillFunc;
}

void UCoolDown::SetChar(AMyChar* _char)
{
	mOwnerChar = _char;
	if (mOwnerChar != nullptr)
	{
		mCDFinishDlg.Unbind();
		mCDFinishDlg.BindUObject(mOwnerChar, &AMyChar::OnCDFinish);

		USkillFunction* skillFunc = GetSkillFunc();
		if (skillFunc)
		{
			skillFunc->SetAttacker(mOwnerChar);
		}
	}
}

void UCoolDown::Restart()
{
	mTimer = 0.f;
	mIsOK = false;
}

void UCoolDown::Tick(float DeltaTime)
{
	if (!mIsOK)
	{
		mTimer += DeltaTime * mRatio;
		if (mTimer >= mCDTime)
		{
			mTimer = mCDTime;
			mIsOK = true;
			mCDFinishDlg.ExecuteIfBound(this); //cd��֪ͨchar�������ͷż�����
		}
	}
	else
		mTimer = mCDTime;
}
