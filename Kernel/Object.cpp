#include "Object.h"
TObject::TObject(const char* AnObjectName):FObjectName(AnObjectName)
{
	FDebugMessage = "TObject ";
	FDebugMode = 0; // No debug
}

TObject::~TObject()
{

}

void TObject::Debug(void)
{

}

void TObject::ShowDebug(string AStr)
{
	if (FDebugMode>0)
	{
		cout<<FDebugMessage.c_str()<<" "<<AStr.c_str()<<endl;
	}
}

void TObject::ShowDebug(ostrstream AStream)
{
	if (FDebugMode)
	{
		cout << AStream.str();
	}	
}



