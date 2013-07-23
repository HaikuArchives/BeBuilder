#ifndef __COMPONENTLIST_H__
#define __COMPONENTLIST_H__

#include <map>
#include <string>
#include <stdio.h>
#include "Component.h"
#include "Object.h"
#include <List.h>
#include <Message.h>
typedef map<string,TComponent *>::const_iterator TComponentCI;

using namespace std;
class TComponentList : public TObject  
{
public:
	TComponentList(TComponent *AParentComponent);
	virtual ~TComponentList();
	void AddComponent(TComponent *AComponent);
	void AddComponent(string AComponentName, string AClassName);
	void RemoveComponent(TComponent *AComponent);
	void RemoveComponent(string AComponentName);
	bool RemoveAllChild(void);
	
//	void RemoveComponent(string AComponentName, string AClassName);

	bool SetLastChildAdded(TComponent *AComponent);
	TComponent *GetLastChildAdded(void);
	TComponent *GetComponent(const char * AComponentName);
	TComponent *NextComponent(bool FromBeginning);
	void Debug(void);
	BMessage *SaveData();
	bool LoadData(BMessage *AMessage, BHandler *AGuiHandler);
private:
	map<string,TComponent *> FListe;
	BList *FListeNotSorted;
//	hash_map<string,TComponent *> FListe;
	TComponentCI FBufIterator;
	int32 FIndex;
	TComponent *FParentComponent;
};

#endif 
