#ifndef __SLIDER_CODE_GENERATOR_H__
#define __SLIDER_CODE_GENERATOR_H__
#include "CodeGenerator.h"
#include <Entry.h>
class TSliderComponent;
class TSliderCodeGenerator : public TCodeGenerator
{
	public :
		TSliderCodeGenerator(TSliderComponent * ASliderComponent,bool CanCreateSourceFile);
//		void GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP);
//		bool InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);
//		bool InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);
		void GenerateAll(const char *APath,const char *ClassName);
		bool CreateBody(bool ReallyWriteInFile = true);
		bool CreateHeader(bool ReallyWriteInFile = true);
		bool CreateMakeFile(bool ReallyWriteInFile = true);
		bool CreateConstructor(bool ReallyWriteInFile = true);
		bool CreateMessageReceived(bool ReallyWriteInFile = true);
		bool PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true);
	private :
		TSliderComponent *FSliderComponent;
		bool InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP);
		
		
};

#endif