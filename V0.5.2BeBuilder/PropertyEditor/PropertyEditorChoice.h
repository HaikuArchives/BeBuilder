#ifndef __PROPERTY_EDITOR_CHOICE_H__ 
#define __PROPERTY_EDITOR_CHOICE_H__ 
#include <View.h>
#include <Window.h>
#include <Application.h>
//#include "Property.h"
#include <Handler.h>
#include "PropertyEditorWindow.h"
class TProperty;
class TPropertyEditorChoice: public TPropertyEditorWindow
{
	public: 
		TPropertyEditorChoice(char *AWindowTitle, BRect AFrame);
		~TPropertyEditorChoice(void);
		void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler);		
};
#endif
