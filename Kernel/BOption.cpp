#include "BOption.h"

BOption::BOption(const char *filename) : BMessage('pref') 
{ 
	//BFile file; 
	status = find_directory(B_COMMON_SETTINGS_DIRECTORY, &path); 
	if (status != B_OK) 
	{ 
		return; 
	} 
	path.Append(filename); 
	status = file.SetTo(path.Path(), B_READ_ONLY); 
	if (status == B_OK) 
	{ 
		status = Unflatten(&file); 
	} 	
} 

BOption::~BOption() 
{ 
	//BFile file; 
//	if (file.SetTo(path.Path(),B_WRITE_ONLY | B_CREATE_FILE) == B_OK) 
//	{ 
//		Flatten(&file); 
//	} 
} 

void BOption::ApplyUpdates(void) 
{ 
	if (file.SetTo(path.Path(),B_WRITE_ONLY | B_CREATE_FILE) == B_OK) 
	{ 
		Flatten(&file); 
	} 
} 


void BOption::SetBool(const char *name, bool ABool) 
{ 
	if (HasBool(name)) 
	{ 
		if (ReplaceBool(name, 0, ABool)!=B_OK)
		{
			GeneralException excep("ReplaceBool errors","BOption::SetBool",true);
//			throw(excep);
		} 
	} 
	else
	{
		if (AddBool(name, ABool)!=B_OK) 
		{
			GeneralException excep("AddBool errors","BOption::SetBool",true);
//			throw(excep);
		}
	}
} 


void BOption::GetBool(const char *name, bool *ABool) 
{ 
	if (HasBool(name)) 
	{ 
		if (FindBool(name,ABool)!=B_OK)
		{
			GeneralException excep("FindBool errors","BOption::GetBool",true);
//			throw(excep);
		}
	} 
	else
	{
		*ABool = false;
//		GeneralException excep("HasBool errors","BOption::GetBool");
//		throw(excep);
	}
} 

void BOption::SetString(const char *name, char *AStr) 
{ 
	if (HasString(name)) 
	{ 
		if (ReplaceString(name, 0, AStr)!=B_OK)
		{
			GeneralException excep("ReplaceString errors","BOption::SetString",true);
//			throw(excep);
		} 
	} 
	else
	{
		if (AddString(name, AStr)!=B_OK)
		{
			GeneralException excep("AddString errors","BOption::SetString",true);
//			throw(excep);
		} 
	}
} 

//----------------
// Astr should not be allocated... before calling this... memory leak.
//----------------
void BOption::GetString(const char *name, char **AStr) 
{ 
	const char *truc;
	if (HasString(name)) 
	{ 
		FindString(name,&truc);
		if (truc!=NULL)
		{
			*AStr = (char *) malloc(sizeof(char)*(strlen(truc)+1));
			strcpy(*AStr,truc);
		//	return true;
		}
		else
		{
			GeneralException excep("FindString errors","BOption::GetString",true);
//			throw(excep);
		}
	}
	else
	{ 
		*AStr = NULL;
//		GeneralException excep("HasString errors","BOption::GetString");
//		throw(excep);
	}
} 

void BOption::SetFloat(const char *name, float AFloat)
{
	if (HasFloat(name)) 
	{ 
		if (ReplaceFloat(name, 0, AFloat)!=B_OK)
		{
			GeneralException excep("ReplaceFloat errors","BOption::SetFloat",true);
//			throw(excep);
		} 
	}
	else
	{ 
		if (AddFloat(name, AFloat)!=B_OK) 
		{
			GeneralException excep("AddFloat errors","BOption::SetFloat",true);
//			throw(excep);
		}
	}

}

void BOption::GetFloat(const char *name, float *AFloat)
{
	if (HasFloat(name)) 
	{ 
		if (FindFloat(name,AFloat)!=B_OK)
		{
			GeneralException excep("FindFloat errors","BOption::GetFloat",true);
//			throw(excep);
		}
	} 
	else
	{
		*AFloat = 0;
	}
}
