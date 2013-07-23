/*********************************************
* Generated Code By BeBuilder Alpha Release V0.5.1                
* Written by Jerome Fillon (Softimedia Inc.) 
* Copyrights Jerome Fillon, Softimedia Inc.
**********************************************/
#ifndef __WindowOption_H__ 
#define __WindowOption_H__ 
#include <View.h>
#include <Window.h>
#include "BGeneralWindow.h"
#include "ViewOption.h"
#include <Application.h>

class TWindowOption: public BGeneralWindow
{
	public: 
		TWindowOption(char *AWindowTitle, BRect AFrame);
		~TWindowOption(void);
		void WindowActivated(bool active);
		bool QuitRequested(void);
		
		TViewOption *FViewOption;
};
#endif
