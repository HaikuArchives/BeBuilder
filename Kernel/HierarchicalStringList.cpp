#include "HierarchicalStringList.h"
// TElement
//TElement::TElement(void *AMainItem):TStringList()
TElement::TElement(void *AMainItem):THierarchicalStringList()
{
	FMainItem = AMainItem;
//	printf("TElement constructeur\n");
}

TElement::~TElement(void)
{
	printf("TElement destructeur\n");
}

// THierarchicalStringList
THierarchicalStringList::THierarchicalStringList(void)
{
	FMainListe = new TStringList;
//	printf("THierarchicalStringList constructeur\n");
	
}

THierarchicalStringList::~THierarchicalStringList(void)
{
	delete FMainListe;
	printf("THierarchicalStringList destructeur\n");
}

TElement *THierarchicalStringList::GetElement(int index)
{
	return (TElement*)FMainListe->GetItem(index);
}

TElement *THierarchicalStringList::GetElement(string AValue)
{
	return (TElement*)FMainListe->GetItem(AValue);
}


int THierarchicalStringList::AddItem(string AName, void *AnItem,bool CanBeDestroyed = false)
{
	return FMainListe->AddItem(AName,new TElement(AnItem),CanBeDestroyed);
}
void THierarchicalStringList::RemoveItem(string AName)
{
	if ((TElement*)FMainListe->GetItem(AName)!=NULL)
	{
		for (int ind=0; ind<((TElement*)FMainListe->GetItem(AName))->CountItems();ind++)
		{
			((TElement*)FMainListe->GetItem(AName))->RemoveItem(ind);			
		}
		FMainListe->RemoveItem(AName);
	}
}
void THierarchicalStringList::RemoveItem(int index)
{
	if ((TElement*)FMainListe->GetItem(index)!=NULL)
	{
		for (int ind=0; ind<((TElement*)FMainListe->GetItem(index))->CountItems();ind++)
		{
			((TElement*)FMainListe->GetItem(index))->RemoveItem(ind);			
		}
		FMainListe->RemoveItem(index);	
	}
}
void THierarchicalStringList::RemoveItemUnder(string AName, int UnderIndex)
{
	if ((TElement*)FMainListe->GetItem(UnderIndex) != NULL)
		((TElement*)FMainListe->GetItem(UnderIndex))->RemoveItem(AName);	
}
void THierarchicalStringList::RemoveItemUnder(string AName, string UnderName)
{
	if ((TElement*)FMainListe->GetItem(UnderName)!=NULL)
		((TElement*)FMainListe->GetItem(UnderName))->RemoveItem(AName);
}
void THierarchicalStringList::RemoveItemUnder(int index,int UnderIndex)
{
	if ((TElement*)FMainListe->GetItem(UnderIndex) != NULL)
		((TElement*)FMainListe->GetItem(UnderIndex))->RemoveItem(index);
}
void THierarchicalStringList::RemoveItemUnder(int index,string UnderName)
{
	if ((TElement*)FMainListe->GetItem(UnderName)!=NULL)
		((TElement*)FMainListe->GetItem(UnderName))->RemoveItem(index);
}
int THierarchicalStringList::CountItems (void)
{
	return FMainListe->GetCount();
}
int THierarchicalStringList::CountItemsUnder (int index)
{
	if ((TElement*)FMainListe->GetItem(index)!=NULL)
		return ((TElement*)FMainListe->GetItem(index))->CountItems();
	else
		return -1;
}
int THierarchicalStringList::AddItemUnder(string AName, void *AnItem,int UnderIndex, bool CanBeDestroyed = false)
{
	if ((TElement*)FMainListe->GetItem(UnderIndex)!=NULL)
		return ((TElement*)FMainListe->GetItem(UnderIndex))->AddItem(AName,AnItem,CanBeDestroyed);
	else
		return -1;
}

int THierarchicalStringList::AddItemUnder(string AName, void *AnItem,string UnderName, bool CanBeDestroyed = false)
{
	if ((TElement*)FMainListe->GetItem(UnderName)!=NULL)
		return ((TElement*)FMainListe->GetItem(UnderName))->AddItem(AName,AnItem,CanBeDestroyed);
	else
		return -1;
}
void *THierarchicalStringList::GetItem(int index)
{
	if ((TElement *)FMainListe->GetItem(index) != NULL)
		return ((TElement *)FMainListe->GetItem(index))->FMainItem;
	else
		return NULL;
}
void *THierarchicalStringList::GetItem(string AName)
{
	if ((TElement *)FMainListe->GetItem(AName) != NULL)
		return ((TElement *)FMainListe->GetItem(AName))->FMainItem;
	else
		return NULL;
}
void *THierarchicalStringList::GetItemUnder(int Index, int UnderIndex)
{
	if ((TElement *)FMainListe->GetItem(UnderIndex) != NULL)
		return ((TElement *)FMainListe->GetItem(UnderIndex))->GetItem(Index);
	else
		return NULL;
}
void *THierarchicalStringList::GetItemUnder(int Index, string UnderName)
{
	if ((TElement *)FMainListe->GetItem(UnderName) != NULL)
		return ((TElement *)FMainListe->GetItem(UnderName))->GetItem(Index);
	else
		return NULL;
}
void *THierarchicalStringList::GetItemUnder(string AName,int UnderIndex)
{
	if ((TElement *)FMainListe->GetItem(UnderIndex) != NULL)
		return ((TElement *)FMainListe->GetItem(UnderIndex))->GetItem(AName);
	else
		return NULL;
}
void *THierarchicalStringList::GetItemUnder(string AName,string UnderName)
{
	if ((TElement *)FMainListe->GetItem(UnderName)!=NULL)
		return ((TElement *)FMainListe->GetItem(UnderName))->GetItem(AName);
	else
		return NULL;
}
