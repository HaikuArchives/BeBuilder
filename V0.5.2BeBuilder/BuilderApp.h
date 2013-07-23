#include <Application.h>
#include <Window.h>
#include "BuilderWindow.h"
#include "Global.h"

class TBuilderApp : public BApplication 
{
	public:
		TBuilderApp();
		void RefsReceived( BMessage *msg );		
//				void MessageReceived(BMessage *message);
	private:
	//	BWindow		*BizWindow;
		TBuilderWindow	*BizWindow;
	
};