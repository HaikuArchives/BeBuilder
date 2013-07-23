#include "BuilderWindow.h"

//TBuilderWindow::TBuilderWindow(const char *Title,BRect frame,const char *Prefs):BGeneralWindow(Title,frame,Prefs,B_TITLED_WINDOW,0)
TBuilderWindow::TBuilderWindow(const char *Title,BRect frame,const char *Prefs):BGeneralWindow(Title,frame,Prefs,B_DOCUMENT_WINDOW,0)
{
	BRect rect;
	rect =  Bounds();
	rect.top = HAUTEUR_MENU;	
	//New
	rect.right -= B_V_SCROLL_BAR_WIDTH;
	rect.bottom -= B_H_SCROLL_BAR_HEIGHT;
	FBuilderView = new TBuilderView(rect);
//	AddChild(FBuilderView);
	AddChild(new BScrollView("ScrollBuilderView",FBuilderView->FOutListe,B_FOLLOW_ALL_SIDES,0,true,true));

 	rect.top = 0; 
 	rect.bottom = HAUTEUR_MENU -1; // 19 
	FBuilderMenu = new TBuilderMenu(rect);	
	AddChild(FBuilderMenu);	
	FComponentProject = NULL;
//	FComponentWindow = NULL;
//	FComponentView = NULL;
//	FComponentButton = NULL;
//	FComponentTextControl = NULL;
	FAddOnManager = NULL;

	FAddOnManager = new TAddOnManager();
	FAddOnManager->AddLooper(be_app);
	FAddOnManager->SetMenuBar(FBuilderMenu);
	FAddOnManager->SetBuilderWindow(this);
	FAddOnManager->LoadStaticAddOn();
	FAddOnManager->LoadAddOn();
	//BE_BUILDER_GENERATION
	BEntry AnEntry(BE_BUILDER_GENERATION);
	entry_ref AnEntryRef;
	AnEntry.GetRef(&AnEntryRef);
	
	FOpenDir = new TOpenDir(NULL,&AnEntryRef,0,true,NULL,NULL,false,true);
	
	FBeBuilderOption = new TBeBuilderOption(PREFS_FILENAME);
	FWindowOption = new TWindowOption(OPTION_TITLE,OPTION_WINDOW_POSITION);
//	FWindowOption->Hide();		
	DEBUGPRINT("TBuilderWindow Fin contructor\n");	
	
	
}

TBuilderWindow::~TBuilderWindow()
{
	DEBUGPRINT("TBuilderWindow destructor Inside");	
	FBeBuilderOption->ApplyUpdates();
	delete FBeBuilderOption;
	delete FAddOnManager;
	delete FBuilderView;
	FWindowOption->Quit();
	DEBUGPRINT("TBuilderWindow destructor Quitting");	
}

bool TBuilderWindow::SaveIfNeeded(void)
{
	bool ARes = true;
	DEBUGPRINT("TBuilderWindow SaveIfNeeded inside!");	
	if (FAddOnManager->IsModified())
	{
		DEBUGPRINT("TBuilderWindow SaveIfNeeded AddOnManager Is Moidified is true");	
		BAlert *AnAlert = new BAlert ("BeBuilder Message", "Your project has been modified but is not saved. What do you want to do?","Save Now!","Don't care.","Cancel",B_WIDTH_FROM_LABEL);
		(AnAlert->ButtonAt(2))->MakeDefault(false);
		(AnAlert->ButtonAt(0))->MakeDefault(true);
		AnAlert->SetShortcut(2,B_ESCAPE);
		AnAlert->SetShortcut(0,B_ENTER);
		DEBUGPRINT("TBuilderWindow SaveIfNeeded AddOnManager before Go");			
		int32 AValue = AnAlert->Go();
		DEBUGPRINT("TBuilderWindow SaveIfNeeded AddOnManager After Go");			
		if (AValue==0)
		{
			//Save Now!
			MessageReceived(new BMessage(MENU_FILE_SAVE_PROJECT));
		}
		if (AValue==1)
		{
			; // Do nothing		
		}
		if (AValue==2)
		{
			ARes = false;
		}	
	}
	return ARes;
}

bool TBuilderWindow::QuitRequested(void)
{
	if (SaveIfNeeded())
		return BGeneralWindow::QuitRequested();
	else
		return false;
}

/*
bool TBuilderWindow::QuitRequested(void)
{
	DEBUGPRINT("TBuilderWindow::QuitRequested");	
	be_app->PostMessage(B_QUIT_REQUESTED);
	return (TRUE);
}
*/

bool TBuilderWindow::SaveProject(const char* APath, const char * AName, BMessage *ASaveMessage)
{
	DEBUGPRINT("TBuilderWindow::SaveProject Inside.");
	const BDirectory *DirRef = new BDirectory(APath);
	BPath *ASavePath = new BPath();
	string truc = AName;
	BFile ASaveFile;
		
	truc += BE_BUILDER_EXTENSION;
	ASavePath->SetTo(DirRef,NULL,false);
	ASavePath->Append(truc.c_str());
	if (ASaveMessage==NULL)
	{
		DEBUGPRINT("TBuilderWindow::SaveProject ASaveMessage is NULL.");
		return false;
	}
	BEntry ATempEntry;
	ATempEntry.SetTo(ASavePath->Path());
	DEBUGPRINT("TBuilderWindow::MessageReceived Before ATempEntry.Exists()");
	if (ATempEntry.Exists())
	{
		ATempEntry.Remove();
		DEBUGPRINT("TBuilderWindow::MessageReceived ATempEntry should have been removed.");	
	}
//	DEBUGPRINT("TBuilderWindow::MessageReceived Before PrintingMessage");
//	PrintMessage(ASaveMessage,0);
//	DEBUGPRINT("TBuilderWindow::MessageReceived After PrintingMessage");
	if (ASaveFile.SetTo(ASavePath->Path(),B_ERASE_FILE | B_WRITE_ONLY | B_CREATE_FILE) == B_OK) 
	{
		ASaveMessage->Flatten(&ASaveFile);
		BNode node(ASavePath->Path());
		app_info ApplicationInfo; 

	   	be_app->GetAppInfo(&ApplicationInfo); 
	   	BPath ApplicationPath;
	    BEntry ApplicationEntry(&ApplicationInfo.ref); 
	    ApplicationEntry.GetPath(&ApplicationPath); 
		BNode ApplicationNode(ApplicationPath.Path());
		BNodeInfo ApplicationNodeInfo( &ApplicationNode );

		BNodeInfo nodeinfo( &node );
		
		nodeinfo.SetType(PROJECT_MIME);
		BBitmap *ABmp = new BBitmap( BRect( 0, 0, 31, 31 ), B_CMAP8 );
		
		ApplicationNodeInfo.GetTrackerIcon( ABmp, B_LARGE_ICON );
		nodeinfo.SetIcon( ABmp, B_LARGE_ICON );
		delete ABmp;
		ABmp = new BBitmap( BRect( 0, 0, 15, 15 ), B_CMAP8 );
		ApplicationNodeInfo.GetTrackerIcon( ABmp, B_MINI_ICON );

		nodeinfo.SetIcon( ABmp, B_MINI_ICON );
		delete ABmp;
		FAddOnManager->SetModified(false);		
		return true;			
	}
	delete DirRef;

	delete ASavePath;
	return false;
}


void TBuilderWindow::MessageReceived(BMessage *message)
{
	message->PrintToStream();
//	BRect rect1(50,50,200,200);
	TComponentItem *tempItem = NULL;
	TComponent *AComponent;
	BMessage *ASaveMessage; 
	BMessenger *AMessenger;
	BFilePanel *AFilePanel;
	string truc;
	string AStr;
	string *StrPtr;
	BList AList(20);
	string ABufClassName,ABufComponentName;
	BFile ASaveFile;
	BPath ASavePath;
	entry_ref dir_ref;
	entry_ref open_ref; 
	BFile AFileOpenEntry;
	BMessage ALoadMessage;
	BEntry DirRef;
	BEntry ATempEntry;
	BPath *APath;
	int32 AnIndex;
	const char * ASaveFileName;
	TComponentItem *ATempComponentItem;
	TComponentItem *buf;	
	int32 bidule;
	switch(message->what)
	{
	
			case MSG_OUTLINE_DELETE :
			DEBUGPRINT("TBuilderView::MessageReceived Inside MSG_OUTLINE_DELETE");		
			if (message->FindInt32("index", &bidule) == B_OK) 
			{
				DEBUGPRINT("TBuilderView::MessageReceived bidule="<<bidule);
				DEBUGPRINT("TBuilderView::MessageReceived FToolWindow avant le ItemAt()");
				buf = ((TComponentItem *)(FBuilderView->FOutListe->FullListItemAt(bidule)));
				DEBUGPRINT("TBuilderView::MessageReceived FToolWindow before RemoveChild");				
				if (buf->GetComponent()->FParent != NULL)
				{
					buf->GetComponent()->FParent->RemoveChild(buf->GetComponent());
				}
				else
				{
					DEBUGPRINT("TBuilderView::MessageReceived RemoveAllChild "<<buf->GetComponent()->FComponentName.c_str());
					(buf->GetComponent()->FChildren)->RemoveAllChild();
				}
				DEBUGPRINT("TBuilderView::MessageReceived FToolWindow before RemoveItem");				
				FBuilderView->FOutListe->RemoveItem(bidule);
				DEBUGPRINT("TBuilderView::MessageReceived FToolWindow after RemoveItem");				
			}		
			break;
		case MSG_OUTLINE_CLICK :
			DEBUGPRINT("TBuilderView::MessageReceived Inside MSG_OUTLINE_CLICK");
			if (message->FindInt32("index", &bidule) == B_OK) 
			{
				buf = ((TComponentItem *)(FBuilderView->FOutListe->ItemAt(bidule)));
				FBuilderView->SendPropertyMessage(buf);
			}		
			break;

	
		case MENU_TOOL_SHOW_TOOLBAR:
			FAddOnManager->ShowToolBar();
			break;
		case MENU_FILE_CLOSE_PROJECT:
			if (SaveIfNeeded())
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_CLOSE_PROJECT");
				ASaveMessage = new BMessage(MSG_OUTLINE_DELETE);
				ASaveMessage->AddInt32("index",0);		
				AMessenger = new BMessenger(FBuilderView);
				AMessenger->SendMessage(ASaveMessage);
				DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_CLOSE_PROJECT END.");				
			}
			break;
		case MENU_FILE_PREFERENCES:
//			if (FWindowOption->Lock())
//			if (FWindowOption->LockLooper())
//			{
				FWindowOption->Show();
//				FWindowOption->UnlockLooper();
//				FWindowOption->Unlock();
//			}
			break;
		case MSG_COMPONENT_FOCUS :
			DEBUGPRINT("TBuilderWindow::MessageReceived MSG_COMPONENT_FOCUS");
			if (message->FindPointer(COMPONENT_POINTER,(void**)&ATempComponentItem)!=B_OK)
			{
				printf("TBuilderWindow::MessageReceived MSG_COMPONENT_FOCUS can't find COMPONENT_POINTER.\n");
			}
		    AnIndex = FBuilderView->FOutListe->FullListIndexOf(ATempComponentItem);
			DEBUGPRINT(string("TBuilderWindow::MessageReceived MSG_COMPONENT_FOCUS index=") + IntToStr(AnIndex));
			FBuilderView->FOutListe->Select(AnIndex);
			FBuilderView->SendPropertyMessage(ATempComponentItem);			
			break;
		case MENU_FILE_OPEN_PROJECT	:
			if (SaveIfNeeded())
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_OPEN_PROJECT");
				AFilePanel = new BFilePanel(B_OPEN_PANEL,NULL,NULL,0,false,NULL,NULL,true,true);
				AFilePanel->SetTarget(this);
				AFilePanel->Show();
			}
			break;
		case B_OPEN:
		case B_REFS_RECEIVED:
			DEBUGPRINT("TBuilderWindow::MessageReceived B_REFS_RECEIVED");	
		case B_SIMPLE_DATA :
			DEBUGPRINT("TBuilderWindow::MessageReceived B_SIMPLE_DATA");
			if (message->FindRef("refs",&open_ref)!= B_OK)
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived B_SIMPLE_DATA cannot find refs.");
				break;
			}
			DEBUGPRINT("TBuilderWindow::MessageReceived refs Loaded..."<<open_ref.name);
			AFileOpenEntry.SetTo(&open_ref,B_READ_ONLY);
			ALoadMessage.Unflatten(&AFileOpenEntry); 
			DEBUGPRINT("TBuilderWindow::MessageReceived Printing LoadingMessage");
			ALoadMessage.PrintToStream();
			FComponentProject = new TProjectComponent("ReloadingName","ReloadingClass");
			ATempComponentItem = new TComponentItem(FComponentProject->FComponentName.c_str(),COMPONENT_ITEM_PROJECT,FComponentProject,FComponentProject);
		    FBuilderView->FOutListe->AddItem(ATempComponentItem);
			if (be_app->Lock())
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived  before addHandler for project");
				be_app->AddHandler(FComponentProject);							
				DEBUGPRINT("TBuilderWindow::MessageReceived  after addHandler for project");
				be_app->Unlock();
			}
			FBuilderView->FOutListe->Select(FBuilderView->FOutListe->FullListCountItems()-1);
			FComponentProject->LoadData(&ALoadMessage,FAddOnManager);
			DEBUGPRINT("TBuilderWindow::MessageReceived  before Setname="<<FComponentProject->FComponentName.c_str());			
			ATempComponentItem->SetName(FComponentProject->FComponentName.c_str());
//			FBuilderView->FOutListe->Draw(FBuilderView->FOutListe->Bounds());							
//			FBuilderView->FOutListe->ReplaceItem(0,ATempComponentItem);							
			
			break;
		case MENU_FILE_SAVEAS_PROJECT :
			DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_SAVEAS_PROJECT");
			DirRef.SetTo(FComponentProject->GetGenerationPath());
			DirRef.GetRef(&dir_ref);
			AFilePanel = new BFilePanel(B_SAVE_PANEL,NULL,&dir_ref,0,false,NULL,NULL,true,true);
			AFilePanel->SetTarget(this);
			AFilePanel->Show();
			break;
		case B_SAVE_REQUESTED :
			DEBUGPRINT("TBuilderWindow::MessageReceived B_SAVE_REQUESTED");
			if (message->FindRef("directory",&dir_ref)!=B_OK)
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived B_SAVE_REQUESTED directory not found.")
				break;	
			}
			if (message->FindString("name",&ASaveFileName)!=B_OK)
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived B_SAVE_REQUESTED directory not found.")
				break;	
			}
			truc = ASaveFileName;
			truc += BE_BUILDER_EXTENSION;
			DirRef.SetTo(&dir_ref);
			ASavePath.SetTo(&DirRef);
			ASaveMessage = FComponentProject->SaveData();
			if (SaveProject(ASavePath.Path(),ASaveFileName,ASaveMessage))
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived B_SAVE_REQUESTED is OK!");
			}
			else
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived B_SAVE_REQUESTED failed!");
			}
			break;
		case MENU_FILE_SAVE_PROJECT :
			DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_SAVE_PROJECT");
			if (FComponentProject==NULL)
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_SAVE_PROJECT FProjectComponent is NULL!");				
				break;
			}
			ASaveMessage = FComponentProject->SaveData();
			if (SaveProject(FComponentProject->GetGenerationPath(),
				FComponentProject->FComponentName.c_str(),ASaveMessage))
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_SAVE_PROJECT SaveProject is OK!");
			}
			else
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived MENU_FILE_SAVE_PROJECT SaveProject failed.");			
			}
			break;	

		case ADD_ITEM :
			DEBUGPRINT("TBuilderWindow::MessageReceived ADD_ITEM");
			if (message->FindPointer(COMPONENT_TO_ADD,(void **)&AComponent)==B_OK)
			{
				FBuilderView->FOutListe->AddItem(new TComponentItem(AComponent->FComponentName.c_str(),AComponent->FTypeName.c_str(),AComponent,AComponent->FHandler,1));
			}
			else
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived in ADD_ITEM, COMPONENT_TO_ADD cannot be found.");
			}
			break;
		case ADD_ITEM_UNDER :
			DEBUGPRINT("TBuilderWindow::MessageReceived ADD_ITEM_UNDER");
			if (message->FindPointer(COMPONENT_TO_ADD,(void **)&AComponent)==B_OK)
			{
				tempItem = (TComponentItem *)FBuilderView->FOutListe->FullListLastItem();
				FBuilderView->FOutListe->AddItem(new TComponentItem(AComponent->FComponentName.c_str(),AComponent->FTypeName.c_str(),AComponent,AComponent->FHandler,tempItem->OutlineLevel()+1));
				//(tempItem->GetComponent())->AddChild(FComponentView);				    

			}
			else
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived in ADD_ITEM_UNDER, COMPONENT_TO_ADD cannot be found.");
			}
			break;
	
		case MENU_FILE_ABOUT:
			truc = BE_BUILDER_NAME ;
			truc = truc + " Version " ;
			truc = truc + BE_BUILDER_VERSION ;
			truc = truc + "\n";
			truc = truc + "Copyrights " ;
			truc = truc + BE_BUILDER_COPYRIGHT ;
			truc = truc + "\n";
			truc = truc + BE_BUILDER_DATE ;
			truc = truc + "\n";		
			if (FAddOnStr.length()>0)
				truc = truc + FAddOnStr;
			ShowMessage(truc.c_str());
			break;
		case B_DIR_REFS_RECEIVED:
			DEBUGPRINT("TBuilderWindow::MessageReceived  B_DIR_REFS_RECEIVED ");					
		    FBuilderView->FOutListe->AddItem(new TComponentItem(FComponentProject->FComponentName.c_str(),COMPONENT_ITEM_PROJECT,FComponentProject,FComponentProject));
			if (be_app->Lock())
			{
				DEBUGPRINT("TBuilderWindow::MessageReceived  before addHandler for project");					
				if (FComponentProject->Looper()==NULL)
				{
					DEBUGPRINT("TBuilderWindow::MessageReceived FCOmponentProject->Looper() is NULL.");
				}
				else 
				{
					DEBUGPRINT("TBuilderWindow::MessageReceived FComponentProject->Looper() is not null.");
				}
				if (message->FindRef("refs",&dir_ref)==B_OK)
				{
					FOpenDir->Hide();		
					ATempEntry.SetTo(&dir_ref);
					APath = new BPath(&ATempEntry);
					FComponentProject->SetGenerationPath(APath->Path());
					FAddOnManager->SetGenerationPath(FComponentProject->GetGenerationPath());					
				}
// 				ShowMessage(string("Generated Code will be found in ") + FComponentProject->GetGenerationPath());			
				FComponentProject->Generate("/"); 
				DEBUGPRINT("TBuilderWindow::MessageReceived  after addHandler for project");					
				be_app->Unlock();
			}
		
			break;
		case MENU_FILE_NEW_PROJECT:
			if (SaveIfNeeded())
			{		
				FBuilderView->FOutListe->MakeEmpty();
				if (FComponentProject!=NULL)
				{
					DEBUGPRINT("TBuilderWindow::MessageReceived Inside New file Project before delete COmponentProject!\n");					
					delete FComponentProject;
				}
				FComponentProject = new TProjectComponent("AProject","TProject");
				FOpenDir->SetTarget((BHandler *)this);
				FOpenDir->Show();						
				FAddOnManager->SetModified(true);			
			}
			break;
		case MENU_TOOL_RUN:
			AStr = "cd ";
			AStr += FComponentProject->GetGenerationPath();
			AStr += " ; make";
			DEBUGPRINT("BuilderWindow RUN Before " << AStr.c_str());
			RunCmd(AStr.c_str());	
			DEBUGPRINT("BuilderWindow RUN After " << AStr.c_str());
			AStr = "cd ";
			AStr += FComponentProject->GetGenerationPath();
			AStr += "obj.x86 ; ";
			AStr += FComponentProject->GetExe();
			DEBUGPRINT("BuilderWindow RUN Before " << AStr.c_str());
			RunCmd(AStr.c_str());				
			DEBUGPRINT("BuilderWindow RUN After " << AStr.c_str());
			break;
		case MENU_TOOL_MAKE:
			AStr = "cd ";
			AStr += FComponentProject->GetGenerationPath();
			AStr += " ; make 2>&1 > .make.txt";		
			DEBUGPRINT("BuilderWindow MAKE Before " << AStr.c_str());
			RunCmd(AStr.c_str());	
			DEBUGPRINT("BuilderWindow MAKE After" << AStr.c_str());
			OpenFile(".make.txt");			
			break;

		case MENU_TOOL_EDIT_FILE_BODY:
			DEBUGPRINT("BuilderWindow::MessageReceived Inside MENU_TOOL_EDIT_FILE_BODY");
			for (long ind = 0; ind < FBuilderView->FOutListe->CountItems(); ind ++)
			{
				tempItem = (TComponentItem *)FBuilderView->FOutListe->ItemAt(ind);
				if (tempItem->IsSelected())
				{
					DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_BODY before calling GetBodyFileName");
					StrPtr = (tempItem->GetComponent())->GetBodyFileName();
					if (StrPtr!=NULL)
					{
						DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_BODY before calling OpenFile *StrPtr="<< *StrPtr);
						OpenFile(*StrPtr);
						DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_BODY after calling OpenFile *StrPtr="<< *StrPtr);
					}
					else
					{
						DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_HEADER StrPtr is NULL.");						
					}
				}
			}
			DEBUGPRINT("BuilderWindow::MessageReceived Quitting MENU_TOOL_EDIT_FILE_BODY");
			break;

		case MENU_TOOL_EDIT_FILE_HEADER:
			DEBUGPRINT("BuilderWindow::MessageReceived Inside MENU_TOOL_EDIT_FILE_HEADER");
			for (long ind = 0; ind < FBuilderView->FOutListe->CountItems(); ind ++)
			{
				tempItem = (TComponentItem *)FBuilderView->FOutListe->ItemAt(ind);
				if (tempItem->IsSelected())
				{
					DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_BODY before calling GetHeaderFileName");
					StrPtr = (tempItem->GetComponent())->GetHeaderFileName();
					if (StrPtr!=NULL)
					{
						DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_HEADER before calling OpenFile *StrPtr="<< *StrPtr);
						OpenFile(*StrPtr);
						DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_HEADER after calling OpenFile *StrPtr="<< *StrPtr);
					}
					else
					{
						DEBUGPRINT("BuilderWindow::MessageReceived MENU_TOOL_EDIT_FILE_HEADER StrPtr is NULL.");						
					}
					
				}
			}
			DEBUGPRINT("BuilderWindow::MessageReceived Quitting MENU_TOOL_EDIT_FILE_HEADER");
			break;

		case MENU_TOOL_EDIT_FILE_MAKEFILE:			
			DEBUGPRINT("BuilderWindow::MessageReceived Inside MENU_TOOL_EDIT_FILE_MAKEFILE");
			OpenFile(string("makefile"));
			DEBUGPRINT("BuilderWindow::MessageReceived Quitting MENU_TOOL_EDIT_FILE_MAKEFILE");
			break;
/*
	expid=fork();
	if (expid==0){
//        printf("writerfunc started\n");

		fflush(stdout);close(STDOUT_FILENO);dup(pipefd[1]);
		fflush(stderr);close(STDERR_FILENO);dup(pipefd[1]);
		close(pipefd[0]);//no readers..
		close(pipefd[1]);

		char *args[4];
		args[0]="/bin/sh";
		args[1]="-c";
		args[2]=cmdbuff;
		args[3]=NULL;
		execvp(args[0],args); //doesn't return
		printf("ARGH! DON'T RETURN!!\n");
	}else{

*/
			
		default : 
			BWindow::MessageReceived(message);			
			break;			

	}
}

bool TBuilderWindow::RunCmd(const char* ACommande)
{
	//ShowRunningBar(ACommande);
	system(ACommande);
	//HideRunningBar();
	return true;		
/*	expid=fork();
	if (expid==0)
	{
		execvp(ACommande,Args); //doesn't return
		return true;
	}
	else
	{
		DEBUGPRINT("RunCMD Failed...");
		return false;
	}
*/
}

bool TBuilderWindow::OpenFile(string truc)
{
	DEBUGPRINT("BuilderWindow::OpenFile Inside");
//	BMessage msg(B_ARGV_RECEIVED);
	BMessage msg(B_REFS_RECEIVED);	
	string AStr = FComponentProject->GetGenerationPath();
	DEBUGPRINT("BuilderWindow::OpenFile BEfore truc.length()>0");
	if (truc.length()>0)
	{
		DEBUGPRINT("BuilderWindow::OpenFile INSIDE truc.length()>0 "<<truc);
		AStr += truc;
		BEntry AnEntry(AStr.c_str());
		entry_ref ARef;
		AnEntry.GetRef(&ARef);
		msg.AddRef("refs",&ARef);
//	 	msg.AddString("argv", "BeIDE"); 	
//		msg.AddString("argv",AStr.c_str()); 
//		msg.AddInt32("argc", 2); 
		TBeBuilderOption ABeBuilderOption(PREFS_FILENAME);
//		ABeBuilderOption.FEditorMimeType = ((string *)FListMimeCode->ItemAt(Index))->c_str();
		
		BMessenger AMessengerBeIDE(ABeBuilderOption.FEditorMimeType.c_str()); 
		if (AMessengerBeIDE.IsValid()) 
		{ 
			DEBUGPRINT("BuilderWindow::OpenFile Before SendMessage");
			AMessengerBeIDE.SendMessage( &msg ); 
		} 
		else 
		{ 
			DEBUGPRINT("BuilderWindow::OpenFile Before be_roster->Launch");
			be_roster->Launch (ABeBuilderOption.FEditorMimeType.c_str(), &msg ); 
		} 		
		return true;
	}
	return false;
}
