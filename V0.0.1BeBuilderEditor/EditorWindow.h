#ifndef __EDITOR_WINDOW_H__
#define __EDITOR_WINDOW_H__

#include <Application.h>
#include <Messenger.h>
#include <Message.h>
#include <Window.h>
#include <stdio.h>
#include "EditorView.h"
#include "GlobalVar.h"


class TEditorWindow : public BWindow {
	public:
		TEditorWindow(BRect frame);
		TEditorWindow(BRect frame, entry_ref *ref);
		~TEditorWindow();
		virtual bool QuitRequested();
		virtual void MessageReceived(BMessage *message);
		virtual void FrameResized(float width, float height);
		virtual void GetEntryRef(entry_ref *ref);
		virtual bool Reload(entry_ref *ref);
		virtual bool GotoLine(int32 ALineNumber);
		virtual bool SelectText(int32 AStartOffset, int32 ALength);
		
	private:
		void _InitWindow(void);
		void Register(bool need_id);
		void Unregister(void);	
		int32 window_id;
		TEditorView *FEditorView;
		BEntry *FEntry;
};

#endif