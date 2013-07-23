#ifndef __MENU_COMPONENT_H__
#define __MENU_COMPONENT_H__

#include <Menu.h>
#include <stdio.h>
#include "Component.h" 
#include "GlobalVar.h"
#include "MenuCodeGenerator.h"
#include "ViewComponent.h"
#include <Point.h>
class TMenuComponent : public BMenu, public TComponent
{
	public :
		TMenuComponent(const char *AComponentName, const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		~TMenuComponent();
		void MessageReceived(BMessage *message);
//		void FrameMoved(BPoint screenPoint);		
//		void MouseDown(BPoint point);
};

#endif