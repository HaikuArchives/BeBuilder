#ifndef __TOOLBAR_H__
#define __TOOLBAR_H__
#include <Application.h>
#include <stdio.h>
#include <PictureButton.h>
#include <Bitmap.h>
#include <string>
#include "BGeneralWindow.h"
#include "GlobalVar.h"
#include "Message.h"
#include "GeneralException.h"
//#include "StringList.h"
#include <List.h>
#include "Object.h"
#include "ToolBarView.h"

class TToolBar : public BGeneralWindow, public TObject
{
	public : 
		TToolBar(const char *Title,BRect frame, BHandler *AnAddOnManager);
		~TToolBar();
		bool ListButtonResize(float NewWidth);		
//		bool AddPictureButton(BBitmap *AnIcon, BBitmap *AnOffIcon,BMessage *AMessage);	
		bool AddPictureText(const char *AText,BMessage *AMessage,BHandler *AHandler);
		bool AddPictureButton(BBitmap *AnIcon, BBitmap *AnOffIcon,BMessage *AMessage,const char *AName);	
		BRect GetNextRect(BRect AnIconRect);
	private :
		BHandler *FAddOnManager;
		TToolBarView *FToolBarView;
		BList *FListButton;
		float FCurrentTop;
		float FCurrentBottom;
		float FMaxSize;
		bool QuitRequested(void);
};

#endif
