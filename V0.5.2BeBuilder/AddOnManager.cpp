/*********************************************
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "AddOnManager.h"
#include "BuilderWindow.h"
// When needed to debug add the AddOn...
//#include "WindowComponent.h"

TAddOnManager::TAddOnManager(void):BHandler("AddOnManager"),TObject("AddOnManager")
//TAddOnManager::TAddOnManager(void):BHandler("AddOnManager")
{

	FDebugMode = 1;
	FDebugMessage= "TAddOnManager ";

	FListAddOn = new BList();
	FMenuBar = NULL;
	FMenu = NULL;
	FBuilderWindow = NULL;
	FListMenu = new TStringList();		

	FListInstance = new TStringList();

	FToolBar = NULL;
	FAddOnHasBeenAdded = false;

}

TAddOnManager::~TAddOnManager(void)
{
	// unload all addons
	ShowDebug("TAddOnManager destructeur! BEfore unloadAddOn");
	delete FListMenu;
	ShowDebug("TAddOnManager destructeur! After unloadAddOn");	
	delete FListAddOn;
	ShowDebug("TAddOnManager destructeur! After delete");		

	if (FToolBar!=NULL) 
	{
		ShowDebug("TAddOnManager destructeur! FToolBar isn't null.");		
		if (FToolBar->Lock()) FToolBar->Quit();
	}

	ShowDebug("TAddOnManager destructeur! After Quitting ToolBar.");			
}

bool TAddOnManager::IsModified(void)
{
	return FAddOnHasBeenAdded;
}

void TAddOnManager::SetModified(bool AValue)
{
	FAddOnHasBeenAdded = AValue;	
}

void TAddOnManager::ShowToolBar(void)
{
	if (FToolBar!=NULL)
	{
		FToolBar->Show();
	}
}

void TAddOnManager::SetMenuBar(BMenuBar *AMenuBar)
{
	FMenuBar = AMenuBar;
}

void TAddOnManager::SetBuilderWindow(TBuilderWindow *ABuilderWindow)
{
	FBuilderWindow = ABuilderWindow;
}

void TAddOnManager::LoadAddOn(void)
{

	image_id	addonId;
   	status_t 	err = B_NO_ERROR; 
//	void (* GetComponentProperties)(BMessage *);
	BMessage* (*GetComponentProperties)(void);
  	TComponent* (*GetComponentInstance)(const char *, const char *, BRect, TComponent*);
	
	BMessage *APropertiesMessage;
	const char *AClassName;


	app_info info; 
    BPath path; 
  
    be_app->GetAppInfo(&info); 
    BEntry entry(&info.ref); 
    entry.GetPath(&path); 
    path.GetParent(&path);
	path.Append("AddOn");
	BDirectory dir( path.Path() );
   	//load all effects
	while( err == B_NO_ERROR )
	{
		err = dir.GetNextEntry( (BEntry*)&entry, TRUE );			
		if( entry.InitCheck() != B_NO_ERROR ){ break; }
		if( entry.GetPath(&path) != B_NO_ERROR )
		{ 
			printf( "entry.GetPath failed\n" );
		}
		else
		{
			addonId = load_add_on( path.Path() );
			if( addonId < 0 )
			{
				printf( "load_add_on( %s ) failed\n", path.Path() );
			}
			else
			{
				printf( "load_add_on( %s ) successful! AddOnId: %ld\n", path.Path(),addonId );
				FListAddOn->AddItem(&addonId);
				if( get_image_symbol( addonId, 
									"GetProperties", 
									B_SYMBOL_TYPE_TEXT, 
									(void **)&GetComponentProperties) )
				{
					printf( "get_image_symbol( Properties ) failed\n" );
//					unload_add_on( addonId );
				}
				else
				{		
					APropertiesMessage = (*GetComponentProperties)();
					if (APropertiesMessage==NULL)
					{
						ShowDebug("LoadAddOn APropertiesMessage is NULL!");
					}
					else
					{
						ShowDebug("LoadAddOn APropertiesMessage is not NULL!");						
//							APropertiesMessage->AddInt32("AddOnID",addonId);
//							ShowDebug("LoadAddOn APropertiesMessage=");
//							APropertiesMessage->PrintToStream();
					}
					if (RegisterProperties(APropertiesMessage))
					{
						ShowDebug("LoadAddOn RegisterProperties OK!");
					}
					else
					{
						ShowDebug("LoadAddOn RegisterProperties Failed.");
					}
					if( get_image_symbol( addonId,
										"GetInstance",
										B_SYMBOL_TYPE_TEXT,
										(void **)&GetComponentInstance) )
					{
						ShowDebug("get_image_symbol for GetInstance failed.");
					}						
					else
					{
						if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
						{
							ShowDebug("LoadAddOn No CLASS_NAME");
						}
						FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);
					}
				}
			}
		}
	}
}

void TAddOnManager::AddLooper (BLooper *ALooper)
{
	if (ALooper->Lock())
	{
		ALooper->AddHandler(this);
		ALooper->Unlock();
	}
}

bool TAddOnManager::Remove(void)
{
	bool res = false;
	res = Looper()->RemoveHandler(this);
	return res;	
}

void TAddOnManager::MessageReceived(BMessage *message)
{
	int32 AddOnId;
	int32 NbElements;
	const char *AddOnParentItem;
	const char *AddOnClassName;
	const char *AddOnComponentName;
	const char *AComponentItemName;
	TComponentItem *tempItem=NULL;
	TComponent *AComponent;
	string ABufClassName;
	string ABufComponentName;
	BRect rect1;
	bool ParentTypeFound=false;
	bool FLoadDataMode =false;
	BMessage AComponentSaveMessage;
	TComponentItem *ATempComponentItem;
  	TComponent* (*GetComponentInstance)(const char *, const char *, BRect, TComponent*);	//addon function prototype
	switch(message->what)
	{
		case MSG_WANT_ADDON : //This Message is sent by BeBuilder when asking for an AddOn
//			DEBUGPRINT("TAddOnManager::MessageReceived Message MSG_WANT_ADDON received!");
			if (FBuilderWindow==NULL)
			{
				printf("TAddOnManager::MessageReceived FBuilderWindow is NULL! \n");			
				break;				
			}			
//			DEBUGPRINT("TAddOnManager::MessageReceived 1");
			if (message->FindInt32("AddOnID",&AddOnId) != B_OK)
			{
				printf("TAddOnManager::MessageReceived MSG_WANT_ADDON No AddOnID \n");
				break;				
			}
//			DEBUGPRINT("TAddOnManager::MessageReceived 2");
			if (message->FindString("ClassName",&AddOnClassName) != B_OK)
			{
				printf("TAddOnManager::MessageReceived MSG_WANT_ADDON No ClassName \n");
				break;							
			}
//			DEBUGPRINT("TAddOnManager::MessageReceived 3");			
			if (message->FindString("ComponentName",&AddOnComponentName) != B_OK)
			{
				printf("TAddOnManager::MessageReceived MSG_WANT_ADDON No ComponentName \n");
				break;							
			}
//			DEBUGPRINT("TAddOnManager::MessageReceived 4");			
			if (message->FindString("ItemName",&AComponentItemName) != B_OK)
			{
				printf("TAddOnManager::MessageReceived MSG_WANT_ADDON No ItemName \n");
				break;							
			}
//			DEBUGPRINT("TAddOnManager::MessageReceived 5");
			if (message->FindMessage(COMPONENT_SAVE_MESSAGE_ADDON,&AComponentSaveMessage) != B_OK)
			{
				DEBUGPRINT("TAddOnManager::MessageReceived MSG_WANT_ADDON No COMPONENT_SAVE_MESSAGE_ADDON \n");	
			//	break;							
			}
			else
			{
//				DEBUGPRINT("TAddOnManager::MessageReceived 6");
				FLoadDataMode = true;
				//We need to select the last item in the list.
//				NbElements = FBuilderWindow->FBuilderView->FOutListe->FullListCountItems();
//				NbElements = FBuilderWindow->FBuilderView->FOutListe->FullListIndexOf(FBuilderWindow->FBuilderView->FOutListe->FullListLastItem());
				/*
				if (message->FindPointer(COMPONENT_ITEM_TO_SELECT,(void **)&tempItem) != B_OK)
				{
					DEBUGPRINT("TAddOnManager::MessageReceived MSG_WANT_ADDON No COMPONENT_SAVE_MESSAGE_ADDON \n");	
					break;							
				}
				if (tempItem!=NULL)
				{
					NbElements = FBuilderWindow->FBuilderView->FOutListe->FullListIndexOf(tempItem);
				}
				else
				{
					ShowDebug("tempItem is NULL.");
				}
				*/
				if (message->FindInt32(COMPONENT_ITEM_TO_SELECT,&NbElements) != B_OK)
				{
					DEBUGPRINT("TAddOnManager::MessageReceived MSG_WANT_ADDON No COMPONENT_SAVE_MESSAGE_ADDON \n");	
					message->PrintToStream();
					break;							
				}

//				DEBUGPRINT("TAddOnManager::MessageReceived NbElements="<<NbElements);
//				if ( NbElements > 0)
//				{
//					FBuilderWindow->FBuilderView->FOutListe->Select(NbElements-1);			
					FBuilderWindow->FBuilderView->FOutListe->Select(NbElements);
//				}
//				DEBUGPRINT("TAddOnManager::MessageReceived 7");
			}
			ShowDebug("MessageReceived Before for.");
			for (long ind = 0; ind < FBuilderWindow->FBuilderView->FOutListe->CountItems(); ind ++)
			{
				tempItem = (TComponentItem *)FBuilderWindow->FBuilderView->FOutListe->ItemAt(ind);
				ShowDebug(string("MessageReceived Searching=") + tempItem->GetTypeName());
				if (tempItem->IsSelected())
				{
					ParentTypeFound = false;
					for (int32 index = 0; ; index++) 
					{
						if (message->FindString("ParentItem",index,&AddOnParentItem) != B_OK)
						{
							ShowDebug(string("MessageReceived MSG_WANT_ADDON No more ParentItem Nb= ") + IntToStr(index));
							break;							
						}
						else 
						{
							ShowDebug(string("MessageReceived ParentItem Value=") + AddOnParentItem);
							if(strcmp(tempItem->GetTypeName(),AddOnParentItem)==0)
							{
								ShowDebug("MessageReceived ParentItem Found!");
								ParentTypeFound = true;
								break;						
							}
						}						
					}
				}
				if ((tempItem->IsSelected())&&(ParentTypeFound))
				{
					ABufClassName = AddOnClassName;
					ABufComponentName = AddOnComponentName;
					rect1 = ((TComponent *)tempItem->GetComponent())->GetChildRect(AddOnClassName);
//						rect1.top = 25; rect1.left = 5; rect1.right = 100; rect1.bottom = 15;
					FBuilderWindow->FComponentProject->GetNextComponentIndex(&ABufComponentName,&ABufClassName);
					if (AddOnId==-1)
					{
						ShowDebug(string("MessageReceived AddOnId==-1 AddOnClassName=") + AddOnClassName);
						// Due to a major problem in gcc... with pointer to static function... 
						GetComponentInstance = (TComponent* (*)(const char *, const char *, BRect, TComponent*))FListInstance->GetItem(AddOnClassName);
					}
//					else
//					{
//						if( get_image_symbol( AddOnId,"GetInstance",B_SYMBOL_TYPE_TEXT,(void **)&GetComponentInstance) !=B_NO_ERROR)
//						{
//							ShowDebug( "TAddOnManager::MessageReceived get_image_symbol( Instance ) failed Trying with AddOnClassName...");
//							
//							break;
//						}
//					}
					ShowDebug("MessageReceived before Calling GetComponentInstance...");					
					AComponent = (* GetComponentInstance)(ABufComponentName.c_str(),ABufClassName.c_str(),rect1,(TComponent *)tempItem->GetComponent());

					// AddIng BMessageAddOn to the Component
					ShowDebug("MessageReceived before adding BMessage to the component");
					message->RemoveName(COMPONENT_SAVE_MESSAGE_ADDON);
					AComponent->SetAddOnMessage(message);
					ShowDebug("MessageReceived after adding BMessage to the component");					
					if (FBuilderWindow->Lock())				
					{
//					    ATempComponentItem = new TComponentItem(AComponent->FComponentName.c_str(),AComponentItemName,AComponent,AComponent->FHandler,tempItem->OutlineLevel()+1);
//					    FBuilderWindow->FBuilderView->FOutListe->AddItem(ATempComponentItem);				    

					    ATempComponentItem = new TComponentItem(AComponent->FComponentName.c_str(),AComponentItemName,AComponent,AComponent->FHandler,tempItem->OutlineLevel()+1);
					    FBuilderWindow->FBuilderView->FOutListe->AddUnder(ATempComponentItem,tempItem);				    
						FBuilderWindow->FBuilderView->FOutListe->Select(FBuilderWindow->FBuilderView->FOutListe->FullListIndexOf(ATempComponentItem));

						AComponent->SetStringItem(ATempComponentItem);
						AComponent->SetIndexInList(FBuilderWindow->FBuilderView->FOutListe->FullListIndexOf(ATempComponentItem));
						AComponent->SetComponentListWindow(FBuilderWindow);
						FBuilderWindow->Unlock();
						ShowDebug(string("MessageReceived Before AddChild. PathGeneration=") + AComponent->FPathGeneration.c_str());
						((TComponent *)tempItem->GetComponent())->AddChild(AComponent);
						ShowDebug(string("MessageReceived Before Generate. PathGeneration=") + AComponent->FPathGeneration.c_str());
						ShowDebug("MessageReceived After AddChild.");
						SetModified(true); // Just a flag to say that a save is needed by the main application ...		
						if (FLoadDataMode)
						{
							ShowDebug("MessageReceived Mode de Rechargement avant LoadData");
							AComponent->LoadData(&AComponentSaveMessage,this);
							ShowDebug("MessageReceived Mode de Rechargement Apres LoadData");
						}
						else
						{
							ShowDebug("MessageReceived FLoadDataMode is FALSE!");
							AComponent->FPathGeneration = FGenerationPath;
							AComponent->Generate(AComponent->FPathGeneration.c_str());    
						}
					}
					break;
				}		
			}
			break;
		default:
			BHandler::MessageReceived(message);
			break;
	}	
}

BMenu *TAddOnManager::FindSubMenu(const char *AMenuName)
{
	//BMenu *buf = NULL;
	string buf;
	for (int ind=0; ind< FListMenu->GetCount(); ind++)
	{
		buf = FListMenu->GetValue(ind);
		if (strcmp(buf.c_str(),AMenuName)==0)
		{
			return (BMenu *)FListMenu->GetItem(ind);
		}
	}
	return NULL;
}

bool TAddOnManager::RegisterProperties(BMessage *ABMessage)
{
	const char *AMenu;
	const char *AVersionClass;
	const char *AClassName;
	const char *AComponentName;						
	const char *ACopyrights;	
	const char *AWrittenBy;
	const char *AComponentItemName;	
	const char *AComponentGroupName;
//	void *AnIcon;
//	void *AnIconOff;
	BBitmap *AnIcon;
	BBitmap *AnIconOff;
	ShowDebug("RegisterProperties Inside");
	if (ABMessage==NULL)
	{
		ShowDebug("RegisterProperties ABMessage is NULL.");
		return false;
	}
 	ABMessage->PrintToStream();		
	if (ABMessage->FindString(MENU_NAME,&AMenu) != B_OK)
	{
		ShowDebug("RegisterProperties No MENU_NAME");
		return false;
	}
	if (ABMessage->FindString(VERSION_NAME,&AVersionClass) != B_OK)
	{
		ShowDebug("RegisterProperties No VERSION_NAME");
		return false;
	}
	if (ABMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("RegisterProperties No CLASS_NAME");
		return false;
	}
	if (ABMessage->FindString(COMPONENT_NAME,&AComponentName) != B_OK)
	{
		ShowDebug("RegisterProperties No COMPONENT_NAME");
		return false;
	}
	if (ABMessage->FindString(COPYRIGHTS_NAME,&ACopyrights) != B_OK)
	{
		ShowDebug("RegisterProperties No COPYRIGHTS_NAME");
		return false;
	}
	if (ABMessage->FindString(WRITTEN_NAME,&AWrittenBy) != B_OK)
	{
		ShowDebug("RegisterPropertiesn No WRITTEN_NAME \n");
		return false;
	}
	if (ABMessage->FindString(COMPONENT_ITEM_NAME,&AComponentItemName) != B_OK)
	{
		ShowDebug("RegisterProperties No COMPONENT_ITEM_NAME \n");
		return false;
	}
/*
     status_t FindData(const char *name, 
         type_code type, 
         const void **data, 
         ssize_t *numBytes) const 
*/
//	ssize_t numBytes;
	if (ABMessage->FindPointer(ICON_NAME,(void **)&AnIcon) != B_OK)
//	if (ABMessage->FindData(ICON_NAME,B_ANY_TYPE,(void **)&AnIcon,&numBytes) != B_OK)
	{
		ShowDebug("RegisterProperties No ICON_NAME \n");
		return false;
	}
//	if (ABMessage->FindData(ICON_OFF_NAME,B_ANY_TYPE,(void **)&AnIconOff,&numBytes) != B_OK)
	if (ABMessage->FindPointer(ICON_OFF_NAME,(void **)&AnIconOff) != B_OK)
	{
		ShowDebug("RegisterProperties No ICON_OFF_NAME \n");
		return false;
	}										
	if (AnIcon==NULL) ShowDebug("RegisterProperties AnIcon is null.");
	if (AnIconOff==NULL) ShowDebug("RegisterProperties AnIconOff is null.");
		
	//Creation du menu et du message!
	if (FMenu==NULL)
	{
		FMenu = new BMenu("AddOns");
		FMenuBar->AddItem(FMenu);
	}
	else
	{
//		ShowDebug("TAddOnManager::LoadAddOn FAlreadyAddMenu is true");
	}
	const char *AParentItemComponent;
	BMessage *AMessageAddOn = new BMessage(MSG_WANT_ADDON);
	int32 AnAddOnId=-1;
	if (ABMessage->FindInt32("AddOnID",&AnAddOnId)==B_OK)
	{
		AMessageAddOn->AddInt32("AddOnID",AnAddOnId); //Means from a statically linked addons	
	}
	else
	{
		AMessageAddOn->AddInt32("AddOnID",-1); //Means from a statically linked addons	
	}
	for (int32 index = 0; ; index++) 
	{
		if (ABMessage->FindString(PARENT_COMPONENT_NAME,index,&AParentItemComponent) != B_OK)
		{
			ShowDebug("RegisterProperties NoMore PARENT_COMPONENT_NAME");
			break;							
		}
		else 
		{
			ShowDebug(string("RegisterProperties Another PARENT_COMPONENT_NAME=") + AParentItemComponent);
			AMessageAddOn->AddString("ParentItem",AParentItemComponent);						
		}
	}
	AMessageAddOn->AddString("ItemName",AComponentItemName);												
	AMessageAddOn->AddString("ClassName",AClassName);						
	AMessageAddOn->AddString("ComponentName",AComponentName);									

	// Adding Component In Menu
	BMenuItem *AMenuItem;
	BMenu *FTmpMenu;
	BMenu *FTmpMenu2;
    
    FTmpMenu = FMenu;
	for (int32 index = 0; ; index++) 
	{
		if (ABMessage->FindString(COMPONENT_GROUP_NAME,index,&AComponentGroupName) != B_OK)
		{
//			ShowDebug("RegisterProperties NoMore COMPONENT_GROUP_NAME");
			break;							
		}
		else 
		{
//			ShowDebug(string("RegisterProperties Another COMPONENT_GROUP_NAME=") + AComponentGroupName);
			if (strlen(AComponentGroupName)!=0)
			{
				FTmpMenu2 = FindSubMenu(AComponentGroupName);
				if (FTmpMenu2==NULL)
				{
//					ShowDebug("RegisterProperties Another Creation du menu TEMp2 \n");
					FTmpMenu2 = new BMenu(AComponentGroupName);
					FTmpMenu->AddItem(FTmpMenu2);
					FListMenu->AddItem(AComponentGroupName,FTmpMenu2,false);
				}
				FTmpMenu = FTmpMenu2; //FTmpMenu2 should not be NULL anymore								
			}
		}
	}

	AMenuItem = new BMenuItem(AMenu,AMessageAddOn);
	FTmpMenu->AddItem(AMenuItem);					
	AMenuItem->SetTarget(this);
	
	//Adding Component in ToolBar.
	ShowDebug("RegisterProperties Adding Component In ToolBar");
	if (FToolBar==NULL)
	{
		ShowDebug("RegisterProperties FToolBar is NULL.");
//		FToolBar = new TToolBar("ToolBar",BRect(10,10,100,100),this);		
//		FToolBar = new TToolBar("ToolBar",BRect(184,50,260,140),this);		
		FToolBar = new TToolBar("ToolBar",TOOLBAR_POSITION,this);		
		FToolBar->Show();
	}
	ShowDebug("RegisterProperties Before Adding Picture In ToolBar");
//	FToolBar->AddPictureButton(AnIcon, AnIconOff,AMessageAddOn,AClassName);	
	FToolBar->AddPictureText(AMenu,AMessageAddOn,this);	
	ShowDebug("RegisterProperties After Adding Picture In ToolBar");
		
	if (FBuilderWindow!=NULL)
	{
		FBuilderWindow->FAddOnStr = FBuilderWindow->FAddOnStr + "\n";
		FBuilderWindow->FAddOnStr = FBuilderWindow->FAddOnStr + "AddOn: ";
		FBuilderWindow->FAddOnStr = FBuilderWindow->FAddOnStr + AClassName;
		FBuilderWindow->FAddOnStr = FBuilderWindow->FAddOnStr + "\n\tWritten by ";
		FBuilderWindow->FAddOnStr = FBuilderWindow->FAddOnStr + AWrittenBy;
		FBuilderWindow->FAddOnStr = FBuilderWindow->FAddOnStr + "\n\t";
		FBuilderWindow->FAddOnStr = FBuilderWindow->FAddOnStr + ACopyrights;
	}									
	ShowDebug("RegisterProperties Loading Done ?");
	ShowDebug(string("AMenu=") + AMenu);
//	ShowDebug(string ("ParentItemComponent=") + AParentItemComponent);
	ShowDebug(string("ClassName=") + AClassName);
	ShowDebug(string("ComponentName=") + AComponentName);
	ShowDebug(string("Copyrights=") + ACopyrights);
	ShowDebug(string("WrittenBy=") + AWrittenBy);
	ShowDebug(string("Version=") + AVersionClass);
	return true;
}

bool TAddOnManager::LoadStaticAddOn(void)
{
	// Here you add your statically linked addons...
	// This weird method has been added to debug the add-ons... that will be loaded at runtime	
	// BMessage *TWindowComponent::GetProperties(void)
	// Then you know exactly the kind of addon you loaded
	// Then register the Instance static function in a TStringList.
 	ShowDebug("LoadStaticAddOn Inside");
 	TComponent* (*GetComponentInstance)(const char *, const char *, BRect, TComponent*);	//addon function prototype
	const char *AClassName;	
	BMessage *APropertiesMessage;
//WindowComponent	
 	ShowDebug("LoadStaticAddOn before TWindowComponent::GetProperties()");
	APropertiesMessage = TWindowComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TWindowComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);
//ViewComponent	
 	ShowDebug("LoadStaticAddOn before TViewComponent::GetProperties()");
	APropertiesMessage = TViewComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TViewComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);
//BoxComponent	
 	ShowDebug("LoadStaticAddOn before TBoxComponent::GetProperties()");
	APropertiesMessage = TBoxComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TBoxComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);
//ButtonComponent	
 	ShowDebug("LoadStaticAddOn before TButtonComponent::GetProperties()");
	APropertiesMessage = TButtonComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TButtonComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

//TextControlComponent	
 	ShowDebug("LoadStaticAddOn before TTextControlComponent::GetProperties()");
	APropertiesMessage = TTextControlComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TTextControlComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

//CheckBoxComponent	
 	ShowDebug("LoadStaticAddOn before TCheckBoxComponent::GetProperties()");
	APropertiesMessage = TCheckBoxComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TCheckBoxComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);
	
//RadioButtonComponent	
 	ShowDebug("LoadStaticAddOn before TRadioButtonComponent::GetProperties()");
	APropertiesMessage = TRadioButtonComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TRadioButtonComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

//SliderComponent	
 	ShowDebug("LoadStaticAddOn before TSliderComponent::GetProperties()");
	APropertiesMessage = TSliderComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TSliderComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

//MenuBarComponent	
 	ShowDebug("LoadStaticAddOn before TMenuBarComponent::GetProperties()");
	APropertiesMessage = TMenuBarComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TMenuBarComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

//MenuComponent	
 	ShowDebug("LoadStaticAddOn before TMenuComponent::GetProperties()");
	APropertiesMessage = TMenuComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TMenuComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);
//MenuItem	
 	ShowDebug("LoadStaticAddOn before TMenuItemComponent::GetProperties()");
	APropertiesMessage = TMenuItemComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TMenuItemComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

//MenuSeparator	
 	ShowDebug("LoadStaticAddOn before TMenuSeparatorComponent::GetProperties()");
	APropertiesMessage = TMenuSeparatorComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TMenuSeparatorComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

//MenuField	
 	ShowDebug("LoadStaticAddOn before TMenuFieldComponent::GetProperties()");
	APropertiesMessage = TMenuFieldComponent::GetProperties();
	// Now add the Menu and so on...
	RegisterProperties(APropertiesMessage);
	GetComponentInstance = TMenuFieldComponent::GetInstance;
	if (APropertiesMessage->FindString(CLASS_NAME,&AClassName) != B_OK)
	{
		ShowDebug("LoadStaticAddOn No CLASS_NAME");
		return false;
	}
	FListInstance->AddItem(AClassName,(void *)GetComponentInstance,false);

	
	ShowDebug("LoadStaticAddOn Quitting.");
		
	return true;
}

bool TAddOnManager::SetGenerationPath(const char *AGenerationPath)
{
	FGenerationPath = AGenerationPath;
}

