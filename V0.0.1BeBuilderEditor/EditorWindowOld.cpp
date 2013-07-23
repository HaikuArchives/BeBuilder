/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include "EditorWindow.h"

TEditorWindow::TEditorWindow(char *AWindowTitle, BRect AFrame): BWindow(AFrame,AWindowTitle,B_TITLED_WINDOW,0)
{
	FEditorMenu = new TEditorMenu(BRect(0,0,AFrame.right,HAUTEUR_MENU));
	AddChild(FEditorMenu);
	BRect ARect = Bounds();
	ARect.top = HAUTEUR_MENU;
	FNBTab = 0;


/*
	FTabView = new TEditorTabView(ARect,"FTabView");
//	FTabView = new TabView(ARect,"FTabView",Nom,4);
	AddChild(FTabView);
	FListEditorTab = new BList();
	FTabView->SetListTab(FListEditorTab);
	*/
	ARect.bottom = ARect.top + 40; 
	FEasyTabView = new TEasyTabView(ARect,"EasyTabView");
	AddChild(FEasyTabView);

}
TEditorWindow::~TEditorWindow(void)
{
}

bool TEditorWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return (TRUE);
}

void TEditorWindow::MessageReceived(BMessage *message)
{
	entry_ref open_ref;
	switch(message->what)
	{
		case B_OPEN:
		case B_REFS_RECEIVED:
		case B_SIMPLE_DATA:
			DEBUGPRINT("Before AddTabView()");
			if (message->FindRef("refs",&open_ref)!= B_OK)
			{
				DEBUGPRINT("TEditorWindow::MessageReceived B_SIMPLE_DATA cannot find refs.");
				break;
			}
			AddTabView(&open_ref);		
//			AddView(&open_ref);		
			DEBUGPRINT("AddTabView() done!");
			break;
		default :
			BWindow::MessageReceived(message);
			break;
	}
}


bool TEditorWindow::AddTabView(entry_ref *ref)
{
	BEntry entry(ref);
	if (!entry.Exists())
		return false;

	// open the file
	BFile file(&entry, B_READ_ONLY);
	if (file.InitCheck() != B_OK)
	{
		// could not open so report an error
		BPath path(&entry);
		string truc="";
		if (path.InitCheck() == B_OK)
		{
			truc = "Could not open ";
			truc = truc + path.Path();
		}
		else
			truc = "Could not open ";

		BAlert *alert = new BAlert("File Failure", truc.c_str(), "Sorry!");
		alert->Go(NULL);
		return false ;
	}
	else
	{
			DEBUGPRINT("TEditorWindow::AddTabView fEdit is not null. Long_Max="<<LONG_MAX);
			// read up to LONG_MAX bytes of the file into the text view
			off_t size = 0;
			file.GetSize(&size);
			int32 sizeToRead = min_c(size, (off_t)LONG_MAX);
//			fEdit->SetText(&file, 0, sizeToRead);
/*
			BRect ARect = FTabView->GetContentArea();

			TEditorTab *AnEditorTab = new TEditorTab(ARect);
			FListEditorTab->AddItem(AnEditorTab);
			FTabView->AddViews((BView **)&AnEditorTab);
*/
			/* //EditorTabView's case...
			BRect ARect = FTabView->Bounds();

			ARect.InsetBy(5,5);
			ARect.bottom -= FTabView->TabHeight();
			TEditorTab *AnEditorTab = new TEditorTab(ARect);
			AnEditorTab->SetText(&file,0,sizeToRead);
//			FListEditorTab->AddItem(AnEditorTab);
			
			BTab *ATab = new BTab(AnEditorTab);	
//			BTab *ATab = new BTab();	

//			FListEditorTab->AddItem(ATab);
			
			FTabView->AddTab(AnEditorTab,ATab);

			
			FNBTab ++;
//			FTabView->AddTab(AnEditorTab,NULL);
//			AnEditorTab->Draw(ARect);
//			FTabView->DrawTabs();

			BPath path(&entry);
			if (path.InitCheck() == B_OK)
				ATab->SetLabel(path.Leaf());

			FTabView->Select(0);
			
//			ATab->Deselect();
//			ATab->Select(FTabView);

//			ATab->DrawTab((BView *)FTabView,ARect,B_TAB_FIRST,true);

//			ARect = FTabView->DrawTabs();
//			FTabView->Draw(ARect);
//			FTabView->DrawBox(ARect);

			// set the title to the name of the file	
//				*/

//			/* //EasyTabView's case...
			BRect ARect = FEasyTabView->Bounds();

			ARect.InsetBy(5,5);
			ARect.bottom -= FEasyTabView->TabHeight();
			
			TEditorTab *AnEditorTab = new TEditorTab(ARect);
			AnEditorTab->SetText(&file,0,sizeToRead);
			BPath path(&entry);
			if (path.InitCheck() == B_OK)
			{
//				ATab->SetLabel(path.Leaf());
				FEasyTabView->AddTab(AnEditorTab,path.Leaf());
			}
			
			FNBTab ++;
			FEasyTabView->Draw(FEasyTabView->Bounds());
//			FTabView->Select(0);

			// set the title to the name of the file	
	//			*/



	}


/*
    r = tabView->Bounds(); 
      r.InsetBy(5,5); 
      r.bottom -= tabView->TabHeight(); 
      tab = new BTab(); 
      tabView->AddTab(new ConstView(r), tab); 
      tab->SetLabel("Construct"); 
      tab = new BTab(); 
      tabView->AddTab(new DestView(r), tab); 
      tab->SetLabel("Obliterate");
*/	
/*
virtual void AddTab(BView *target, BTab *tab = NULL) 
virtual BTab *RemoveTab(int32 tab_index) 
*/	
	return true;
}

void TEditorWindow::FrameResized(float width, float height)
{
/*
//	for (int32 ind=0; ind<FListEditorTab->CountItems(); ind++)
	for (int32 ind=0; ind<FNBTab; ind++)
	{
		DEBUGPRINT("TEditorWindow::FrameResized() ind="<<ind << " w: "<<width<<" h: "<<height);
//		BRect ARect = FTabView->TabFrame(ind);	
//		ARect.PrintToStream();

//		FTabView->Select(ind);		
//		((TEditorTab *)FListEditorTab->ItemAt(ind))->FrameResized(width,height);

		BTab *ATab = NULL;
//		ATab = ((BTab *)FListEditorTab->ItemAt(ind));
		FTabView->Select(ind);
		BRect ARect = FTabView->DrawTabs();
		ARect.PrintToStream();
		
		FTabView->DrawBox(ARect);
		
		ATab = ((BTab *)FTabView->TabAt(ind));	
		
		if (ATab!=NULL)
		{
			BView *AView = NULL;
//			TEditorTab *AView = NULL;
//			AView = (TEditorTab *)(ATab->View());
			AView = ATab->View();
			ATab->SetView(NULL);
			if (AView != NULL)
			{
				BRect ARect = AView->Bounds();	
				ARect.PrintToStream();
				
				ARect = AView->Frame();	
				ARect.PrintToStream();
				AView->Show();
//				AView->ResizeToPreferred();
				AView->FrameResized(width,height);
				
				ATab->SetView(AView);
			}
		}
		
	}
*/
	BWindow::FrameResized(width,height);	
}
bool TEditorWindow::RemoveTabView(void)
{
	return true;
}


