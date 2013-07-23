/*********************************************
* Generated Code By BeBuilder Pre-Alpha Release V0.4                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#include <TranslationUtils.h> 
#include <Bitmap.h> 
#include "OutlineListViewComponent.h"
#include "ScrollViewComponent.h"
#include "Component.h"
#include <image.h>
#include <Rect.h>
#include <string.h>
#include "AddOn.h"

//****************************************
extern "C" _EXPORT TComponent* GetInstance(const char *,const char *,BRect,TComponent *);
extern "C" _EXPORT BMessage *GetProperties(void);
//****************************************
TComponent* GetInstance(const char *AComponentName,const char *AClassName, BRect AFrame, TComponent *AFatherComponent)
{
  	return TScrollViewComponent::GetInstance(AComponentName,AClassName,AFrame,AFatherComponent);
}

BMessage *GetProperties(void)
{
	return TScrollViewComponent::GetProperties();
	/*
xres -o xmas x86.rsrc -a bits:666:xmas bmap newr4.jpg xmas x86.rsrc

Here, xmas x86.rsrc is the resource (if it doesn't exist, it will be created) and 
bits:666:xmas bitmap is the type:ID:name of the resource you're adding. (You can 
name these elements anything you want, but the name type 'bits' is a good choice for an 
image, as you'll see in a minute.) newr4.jpg and xmas x86.rsrc are the two files being 
merged. 
Now execute xres (you can type --help if you need more info) and add your resource file to 
the project file, if you haven't already done so. 
Next we need to do something with our image: 


#include <TranslationUtils.h> 
#include <Bitmap.h> 
... 



BBitmap *icon bitmap = 
  BTranslationUtils::GetBitmap("xmas bmap");	
	*/
	
}