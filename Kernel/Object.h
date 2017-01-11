#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <stdio.h>
#include <string>
#include <strstream>
#include "Global.h"
#include <Message.h>
#include <iostream>
//#include "GlobalVar.h"

using namespace std;
class TObject 
{
public:
	TObject(const char* AnObjectName);
	virtual ~TObject();
	virtual void Debug(void);
	void ShowDebug(string AStr);
	void ShowDebug(ostrstream AStream);
// Save and Load
	virtual BMessage *SaveData(){return NULL;};
	virtual bool LoadData(BMessage *AMessage, BHandler *AGuiHandler){return false;}; 
	
protected:
	string FObjectName;
	// For Debugging Only!
	int FDebugMode;
	string FDebugMessage;
	
};
#endif
