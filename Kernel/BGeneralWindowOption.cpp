#include "BGeneralWindowOption.h"

BGeneralWindowOption::BGeneralWindowOption(const char *filename,const char *WindowName):BOption(filename)
{
	try
	{
		if (WindowName!=NULL)
		{
			TheWindowName = WindowName;
			std::string final("");
			final = TheWindowName + "_Top";
			GetFloat(final.c_str(),&Top);
			final = TheWindowName + "_Bottom";
			GetFloat(final.c_str(),&Bottom);
			final = TheWindowName + "_Left";
			GetFloat(final.c_str(),&Left);
			final = TheWindowName + "_Right";
			GetFloat(final.c_str(),&Right);	
					
		}
		else
		{
			GetFloat("Top",&Top);
			GetFloat("Bottom",&Bottom);
			GetFloat("Left",&Left);
			GetFloat("Right",&Right);	
		}
	}
	catch(...)
	{
		ShowMessage("Exception in BGeneralWindowOption constructor... not finished! ask Jerome.");
	}
}

BGeneralWindowOption::~BGeneralWindowOption(void)
{
	; //Nothing for the moment but who knows?
}

void BGeneralWindowOption::ApplyUpdates(void)
{
	try
	{
		//ShowMessage("BGeneralWindowOption ",TheWindowName.data())
		if (TheWindowName.length()>0)
		{
			std::string final("");
			final = TheWindowName + "_Top";
			SetFloat(final.c_str(),Top);
			final = TheWindowName + "_Bottom";
			SetFloat(final.c_str(),Bottom);
			final = TheWindowName + "_Left";
			SetFloat(final.c_str(),Left);
			final = TheWindowName + "_Right";
			SetFloat(final.c_str(),Right);			
		}
		else
		{
			SetFloat("Top",Top);
			SetFloat("Bottom",Bottom);
			SetFloat("Left",Left);
			SetFloat("Right",Right);	
		}
		BOption::ApplyUpdates();
	}
	catch(...)
	{
		ShowMessage("Exception in BGeneralWindowOption Applyupdates... not finished! ask Jerome.");
	}

} 	

