#ifndef __BUILDERVIEW_H__
#define __BUILDERVIEW_H__
#include <View.h>
#include <OutlineListView.h>
#include <ScrollView.h>
#include "GlobalVar.h"
#include "BuilderMenu.h"
#include "Global.h"
#include "Couleur.h"
#include "GeneralOutlineList.h"
#include "ToolWindow.h"
#include "ComponentItem.h"
#include <Application.h>

class TBuilderView : public BView
{
	public :
		TGeneralOutlineList *FOutListe;
		TBuilderView(BRect frame);
		~TBuilderView();
		void SendPropertyMessage(TComponentItem *AComponentItem);
	private :
		BScrollView *FScrollView;
		TToolWindow *FToolWindow;
		void AttachedToWindow(void);		
	
	
};
#endif