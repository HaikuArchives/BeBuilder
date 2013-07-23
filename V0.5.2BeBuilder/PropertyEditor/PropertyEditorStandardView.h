#ifndef __PROPERTY_EDITOR_STANDARD_VIEW_H__
#define __PROPERTY_EDITOR_STANDARD_VIEW_H__
#include <View.h>
#include <Button.h>
#include <TextControl.h>
#include "GlobalVar.h"
#include "Global.h"
#include "Couleur.h"
#include "StringList.h"
#include <string>
#include "PropertyEditorView.h"
class TProperty;
class TPropertyEditorStandardView : public TPropertyEditorView
{
	public :
		TPropertyEditorStandardView(BRect frame);
		virtual ~TPropertyEditorStandardView();
		virtual void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler){};
};

#endif