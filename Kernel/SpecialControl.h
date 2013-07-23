//------------------------------------------
// Electronic BizCardz enr.
// Copyright (C) 1998, All Rights Reserved.
//
// Created by Jerome Fillon 14-Sept-98
//------------------------------------------
#ifndef __SPECIAL_CONTROL_H__
#define __SPECIAL_CONTROL_H__
#include <Control.h>
#include "Global.h"
class SpecialControl : public BControl
{
	public:
		SpecialControl(BRect frame, 
	  				const char *name, 
         			const char *label, 
         			BMessage *message, 
         			uint32 resizingMode, 
         			uint32 flags);
		~SpecialControl(void);
		void SetDragMessage(BMessage *AMessage);		
		void MouseDown(BPoint point);
		void MouseMoved(BPoint point, 
					uint32 transit, 
					const BMessage *message);	
		//void MessageReceived(BMessage *message);
						
	private:
		BMessage *AMessage;
		BMessage *TheDragMessage;
};
#endif