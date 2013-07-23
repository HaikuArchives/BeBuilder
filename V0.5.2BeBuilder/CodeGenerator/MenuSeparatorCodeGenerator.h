#ifndef __MENU_SEPARATOR_CODE_GENERATOR_H__
#define __MENU_SEPARATOR_CODE_GENERATOR_H__
#include "CodeGenerator.h"
#include <Entry.h>
#include <MenuField.h>
class TMenuSeparatorComponent;
class TMenuSeparatorCodeGenerator : public TCodeGenerator
{
	public :
		TMenuSeparatorCodeGenerator(TMenuSeparatorComponent * AMenuSeparatorComponent,bool CanCreateSourceFile);
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
		TMenuSeparatorComponent *FMenuSeparatorComponent;
		
};

#endif