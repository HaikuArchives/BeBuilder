#ifndef __TOOLBAR_VIEW_H__
#define __TOOLBAR_VIEW_H__
#include <View.h>
#include <Button.h>
#include <TextControl.h>
#include "GlobalVar.h"
#include "Global.h"
#include "Couleur.h"
#include "StringList.h"
#include <string>
#include "PropertyEditorView.h"
class TToolBarView : public BView
{
	public :
		TToolBarView(BRect frame);
		virtual ~TToolBarView();
//		virtual void SetProperty(TProperty *AProperty,int32 AnIndex,BHandler *AHandler){};
};

#endif