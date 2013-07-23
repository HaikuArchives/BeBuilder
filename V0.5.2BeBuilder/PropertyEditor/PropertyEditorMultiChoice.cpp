#include "PropertyEditorMultiChoice.h"
#include "PropertyEditorMultiChoiceView.h"
TPropertyEditorMultiChoice::TPropertyEditorMultiChoice(char *AWindowTitle, BRect AFrame)
//: BGeneralWindow(AFrame,AWindowTitle,B_TITLED_WINDOW,0)
//: BGeneralWindow("Choose Property",AFrame,PREFS_FILENAME,B_FLOATING_WINDOW)
: TPropertyEditorWindow(AWindowTitle,PROPERTY_EDITOR_MULTI_POSITION,PREFS_FILENAME)
{
	FView = new TPropertyEditorMultiChoiceView(Bounds());
	rgb_color kGray = {219,219,219,255};
	FView->SetViewColor(kGray);
	AddChild(FView);
}
TPropertyEditorMultiChoice::~TPropertyEditorMultiChoice(void)
{
}
void TPropertyEditorMultiChoice::SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler)
{
	DEBUGPRINT("TPropertyEditorMultiChoice::SetProperty Inside.");
	FView->SetProperty(AProperty,AnIndex,AHandler);
	DEBUGPRINT("TPropertyEditorMultiChoice::SetProperty Quitting.");
}

