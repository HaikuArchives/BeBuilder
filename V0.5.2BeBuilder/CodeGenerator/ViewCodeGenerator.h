#ifndef __VIEW_CODE_GENERATOR_H__
#define __VIEW_CODE_GENERATOR_H__
#include "CodeGenerator.h"
#include <Entry.h>
class TViewComponent;
class TViewCodeGenerator : public TCodeGenerator
{
	public :
		TViewCodeGenerator(TViewComponent * AViewComponent,bool CanCreateSourceFile);
//		void GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP);
//---------NEW FUNCTION----------
//		bool SkeletonCPP(TFileRW *AFileRW);
//		bool SkeletonH(TFileRW *AFileRW);
//		bool InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);
		//bool InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);
		void GenerateAll(const char *APath,const char *ClassName);
//		bool SkeletonCPP(TFileRW *AFileRW);
//		bool SkeletonH(TFileRW *AFileRW);
//		bool SkeletonMakeFile(TFileRW *AFileRW);
//-------- Dynamic Code --------------
		bool CreateBody(bool ReallyWriteInFile = true);
		bool CreateHeader(bool ReallyWriteInFile = true);
		bool CreateMakeFile(bool ReallyWriteInFile = true);
		bool CreateConstructor(bool ReallyWriteInFile = true);
		bool CreateMessageReceived(bool ReallyWriteInFile = true);
		bool PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile = true);
//------------------------------------
	private :
		TViewComponent *FViewComponent;
};

#endif