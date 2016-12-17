#include "BeBuilderOption.h"

TBeBuilderOption::TBeBuilderOption(const char *filename):BOption(filename)
{
	char *truc = NULL;
	GetString("EditorMimeString",&truc);
	if (truc!=NULL)
		FEditorMimeType = truc;
}

TBeBuilderOption::TBeBuilderOption(void):BOption("")
{
	//We use the static var...
}


void TBeBuilderOption::ApplyUpdates(void)
{
	try
	{
		SetString("EditorMimeString",(char *)FEditorMimeType.c_str());
		BOption::ApplyUpdates();
	}
	catch(...)
	{
//		ShowMessage("Exception in BGeneralWindowOption Applyupdates... not finished! ask Jerome.");
	}

} 	

