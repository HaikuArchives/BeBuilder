#include "MenuPropertyEditorChoice.h"
TMenuPropertyEditorChoice::TMenuPropertyEditorChoice(BRect AFrame,const char *AName)
: BMenuField(AFrame,AName,"",new BMenu(AName,B_ITEMS_IN_COLUMN),B_FOLLOW_LEFT | B_FOLLOW_TOP,B_ITEMS_IN_ROW)
{
	SetDivider(0.000000);
	SetEnabled(true);
}

TMenuPropertyEditorChoice::~TMenuPropertyEditorChoice(void)
{

}

void TMenuPropertyEditorChoice::MessageReceived(BMessage *message)
{
	switch(message->what)
	{
		default :
			 BMenuField::MessageReceived(message);
			break;
	}
}
void TMenuPropertyEditorChoice::AttachedToWindow(void)
{
	BMenuField::AttachedToWindow();
}
