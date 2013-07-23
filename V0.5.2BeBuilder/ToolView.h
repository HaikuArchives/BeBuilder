#ifndef __TOOLVIEW_H__
#define __TOOLVIEW_H__
#include <View.h>
#include <OutlineListView.h>
#include <ScrollView.h>
#include "GlobalVar.h"
#include "Global.h"
#include "Couleur.h"
#include "GeneralOutlineList.h"

class TToolView : public BView
//: public BWindow public TComponent
{
	public :
//		BOutlineListView *FOutListe;
		TGeneralOutlineList *FOutListe;
		TToolView(BRect frame);
		~TToolView();
	private :
//		TBuilderMenu *FBuilderMenu;
		void AttachedToWindow(void);		
		void MessageReceived(BMessage *message);	
};

#endif