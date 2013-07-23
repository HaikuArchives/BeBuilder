#ifndef __WINDOW_CODE_GENERATOR_H__
#define __WINDOW_CODE_GENERATOR_H__
#include "CodeGenerator.h"
#include "ComponentList.h"
#include "GlobalVar.h"
#include "CodeLine.h"
#include <Entry.h>
//#include "WindowComponent.h"
class TWindowComponent;
class TWindowCodeGenerator : public TCodeGenerator
{
	public :
		TWindowCodeGenerator(TWindowComponent * AWindowComponent,bool CanCreateSourceFile);
//		void GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP);
		void GenerateAll(const char *APath,const char *ClassName);
//---------NEW FUNCTION----------
//		bool SkeletonCPP(TFileRW *AFileRW);
//		bool SkeletonH(TFileRW *AFileRW);
//		bool InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);
		//bool InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);
//-------- Dynamic Code --------------
		bool CreateBody(bool ReallyWriteInFile = true);
		bool CreateHeader(bool ReallyWriteInFile = true);
		bool CreateMakeFile(bool ReallyWriteInFile = true);
		bool CreateConstructeur(bool ReallyWriteInFile = true);
		bool PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile = true);
		
//------------------------------------

	private :
		TWindowComponent *FWindowComponent;
// All the CodeLine that could be needed!
		TCodeLine *FBodyLine;
		TCodeLine *FHeaderLine;
		TCodeLine *FMakeFileLine;
		TCodeLine *FHeaderConstructeurLine1;		
		TCodeLine *FHeaderConstructeurLine2;		
		TCodeLine *FBodyConstructeurLine1;		
		TCodeLine *FBodyConstructeurLine2;		
		
};

#endif