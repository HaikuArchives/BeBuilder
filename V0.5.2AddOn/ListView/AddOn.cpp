/*********************************************
* Generated Code By BeBuilder Pre-Alpha Release V0.4                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include <TranslationUtils.h> 
#include <Bitmap.h> 
#include "ListViewComponent.h"
#include "ScrollViewComponent.h"
#include "Component.h"
#include <image.h>
#include <Rect.h>
#include <string.h>
#include "AddOn.h"

//****************************************
extern "C" _EXPORT TComponent* GetInstance(const char *,const char *,BRect,TComponent *);
extern "C" _EXPORT BMessage* GetProperties(void);
//****************************************
TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
/*	TListViewComponent *AListViewComponent;
	TScrollViewComponent *AScrollViewComponent;
	AFrame.left = 10;
	AFrame.top = 10;
	AFrame.right = 100;
	AFrame.bottom = 100;
  	AListViewComponent = new TListViewComponent(AComponentName,AClassName,AFrame,AFatherComponent); 	
	AScrollViewComponent = new TScrollViewComponent(AComponentName,AClassName,AFrame,AFatherComponent,AListViewComponent);
  	return AScrollViewComponent;
  	*/
  	return TScrollViewComponent::GetInstance(AComponentName,AClassName,AFrame,AFatherComponent);
}

BMessage* GetProperties(void)
{
	return TScrollViewComponent::GetProperties();
}