#include "PropertyEditorChoice.h"
#include "PropertyEditorChoiceView.h"
#include "Property.h"
TPropertyEditorChoice::TPropertyEditorChoice(char *AWindowTitle, BRect AFrame)
//: BGeneralWindow("Choose Property",AFrame,PREFS_FILENAME,B_FLOATING_WINDOW)
:TPropertyEditorWindow(AWindowTitle,PROPERTY_EDITOR_CHOICE_POSITION,PREFS_FILENAME)
{
	FView = new TPropertyEditorChoiceView(Bounds());
	rgb_color kGray = {219,219,219,255};
	FView->SetViewColor(kGray);
	AddChild(FView);
}
TPropertyEditorChoice::~TPropertyEditorChoice(void)
{
}

void TPropertyEditorChoice::SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler)
{
	DEBUGPRINT("TPropertyEditorChoice::SetProperty Inside.");
	FView->SetProperty(AProperty,AnIndex,AHandler);
	DEBUGPRINT("TPropertyEditorChoice::SetProperty Quitting.");	
}
