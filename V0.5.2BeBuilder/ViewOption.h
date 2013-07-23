/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __ViewOption_H__ 
#define __ViewOption_H__ 
#include <MenuField.h>
#include <View.h>
#include "GlobalVar.h"
#include "EditorOption.h"
class TViewOption: public BView
{
	public:
		TViewOption(BRect AFrame);
		~TViewOption(void);
		void MessageReceived(BMessage *message);
		void AttachedToWindow(void);
		TEditorOption *FEditorOption;
};
#endif
