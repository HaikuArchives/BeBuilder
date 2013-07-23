/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __TEditorWindow_H__ 
#define __TEditorWindow_H__ 
#include <Window.h>
#include <Application.h>
//#include <TabView.h>
#include "EditorTabView.h"
#include "EasyTabView.h"
#include <Path.h>
#include <Alert.h>
#include <string>
#include <TabView.h>
#include "EditorMenu.h"
#include "GlobalVar.h"
//#include "pEdit.h"
#include "EditorTab.h"
#include "TabView.h"
class TEditorWindow: public BWindow
{
	public: 
		TEditorWindow(char *AWindowTitle, BRect AFrame);
		~TEditorWindow(void);
		bool QuitRequested(void);
		void MessageReceived(BMessage *message);
		bool AddTabView(entry_ref *ref);
		void FrameResized(float width, float height);		
		bool RemoveTabView(void);		
	private:
		TEasyTabView *FEasyTabView;
		TEditorMenu *FEditorMenu;
		TEditorTabView *FTabView;
//		TabView *FTabView;
		BList *FListEditorTab;
		int32 FNBTab;
		
};
#endif
