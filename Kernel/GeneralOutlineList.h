#ifndef __GENERALOUTLINELIST_H__
#define __GENERALOUTLINELIST_H__
#include <View.h>
#include <OutlineListView.h>
#include <ScrollView.h>
#include <stdio.h>
#include "GlobalVar.h"
//#include "BuilderMenu.h"
#include "Global.h"
#include "Couleur.h"

class TGeneralOutlineList : public BOutlineListView
//: public BWindow public TComponent
{
	public :
	TGeneralOutlineList(BRect frame, const char *name, list_view_type type = B_SINGLE_SELECTION_LIST, 
	 					uint32 resizingMode = B_FOLLOW_LEFT | B_FOLLOW_TOP, 
	 					uint32 flags = B_WILL_DRAW | B_FRAME_EVENTS | B_NAVIGABLE ); 
	void Draw(BRect ARect);	 					
	private :
    	void MouseDown(BPoint point);	
  		void KeyDown(const char *bytes, int32 numBytes);
		bool AddIndexToMessage(BMessage *AMessage);
  	
};

#endif