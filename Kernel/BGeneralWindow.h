#ifndef __BGENERAL_WINDOW_H__
#define __BGENERAL_WINDOW_H__
#include <Window.h>
#include "BGeneralWindowOption.h"
#include "GeneralException.h"
#include <string>
#include <Application.h>
//#include <Application.h>
class BGeneralWindow : public BWindow
{
	public:
		BGeneralWindow(const char *Title,BRect frame, const char *Prefs, window_type type, uint32 flags);
//		BGeneralWindow(const char *Title,BRect frame, const char *Prefs, window_type type, int flags);
		~BGeneralWindow(void);
		bool QuitRequested(void);
	private:
		std::string FTitre;
		std::string FPreferences;
};
#endif
