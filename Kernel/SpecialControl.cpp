//------------------------------------------
// Electronic BizCardz enr.
// Copyright (C) 1998, All Rights Reserved.
//
// Created by Jerome Fillon 14-Sept-98
//------------------------------------------
#include "SpecialControl.h"

SpecialControl::SpecialControl(BRect frame, 
	const char *name, const char *label, 
	BMessage *message, uint32 resizingMode, 
    uint32 flags):BControl(frame,name,label,message,resizingMode,flags)
{
	AMessage = new BMessage(message);
	TheDragMessage = NULL;
}

SpecialControl::~SpecialControl(void)
{
	;
}

void SpecialControl::SetDragMessage(BMessage *AMessage)	
{
	if (TheDragMessage==NULL)
	{
		delete TheDragMessage;
	}
	TheDragMessage = new BMessage(AMessage);	
}

void SpecialControl::MouseDown(BPoint point)
{
	BMessage MyMessage(AMessage);
	MyMessage.AddString("SpecialName","MOUSE_DOWN");
	MyMessage.AddPoint("TheImpactPoint",point);
	Invoke(&MyMessage);
}

void SpecialControl::MouseMoved(BPoint point, uint32 transit, const BMessage *message)
{
	BPoint point2;
	uint32 buttons;
//      void GetMouse(BPoint *cursor, uint32 *buttons, bool checkQueue = true) 
	GetMouse(&point2, &buttons, true); 

	if (buttons == B_PRIMARY_MOUSE_BUTTON) 
	{
	//	B_SECONDARY_MOUSE_BUTTON 
	//	B_TERTIARY_MOUSE_BUTTON 
		//ShowMessage("MouseMoved...Launching DragMessage...");
		BMessage ADragMessage(TheDragMessage);
		BRect ARect(0,0,20,20);
		DragMessage(&ADragMessage,ARect); 
	}
}
/*
    void DragMessage(BMessage *message, BBitmap *image, BPoint point, 
         BHandler *replyTarget = NULL) 
*/


