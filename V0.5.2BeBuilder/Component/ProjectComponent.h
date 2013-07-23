#ifndef __PROJECT_COMPONENT_H__
#define __PROJECT_COMPONENT_H__

#include <stdio.h>
#include "Component.h" 
#include "Global.h"
#include "GlobalVar.h"
#include "ProjectCodeGenerator.h"
#include <string>
#include <Handler.h>
//#include <Looper.h>
#include "FileRW.h"
#include "JerFiles.h"

class TProjectComponent : public TComponent, public BHandler
//class TProjectComponent : public TComponent, public BLooper
{
	public :
		TProjectComponent(char *AComponentName, char *AClassName);
		~TProjectComponent();
		void GetNextComponentIndex(string *AComponentName, string *AClassName);
//		void Generate(char *APathName, TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP);
		bool Generate(char *APathName);
		bool RemoveChild(TComponent *AComponent);		
		void MessageReceived(BMessage *message);
		const char *GetGenerationPath(void);
		void SetGenerationPath(const char* AGenerationPath);
		const char *GetExe(void);
	protected :
		int FIndex;
		string FGenerationPath;
		bool ChangeProperty(string APropertyName, string APropertyValue);
		
//		void CreateCompletePath()
//		void Generate(char *APathName);
	
};

#endif