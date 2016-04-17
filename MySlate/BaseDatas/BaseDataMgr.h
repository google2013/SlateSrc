/*
�������ݹ�����
*/
#pragma once

#include "Common/ISingleton.h"
#include "BaseDataMgr.generated.h"

class UCharData;

UCLASS()
class UBaseDataMgr : public UObject, public USingleton<UBaseDataMgr>
{
	GENERATED_BODY()

public:
	UBaseDataMgr();
	virtual ~UBaseDataMgr();

	void InitFakeData();
	void LoadCharData();

public:
	UCharData*		GetCharData(int32 _id);
public:
	TMap<int32, UCharData*> mCharDataMap;
};
