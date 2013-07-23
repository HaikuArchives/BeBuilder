#ifndef __PROJECT_CODE_GENERATOR_H__
#define __PROJECT_CODE_GENERATOR_H__
#include "CodeGenerator.h"
#include "ComponentList.h"
#include "CodeFile.h"
#include "CodeLine.h"
#include <Entry.h>
class TProjectComponent;
class TProjectCodeGenerator : public TCodeGenerator
{
	public :
		TProjectCodeGenerator(TProjectComponent * AProjectComponent,bool CanCreateSourceFile);
		void GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP);
		void GenerateAll(const char *APath,const char *ClassName);
		bool SkeletonCPP(TFileRW *AFileRW);
		bool SkeletonH(TFileRW *AFileRW);
		bool SkeletonMakeFile(TFileRW *AFileRW);
//-------- Dynamic Code --------------
		bool CreateBody(bool ReallyWriteInFile = true);
		bool CreateHeader(bool ReallyWriteInFile = true);
		bool CreateMakeFile(bool ReallyWriteInFile = true);
		bool PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile = true);
		
//------------------------------------	
	private :
		TProjectComponent *FProjectComponent;
// All the CodeLine that could be needed!
		TCodeLine *FBodyLine;
		TCodeLine *FHeaderLine;
		TCodeLine *FMakeFileLine;
		
};

#endif