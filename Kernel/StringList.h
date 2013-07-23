#ifndef __STRING_LIST_H__
#define __STRING_LIST_H__
#include <string>
#include <vector>
//#include <hash_map>
#include <map>
#include <stdio.h>
using namespace std;
//typedef hash_map<string,void *>::const_iterator ItemStringCI;
//typedef hash_map<int,void *>::const_iterator ItemIntCI;
//typedef hash_map<string,void *>::const_iterator ItemStringCI;
//typedef hash_map<int,void *>::const_iterator ItemIntCI;

class TStringList  
{
public:
	TStringList(void);
	virtual ~TStringList();
	int IndexOf(string Value);
	int Add(string Value);
	int AddItem(string Value, void *AnItem, bool CanBeDestroyed = false);
	void *GetItem(string Value);
	void *GetItem(int index);
	void RemoveItem (string Value);
	void RemoveItem (int index);
	string GetValue(int index);
	int GetCount(void);
private:
	void BuildIndex(void);
	vector<string> FList;	
	//std::crope,std::crope,hash<std::crope>,eqstr
//	hash_map<string, void *> FListItem1; //Chaine -- Element
//	hash_map<int,void *> FListItem2; //Numero Insert-- Element
//	hash_map<int,string> FListString2; //Numero insert -- Chaine
//	hash_map<string,int> FListString1; // Chaine -- Numero Insert
	map<string, void *> FListItem1; //Chaine -- Element
	map<int,void *> FListItem2; //Numero Insert-- Element
	map<int,string> FListString2; //Numero insert -- Chaine
	map<string,int> FListString1; // Chaine -- Numero Insert

	map<string,bool> FListDestroy; // Chaine -- Destruction 
};

#endif
