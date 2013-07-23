#ifndef __EDIT_H__
#define __EDIT_H__

#include <TextView.h>
#include <Message.h>
#include <Messenger.h>
#include "GlobalVar.h"
class TEdit : public BTextView
{
	public:
		TEdit(const char *name,BRect AFrame, BRect ATextFrame);
		~TEdit();
		void MessageReceived(BMessage *message);
		bool SetTarget (BHandler *AHandler);
		void InsertText(const char *text, int32 length, int32 offset, const text_run_array *runs);
		void DeleteText(int32 start, int32 finish);
		bool GetModified(void);
		bool SetModified(bool AValue);
	private:
		BHandler *FTarget;
		bool FModified;
};
#endif
