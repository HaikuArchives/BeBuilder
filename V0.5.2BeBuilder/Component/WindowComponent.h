#ifndef __WINDOW_COMPONENT_H__
#define __WINDOW_COMPONENT_H__

#include <Window.h>
#include <Point.h>
#include <stdio.h>
#include "GlobalVar.h"
#include "Component.h" 
#include "WindowCodeGenerator.h"
#include "ViewComponent.h"

#define WINDOW_MENU_VALUE "Window"
#define WINDOW_VERSION_VALUE "1.0.0.0"
#define WINDOW_CLASS_VALUE "TWindowComponent"
#define WINDOW_COMPONENT_VALUE "AWindowComponent"
#define WINDOW_COPYRIGHTS_VALUE "(C)1999 Jerome Fillon Softimedia Inc."
#define WINDOW_WRITTEN_VALUE "Jerome Fillon, Softimedia Inc."
#define WINDOW_BITMAP_NAME "Icone" // depends on your resource file!
#define WINDOW_BITMAP_OFF_NAME "IconeOff" // depends on your resource file!


class TWindowComponent : public BWindow, public TComponent
{
	public :
//		TWindowComponent(const char *AComponentName,const char *AClassName,const char *ATitle, BRect AFrame);
		TWindowComponent(const char *AComponentName, const char *AClassName, BRect AFrame,TComponent *AFatherComponent);
		~TWindowComponent();
		void MessageReceived(BMessage *message);
		void WindowActivated(bool active);
		
		void FrameMoved(BPoint screenPoint);	
		void FrameResized(float width, float height);	
		BRect GetChildRect(const char *AClassName);			
		bool AddChild(TComponent *AComponent);
		bool RemoveChild(TComponent *AComponent);
		bool WhenRemoveChild(void);
				
		static BMessage* GetProperties(void);
		static TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent);
		bool ResizeAndMove(BRect ARect); 
		
//Loading and saving
//		BMessage *SaveData();
//		bool LoadData(BMessage *AMessage, BHandler *AGuiHandler); 
		
//		void AddChild(TViewComponent *AViewComponent);
		
//		void Generate(char *APathName);
	protected :
		bool ChangeProperty(string APropertyName, string APropertyValue);
	
};

#endif