/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __TBeBuilderEditor_H__ 
#define __TBeBuilderEditor_H__ 
#include <Application.h>
#include "GlobalVar.h"
#include "EditorWindow.h"
BRect AWindowRect(100,100,399,299);

class TBeBuilderEditor : public BApplication 
{
	public:
		TBeBuilderEditor(void);
		virtual void MessageReceived(BMessage *message);		
		virtual void RefsReceived( BMessage *msg );
		virtual TEditorWindow *FindEditorWindow(entry_ref *ref);
	private:
		int32			FWindowCount;
		int32			FNextUntitledNumber;
		
//		BFilePanel		*FOpenPanel;
//		BFilePanel		*FSavePanel;		
		BList 			*FListWindow;
		TEditorWindow *FEditorWindow;
		
};
#endif
