#ifndef __SCROLL_VIEW_CODE_GENERATOR_H__
#define __SCROLL_VIEW_CODE_GENERATOR_H__
#include "CodeGenerator.h"
#include "ListViewCodeGenerator.h"
#include <Entry.h>
class TScrollViewComponent;
class TScrollViewCodeGenerator : public TCodeGenerator
{
	public :
		TScrollViewCodeGenerator(TScrollViewComponent * AScrollViewComponent,bool CanCreateSourceFile);
//		void GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP);
		void GenerateAll(const char *APath,const char *ClassName);
		bool CreateBody(bool ReallyWriteInFile = true);
		bool CreateHeader(bool ReallyWriteInFile = true);
		bool CreateMakeFile(bool ReallyWriteInFile = true);
		bool CreateConstructor(bool ReallyWriteInFile = true);
		bool CreateMessageReceived(bool ReallyWriteInFile = true);
		bool PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true);
	private :
		TScrollViewComponent *FScrollViewComponent;
		
};

#endif