
#pragma once

#include "ObjInter.generated.h"

class UObjMgr;

UINTERFACE()
class UObjInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IObjInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	IObjInterface();

	virtual void Reset() = 0;	//����ӿڣ�Ҫ�����������д
	virtual void SetObj(UObject* _obj); 
	virtual void Recycle();

private:
	UObjMgr*	mObjMgr;	//��������
	UObject*	mOwnObj;	//��������
};