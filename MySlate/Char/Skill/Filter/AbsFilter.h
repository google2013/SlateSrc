#pragma once

#include "../SkillTypes.h"
#include "AbsFilter.generated.h"

/*
һ�㶨�壺
float		mValue; //��ֵ
int32		mOwner; //������ -- 1:�����ߣ�-1:�ܻ���
int32		mLimitId; //��������
*/

class AMyChar;
class UPkMsg;

UCLASS()
class UAbsFilter : public UObject
{
	GENERATED_BODY()

public:
	UAbsFilter();
	virtual ~UAbsFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* _msg, EFilterType _filterType = EFilterType::Locked, float _radius = 0.f, const FVector& _boxSize = FVector::ZeroVector); //���ǿ�ѡactor
	virtual UAbsFilter* Clone() { return nullptr; }
	virtual void Parser(const TArray<FString>& _params) {}//��������
	virtual void DebugDraw(const FVector& _start, const TArray<AMyChar*>& _targets);

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
		FString		mKey;
		int32		mCount; //��������
		ESelectType	mSelectType;
		TArray<AMyChar*>	mDestChars; //Ŀ�꼯��
};
