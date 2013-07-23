#ifndef __CODE_FILE_H__
#define __CODE_FILE_H__
#include <string>
#include "Object.h"
#include <Path.h>
#include <File.h>

class TCodeFile : public TObject
{
	public :
//		TCodeFile(string AFileNameAndPath);
		TCodeFile(const char *AFileName, const char *APath, const char *ASuffix);
		
		virtual ~TCodeFile(void);
//		virtual bool SetFileNameAndPath(string AFileNameAndPath);	
		virtual bool SetFileNameAndPath(const char *AFileName, const char *APath, const char *ASuffix);
		virtual const char *GetFileName(void);					
		virtual const char *GetFilePath(void);
		virtual bool RenameFile(const char *AFileName);	
//		virtual BFile *GetInstance(const char * APath,const char *AFileName,const char *Suffixe); //Suffixe can be null
		virtual BFile *GetInstance(void);		
	protected :
		string FFileName;
		string FFilePath;
		string FFileNameAndPath;
		string FSuffix;
};

#endif