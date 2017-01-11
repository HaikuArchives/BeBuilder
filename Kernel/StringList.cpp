#include "StringList.h"

TStringList::TStringList(void)
{
 
}

TStringList::~TStringList()
{
	for (vector<string>::iterator p = FList.begin(); p != FList.end(); ++p)
	{
		if (FListDestroy[*p]==true) 
		{
			delete FListItem1[*p];		
		}		
	}
}

int TStringList::IndexOf(string Value)
{
	return FListString1[Value];	
}

int TStringList::Add(string Value)
{
 	int result; 
 	FList.push_back(Value);
 	result = FList.size()-1;
 	FListString2[result] = Value;
 	FListString1[Value] = result;
 	return result;
}

int TStringList::AddItem(string Value, void *AnItem, bool CanBeDestroyed)
{
//	printf("----------TStringList::AddItem-- Value = %s\n",Value.data());
	int result = Add(Value);
//	printf("----------TStringList::AddItem-- Size = %d\n",FList.size());
//	printf("----------TStringList::AddItem-- Index = %d\n",result);
	FListItem1[Value] = AnItem;
//	printf("----------TStringList::AddItem-- Added to FListItem1\n");
	FListItem2[result] = AnItem;
//	printf("----------TStringList::AddItem-- Added to FListItem2\n");
	FListDestroy[Value] = CanBeDestroyed;
	return result;
}

void *TStringList::GetItem(string Value)
{
	return FListItem1[Value];
}

void *TStringList::GetItem(int index)
{
//	return FListItem2[index];
	void *truc = NULL;
	truc = FListItem2[index];
	return truc;

}

void TStringList::RemoveItem (string Value)
{
	int index = FListString1[Value];
	if (FListDestroy[Value]==true) 
	{
		delete FListItem1[Value];		
	}
	FListItem1.erase(Value);
	FListItem2.erase(index);
	FListString2.erase(index);
	FListString1.erase(Value);
	for (vector<string>::iterator p = FList.begin(); p != FList.end(); ++p)
	{
		if (*p == Value)
		{
			FList.erase(p);
			break;
		}
	}
	BuildIndex();
}

void TStringList::RemoveItem (int index)
{
	string Value = FListString2[index];
	RemoveItem(Value);
}

string TStringList::GetValue(int index)
{
	return FListString2[index];
}

int TStringList::GetCount(void)
{
	return FList.size();
}

void TStringList::BuildIndex(void)
{
//	int max = GetCount();
	int ind = 0;
	FListString2.erase(FListString2.begin(),FListString2.end());
	FListItem2.erase(FListItem2.begin(),FListItem2.end());
	FListString1.erase(FListString1.begin(),FListString1.end());
	for (vector<string>::const_iterator p = FList.begin(); p != FList.end(); ++p,ind++)
	{
		FListString2[ind] = *p;			
//		printf("---TStringList::BuildIndex--- FListString2 *p = %s, ind= %d \n",p->data(),ind);	
	}
	ind = 0;
	for (vector<string>::iterator p = FList.begin(); p != FList.end(); ++p,ind++)
	{
		FListString1[*p] = ind;
//		printf("---TStringList::BuildIndex--- FListString1 *p = %s, ind= %d \n",p->data(),ind);	
	}	
	for (map<string,int>::const_iterator p = FListString1.begin(); p != FListString1.end(); ++p)
	{
		FListItem2[p->second] = FListItem1[p->first];	
//		printf("---TStringList::BuildIndex--- p->second = %d, p->first= %s \n",p->second,(p->first).data());	
	}
}

