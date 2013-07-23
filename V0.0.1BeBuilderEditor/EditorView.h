#ifndef __EDITOR_VIEW_H__
#define __EDITOR_VIEW_H__
#include <Application.h>
#include <ScrollView.h>
#include <View.h>
#include <string>
#include <Path.h>
#include <Entry.h>
#include <FilePanel.h>
#include <Alert.h>
#include "Edit.h"
#include "EditorMenu.h"
#include "GlobalVar.h"

class TEditorView : public BView 
{
	public:
		TEditorView(BRect frame);
		TEditorView(BRect frame, entry_ref *ref);
		bool LoadText(entry_ref *ref);
		bool CanCloseBuffer(bool ForceSave);
		~TEditorView();
		void MessageReceived(BMessage *message);
		virtual void	FrameResized(float width, float height);
		status_t		Save(BMessage *message);
		bool	SetTitle(const char * ATitle);
		const char * GetTitle(void);
		BEntry	*GetEntry(void);
		bool GotoLineNumber(int32 ALineNumber);
		bool SelectText(int32 AStartOffset, int32 ALength);		
		bool WaitForSaveToBeDone(void);
		
	private:
		virtual bool _InitView(void);
		float GetHauteurMenu(void);
		BMessage		*savemessage;
		string FTitle;
		BScrollView *FScrollView;
		BEntry *FEntry;
		
		TEdit *FEdit;
		TEditorMenu *FEditorMenu;

		BFilePanel *FOpenPanel;
		BFilePanel *FSavePanel;
		BLocker *FLocker;
};

#endif