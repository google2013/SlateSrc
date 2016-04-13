// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "FunctionFactory.h"
#include "../Utils/CommonDef.h"
#include "Base/AbsPkEvent.h"
#include "Funcs/PhyAttack.h"
#include "../Filter/AbsFilter.h"
#include "../Filter/LockFilter.h"
#include "../Filter/CircleFilter.h"

DECLARE_LOG_CATEGORY_EXTERN(UFunctionFactoryLogger, Log, All);
DEFINE_LOG_CATEGORY(UFunctionFactoryLogger)

// Sets default values
UFunctionFactory::UFunctionFactory() : Super()
{

}

UFunctionFactory::~UFunctionFactory()
{
	//���ݶ��ظ�gc
	for (auto iter = mFunctionMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
	}
	mFunctionMap.Empty();
	
	for (auto iter = mFilterMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
	}
	mFilterMap.Empty();
}

//����ע��ģ��
void UFunctionFactory::InitFuncAndFilters()
{
	//------------ ѡ�� Start ------------
	registerFilter(ULockFilter::CreateFilter(Filter_Lock));
	registerFilter(UCircleFilter::CreateFilter(Filter_Circle));
	//------------ ѡ�� End ------------

	//------------ ���� Start ------------
	registerFunction(UPhyAttack::CreateFunction(Func_Phyattack));
	//------------ ���� End ------------
}

void UFunctionFactory::registerFunction(UAbsPkEvent* _object)
{
	FString key = _object->GetKey();
	UAbsPkEvent** func = mFunctionMap.Find(key);
	if (func != nullptr)
	{
		return;
	}
	_object->AddToRoot();
	mFunctionMap.Add(key, _object);
}

void UFunctionFactory::registerFilter(UAbsFilter* _object)
{
	FString key = _object->GetKey();
	UAbsFilter** filter = mFilterMap.Find(key);
	if (filter != nullptr)
	{
		return;
	}
	_object->AddToRoot();
	mFilterMap.Add(key, _object);
}

UAbsFilter* UFunctionFactory::createFilter(const FString& _str)
{
	FString paramStr = _str.ToLower();
	TArray<FString> params;
	paramStr.ParseIntoArray(params, Split_Line, true);
	if (params.Num() > 0)
	{
		FString clsName = params[0];
		UAbsFilter** filter = mFilterMap.Find(clsName);
		if (filter == nullptr)
		{
			return nullptr;
		}

		*filter = (*filter)->Clone();
		if (*filter == nullptr)
		{
			return nullptr;
		}

		params.RemoveAt(0); //�Ƴ�������
		(*filter)->Paser(params);
		return *filter;
	}

	return nullptr;
}

UAbsPkEvent* UFunctionFactory::createFunction(const FString& _str)
{

	return nullptr;
}
