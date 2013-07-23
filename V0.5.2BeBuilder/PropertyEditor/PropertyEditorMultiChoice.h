/*********************************************
* Generated Code By BeBuilder Pre-Alpha Release V0.4                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __PROPERTY_EDITOR_MULTI_CHOICE_H__ 
#define __PROPERTY_EDITOR_MULTI_CHOICE_H__ 
#include <View.h>
#include <Window.h>
#include <Application.h>
#include "Property.h"
//#include "PropertyEditorMultiChoiceView.h"
//#include "BGeneralWindow.h"
#include "PropertyEditorWindow.h"
//class TPropertyEditorMultiChoice: public BGeneralWindow
class TPropertyEditorMultiChoice: public TPropertyEditorWindow
{
	public: 
		TPropertyEditorMultiChoice(char *AWindowTitle, BRect AFrame);
		~TPropertyEditorMultiChoice(void);
		void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler);
		
};
#endif
