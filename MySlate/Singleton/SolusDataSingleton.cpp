#include "MySlate.h"
#include "SolusDataSingleton.h"

USolusDataSingleton::USolusDataSingleton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "I am Mr. Yang"; //��ʼ��������������������������ͼ�г�ʼ��
	SolusEssentialVector = FVector(900, 800, 700);
}