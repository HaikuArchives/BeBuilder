#ifndef __OUTLINE_LISTVIEW_CODE_GENERATOR_H__
#define __OUTLINE_LISTVIEW_CODE_GENERATOR_H__
#include "CodeGenerator.h"
#include "ComponentList.h"
#include <Entry.h>
class TOutlineListViewComponent;
class TOutlineListViewCodeGenerator : public TCodeGenerator
{
	public :
		TOutlineListViewCodeGenerator(TOutlineListViewComponent * AOutlineListViewComponent,bool CanCreateSourceFile);
//		void GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP);
//		bool InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);

		void GenerateAll(const char *APath,const char *ClassName);
		bool CreateBody(bool ReallyWriteInFile = true);
		bool CreateHeader(bool ReallyWriteInFile = true);
		bool CreateMakeFile(bool ReallyWriteInFile = true);
		bool CreateConstructor(bool ReallyWriteInFile = true);
		bool CreateMessageReceived(bool ReallyWriteInFile = true);
		bool PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true);
		
	private :
		TOutlineListViewComponent *FOutlineListViewComponent;
		
};

#endif