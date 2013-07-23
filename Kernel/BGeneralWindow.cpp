//------------------------------------------
// Softimedia inc.
// Copyright (C) 1998, All Rights Reserved.
//
// Created by Jerome Fillon 12-Sept-98
//------------------------------------------
#include "BGeneralWindow.h"
BGeneralWindow::BGeneralWindow(const char *Title, BRect frame, const char *Prefs, window_type type, uint32 flags):BWindow(frame,Title,type,flags)
{	BRect rect;
	FTitre = Title;
	FPreferences = Prefs;	
	BGeneralWindowOption *truc;
	truc = new BGeneralWindowOption(Prefs,Title);
	rect.left = truc->Left;
	rect.top = truc->Top;
	rect.right = truc->Right;
	rect.bottom = truc->Bottom;
	delete truc;
	float larg = rect.right-rect.left;
	float haut = rect.bottom-rect.top;
//	if ((larg<1024) && (haut<768))
	if (larg==0)
		larg = 200;
	if (haut==0)
		haut = 200;
	if ((rect.left>0) && (rect.right>0) && (rect.top>0) && (rect.bottom>0))
	{
		MoveTo(rect.left,rect.top);
		ResizeTo(larg,haut);	
		SetTitle(Title);
	}
//	printf("Loading Windows %s Top: %f Left: %f Right: %f Bottom: %f \n",Title,rect.top,rect.left,rect.right,rect.bottom);
}

BGeneralWindow::~BGeneralWindow(void)
{
	BRect rect;
	rect = Frame();
	BGeneralWindowOption *truc;

	truc = new BGeneralWindowOption(FPreferences.c_str(),FTitre.c_str());
	truc->Left = rect.left;
	truc->Top = rect.top;
	truc->Right = rect.right;
	truc->Bottom = rect.bottom;
	try
	{
		truc->ApplyUpdates();
	}
	catch(GeneralException &e)
	{
		printf("Exception! %s in %s \n",e.Message.c_str(),e.Location.c_str());
	}
	//printf("Saving Windows %s Top: %f Left: %f Right: %f Bottom: %f \n",Title(),truc->Top,truc->Left,truc->Right,truc->Bottom);
	delete truc;
}

bool BGeneralWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return (TRUE);
}


		
