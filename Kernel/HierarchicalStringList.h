#ifndef __HIERARCHICAL_STRING_LIST_H__
#define __HIERARCHICAL_STRING_LIST_H__

#include <stdio.h>
#include <string>
#include "StringList.h"
using namespace std;
//----------------------------
class TElement;
class THierarchicalStringList 
{
	public:
		THierarchicalStringList(void);
		virtual ~THierarchicalStringList(void);
		TElement *GetElement(int index);
		TElement *GetElement(string AValue);
		
		int AddItem(string AName, void *AnItem,bool CanBeDestroyed = false);
		void RemoveItem(string AName);
		void RemoveItem(int index);
		void RemoveItemUnder(string AName, int UnderIndex);
		void RemoveItemUnder(string AName, string UnderName);
		void RemoveItemUnder(int index,int UnderIndex);
		void RemoveItemUnder(int index,string UnderName);
		int CountItems (void);
		int CountItemsUnder (int index);
		int AddItemUnder(string AName, void *AnItem,int UnderIndex,bool CanBeDestroyed = false);
		int AddItemUnder(string AName, void *AnItem,string UnderName, bool CanBeDestroyed = false);
		void *GetItem(int index);
		void *GetItem(string AName);
		void *GetItemUnder(int index,int UnderIndex);
		void *GetItemUnder(int index,string UnderName);
		void *GetItemUnder(string AName,int UnderIndex);
		void *GetItemUnder(string AName,string UnderName);
	private:
		TStringList *FMainListe;
};
//---------- Internal --------
//class TElement : public TStringList
class TElement : public THierarchicalStringList
{
	public:
		TElement(void *AMainItem);
		virtual ~TElement(void);
//	private:
		void *FMainItem;
};

#endif