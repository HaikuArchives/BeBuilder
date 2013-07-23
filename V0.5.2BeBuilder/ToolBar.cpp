#include "ToolBar.h"

TToolBar::TToolBar(const char *Title,BRect frame, BHandler *AnAddOnManager)
:BGeneralWindow(Title,frame,PREFS_FILENAME,B_FLOATING_WINDOW,B_NOT_RESIZABLE),TObject("ToolBar")
{
	FDebugMode = 1;
	FDebugMessage= "TToolBar ";
	
	FToolBarView = new TToolBarView(Bounds());
//	FView = new TPropertyEditorStandardView(Bounds());
	AddChild(FToolBarView);
	FAddOnManager = AnAddOnManager;
	FListButton = new BList(20);

	FCurrentTop = 0;
	FCurrentBottom = 0;
	FMaxSize = 0;
}

TToolBar::~TToolBar()
{
	ShowDebug("TToolBar destructor Inside");		
	void *AnItem;
	for (int32 ind=0; AnItem = FListButton->ItemAt(ind); ind++)
	{
		FToolBarView->RemoveChild((BPictureButton *)AnItem);
		delete AnItem;
	}
	delete FListButton;
//	RemoveChild(FToolBarView);
//	FToolBarView->RemoveSelf();
//	delete FToolBarView;
	ShowDebug("TToolBar destructor Quitting");		
}	

bool TToolBar::ListButtonResize(float NewWidth)
{
	BButton *ATempButton;
	BRect ARect; 
	for (int32 ind=0; ind<FListButton->CountItems();ind++)
	{
		ATempButton = (BButton *)FListButton->ItemAt(ind);
		ARect = ATempButton->Bounds();
		ATempButton->ResizeTo(NewWidth,ARect.bottom - ARect.top);
	}
	return true;
}

bool TToolBar::AddPictureText(const char *AText,BMessage *AMessage,BHandler *AHandler)
{
	if (LockLooper())
	{
		ShowDebug(string("TToolBar::AddPictureText top=") + FloatToStr(FCurrentTop));
		BButton *ATempButton = new BButton(BRect(0,FCurrentTop,100,FCurrentTop + 10),"temp",AText,AMessage,B_FOLLOW_NONE,B_WILL_DRAW | B_NAVIGABLE);
		ATempButton->SetTarget(AHandler);
		ATempButton->ResizeToPreferred();
		FListButton->AddItem(ATempButton);
		FToolBarView->AddChild(ATempButton);
		BRect truc = ATempButton->Frame();
		FCurrentTop = truc.bottom;
		if (FMaxSize < (truc.right - truc.left))
		{
			FMaxSize = (truc.right - truc.left);
//			BRect ARectWin = Frame();
//			ResizeTo(FMaxSize,(ARectWin.bottom-ARectWin.top));
//			ResizeTo(FMaxSize,(truc.bottom));
			ListButtonResize(FMaxSize);
		}
		ATempButton->ResizeTo(FMaxSize,truc.bottom - truc.top);
		ResizeTo(FMaxSize,(truc.bottom));
		UnlockLooper();
		return true;
	}		
	return false;
}

bool TToolBar::AddPictureButton(BBitmap *AnIcon, BBitmap *AnOffIcon,BMessage *AMessage,const char *AName)	
{
	ShowDebug("AddPictureButton Inside");
	BPictureButton *APictureButton;
	
	BView *ATempView = new BView(BRect(0,0,100,100),"temp",B_FOLLOW_NONE,B_WILL_DRAW);
	AddChild(ATempView);
	ShowDebug("AddPictureButton ATempView has been added.");

	BPicture *AOnPicture;
	ShowDebug("AddPictureButton Before BeginPicture.");
	ATempView->BeginPicture(new BPicture);
	if (AnIcon==NULL)
		ShowDebug("AddPictureButton Before DrawBitmap. AnIcon is NULL.");

	int32 longueur = AnIcon->BitsLength();
	ShowDebug(string("AddPictureButton Before DrawBitmap. Longueur=") + IntToStr(longueur));

	ATempView->DrawBitmap(AnIcon);
	ShowDebug("AddPictureButton After DrawBitmap.");
	AOnPicture = ATempView->EndPicture();
	ShowDebug("AddPictureButton After EndPicture.");

	BPicture *AOffPicture;
	ATempView->BeginPicture(new BPicture);
	ATempView->DrawBitmap(AnOffIcon);
	AOffPicture = ATempView->EndPicture();
   	RemoveChild(ATempView);
   	delete ATempView;

	BRect ARect = GetNextRect(AnIcon->Bounds());
	ShowDebug("AddPictureButton Before creating APictureButton.");
	APictureButton = new BPictureButton(ARect,
										AName,AOffPicture,AOnPicture,AMessage,
										B_ONE_STATE_BUTTON, B_FOLLOW_LEFT | B_FOLLOW_TOP,
										B_WILL_DRAW | B_NAVIGABLE );
	APictureButton->SetTarget(FAddOnManager);
	FToolBarView->AddChild(APictureButton);

	//FListButton->Add();	
	ShowDebug("AddPictureButton Before AddItem.");
	FListButton->AddItem(APictureButton);
	return true;
}

BRect TToolBar::GetNextRect(BRect AnIconRect)
{
	
/*	BPictureButton *APictureButton;
	BRect AViewRect = Bounds();
	BRect ARect;
	int CurrentTop = AViewRect.top;
	int CurrentLeft = AViewRect.left;
	for (int index=0;
	 index<FListButton->CountItems(); index++)
	{
		APictureButton = FListButton->ItemAt(index);
		ARect = APictureButton->Bounds();			
		if ((CurrentLeft + ARect.right) <= (AViewRect.right))
		{
						
		}
	}	
*/
	return BRect(0,0,50,50);
}

/*
void TToolBar::MessageReceived(BMessage *message)
{

	switch (message->what)
	{
		default: BWindow::MessageReceived(message);			
	}
}
*/

bool TToolBar::QuitRequested(void)
{
//	be_app->PostMessage(B_QUIT_REQUESTED);
	// I don't want to have the normal BGeneralWindow feature!
	Hide();
	return false;
}
