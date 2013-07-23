#include "CodeFile.h"
TCodeFile::TCodeFile(const char *AFileName, const char *APath, const char *ASuffix):TObject("TCodeLine")
{
	FDebugMode = 0;
	FDebugMessage = "TCodeFile";
	ShowDebug("Inside ctor");
	SetFileNameAndPath(AFileName,APath,ASuffix);	
	ShowDebug(string("Quitting ctor PATH=") + FFilePath + string(" name=") + FFileName);
}


TCodeFile::~TCodeFile(void)
{
}

bool TCodeFile::SetFileNameAndPath(const char *AFileName, const char *APath, const char *ASuffix)
{
	string toto;
//	toto = APath ;
	toto = AFileName;
	
	if (ASuffix!=NULL)
	{
		toto = toto + ".";
		toto = toto + ASuffix;
		FSuffix = ASuffix;
	} 
	FFileName = toto;
	FFilePath = APath;
	FFileNameAndPath = APath + toto;
	return true;	
}

/*
bool TCodeFile::SetFileNameAndPath(string AFileNameAndPath)
{
	BPath APath(AFileNameAndPath.c_str());
	FFileName = APath.Leaf();
	APath.GetParent(&APath);
	FFilePath = APath.Path();
	return true;	
}
*/

const char *TCodeFile::GetFileName(void)
{
	return FFileName.c_str();
}

const char *TCodeFile::GetFilePath(void)
{
	return FFilePath.c_str();
}

bool TCodeFile::RenameFile(const char *AFileName)
{
	ShowDebug("Inside RenameFile");
	BEntry entry(FFileNameAndPath.c_str());
	FFileNameAndPath = 	FFilePath + AFileName;
	FFileName = AFileName;
	if (FSuffix.length()>0)
	{
		FFileNameAndPath += "." + FSuffix;
		FFileName += "." + FSuffix;
	}
	entry.Rename(FFileNameAndPath.c_str());	
	ShowDebug("RenameFile quitting.");
	return true;
}

BFile *TCodeFile::GetInstance(void)
{
//	BFile *AFichier;
//	AFichier = new BFile(FFileNameAndPath.c_str(),B_READ_WRITE | B_CREATE_FILE);
//	return AFichier;			
	return (new BFile(FFileNameAndPath.c_str(),B_READ_WRITE | B_CREATE_FILE));	
}

