#include "ProjectCodeGenerator.h"
#include "ProjectComponent.h"

TProjectCodeGenerator::TProjectCodeGenerator(TProjectComponent * AProjectComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FDebugMode = 1;
	FDebugMessage = "TProjectCodeGenerator ";
	FProjectComponent = AProjectComponent;
}

void TProjectCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	ShowDebug("GenerateAll Inside.");
	//------------New dynamic code generation----------
	FHeaderCodeFile = new TCodeFile(ClassName,APath,"h");
	FBodyCodeFile = new TCodeFile(ClassName,APath,"cpp");
	FMakeFileCodeFile = new TCodeFile("makefile",APath,NULL);
	ShowDebug(string("BodyFileName=") + string(FBodyCodeFile->GetFileName()));
//const char *TCodeFile::GetFileName(void)
//const char *TCodeFile::GetFilePath(void)


	ShowDebug("GenerateAll Before CreateBody.");

	CreateBody();
	CreateHeader();
	CreateMakeFile();
	
	//-------------------------------------------------
	
/*
	GenerateH(APath,ClassName);
	GenerateCPP(APath,ClassName);
	GenerateMakeFile(APath,"makefile");		
	SkeletonMakeFile(FMakeRW);
	SkeletonH(FHeaderRW);
	SkeletonCPP(FCPPRW);
	printf("TProjectCodeGenerator 2eme GenerateH Generate CPP \n");	
	GenerateH(APath,ClassName); //To open normaly the file in reading....
	GenerateCPP(APath,ClassName);		

	printf("TProjectCodeGenerator Before Appel a NextComponent \n");	
	TComponent *AComponent = FProjectComponent->FChildren->NextComponent(true);
	while(AComponent!=NULL)
	{
		printf("TProjectCodeGenerator Appel au composant : %s \n", ClassName);
		AComponent->Generate(APath,FHeaderRW,FCPPRW);
		AComponent = FProjectComponent->FChildren->NextComponent(false);	
	}
*/
	ShowDebug("GenerateAll Quitting");
}

bool TProjectCodeGenerator::SkeletonCPP(TFileRW *AFileRW)
{
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
	printf("TProjectCodeGenerator::SkeletonCPP Apres copyrights\n");
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	printf("TProjectCodeGenerator::SkeletonCPP Avant WriteLine\n");   	
	AFileRW->WriteALine("#include \"");
	AFileRW->WriteALine(name);
	AFileRW->WriteALine("\"\n");
	AFileRW->WriteALine("TBeBuilderApp::TBeBuilderApp() : BApplication(" );
	AFileRW->WriteALine("\"");
	AFileRW->WriteALine(FProjectComponent->FPropertyList->GetPropertyValue(PROP_APP_SIGNATURE).c_str());
	AFileRW->WriteALine("\"");
	AFileRW->WriteALine(")\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
	AFileRW->WriteALine("int main(int argc, char*argv[])\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tTBeBuilderApp MyApp;\n");
	AFileRW->WriteALine("\tMyApp.Run();\n");
	AFileRW->WriteALine("\treturn 0;\n");
	AFileRW->WriteALine("}\n");
	return true;
}
bool TProjectCodeGenerator::SkeletonH(TFileRW *AFileRW)
{
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
	AFileRW->WriteALine("#ifndef __" + FProjectComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#define __" + FProjectComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#include <stdio.h>\n");
	AFileRW->WriteALine("#include <Application.h>\n");
//	AFileRW->WriteALine("#include <Window.h>\n");
	AFileRW->WriteALine("\n");
	AFileRW->WriteALine("class TBeBuilderApp : public BApplication \n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tpublic:\n");
	AFileRW->WriteALine("\t\tTBeBuilderApp();\n");
	AFileRW->WriteALine("};\n");
	AFileRW->WriteALine("#endif\n");	
	return true;
}

bool TProjectCodeGenerator::SkeletonMakeFile(TFileRW *AFileRW)
{
	//-------- Cette fonction ne sera lancee que par le project MakeFile
	BEntry entry(FCPPRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
  	
	printf("Inside TCodeGenerator::SkeletonMakeFile\n");
	if (AFileRW==NULL) return false;
	if (AFileRW!=NULL)
	{
		printf("TCodeGenerator::SkeletonMakeFile Should Write Soon!\n");
		CopyrightsForMakeFile(AFileRW);
		AFileRW->WriteALine("## BeOS Generic Makefile v2.0 ##\n");
		AFileRW->WriteALine("NAME= BeBuilderApp\n");
		AFileRW->WriteALine("TYPE= APP\n");
		AFileRW->WriteALine("SRCS= ");
		AFileRW->WriteALine(name); //Next Line will be the source files!
//		AFileRW->WriteALine(" \\\n# Add your resource files here!\n");
		AFileRW->WriteALine(" \n# Add your resource files here!\n");
		AFileRW->WriteALine("RSRCS= \n");
		AFileRW->WriteALine("\n# Add Your libs here\n");
		AFileRW->WriteALine("#	specify additional libraries to link against\n");
		AFileRW->WriteALine("#	there are two acceptable forms of library specifications\n");
		AFileRW->WriteALine("#	-	if your library follows the naming pattern of:\n");
		AFileRW->WriteALine("#		libXXX.so or libXXX.a you can simply specify XXX\n");
		AFileRW->WriteALine("#		library: libbe.so entry: be\n");
		AFileRW->WriteALine("#	- 	if your library does not follow the standard library\n");
		AFileRW->WriteALine("#		naming scheme you need to specify the path to the library\n");
		AFileRW->WriteALine("#		and it's name\n");
		AFileRW->WriteALine("#		library: my_lib.a entry: my_lib.a or path/my_lib.a\n");
		AFileRW->WriteALine("LIBS=\tbe translation stdc++.r4 tracker root\n");
//		AFileRW->WriteALine("\t\ttranslation \\ \n");
//		AFileRW->WriteALine("\t\tstdc++.r4 \\\n");
//		AFileRW->WriteALine("\t\ttracker \\\n");
//		AFileRW->WriteALine("\t\troot\n");
		AFileRW->WriteALine("LIBPATHS=\n");
		AFileRW->WriteALine("SYSTEM_INCLUDE_PATHS = \n");
		AFileRW->WriteALine("LOCAL_INCLUDE_PATHS = \n");
		AFileRW->WriteALine("\n#	NONE, SOME, FULL\n");
		AFileRW->WriteALine("OPTIMIZE= NONE\n");
		AFileRW->WriteALine("SYMBOLS = \n");
		AFileRW->WriteALine("DEBUGGER = TRUE\n");
		AFileRW->WriteALine("\n# this flag allows you to use the wonderful bdb for x86! \n");	
		AFileRW->WriteALine("COMPILER_FLAGS = -gdwarf-2\n");
		AFileRW->WriteALine("LINKER_FLAGS = -gdwarf-2\n");
		AFileRW->WriteALine("\n## include the Be makefile-engine\n");
		AFileRW->WriteALine("DEVEL_DIRECTORY := \\\n$(shell findpaths -r \"makefile_engine\" B_FIND_PATH_DEVELOP_DIRECTORY\n");
		AFileRW->WriteALine("include $(DEVEL_DIRECTORY)/etc/makefile-engine\n");
	//	AFileRW->WriteALine("\n");
		printf("TCodeGenerator::SkeletonMakeFile End Of Writing!\n");
	}
	return true;
}
// Dynamic Code

bool TProjectCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	DEBUGPRINT("TProjectCodeGenerator::CreateBody enterring...\n");

	FBodyLine = new TCodeLine(FBodyCodeFile);
	DEBUGPRINT("TProjectCodeGenerator::CreateBody Before Copyrights...\n");

	FBodyLine->Copyrights();	
	DEBUGPRINT("TProjectCodeGenerator::CreateBody After Copyrights...\n");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine->AddString("#include \""); 
	TProperty *AProperty = FProjectComponent->FPropertyList->GetProperty(PROP_NAME);
//	DEBUGPRINT("Inside CreateBody APropertyValue="<<AProperty->GetValue().c_str());
//	AProperty->AddCodeLine(FBodyLine2);	
	AProperty->AddCodeFile(FBodyCodeFile);
	FBodyLine2->AddProperty(FProjectComponent,PROP_NAME,true,true);
//	FBodyLine2->AddProperty(AProperty); 
	FBodyLine2->AddString(".h\"\n");
	
	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	
	FBodyLine3->AddString("TBeBuilderApp::TBeBuilderApp() : BApplication(\"");
//	AProperty = FProjectComponent->FPropertyList->GetProperty(PROP_APP_SIGNATURE);
//	AProperty->AddCodeLine(FBodyLine3);	
//	FBodyLine3->AddProperty(AProperty); 
	FBodyLine3->AddProperty(FProjectComponent,PROP_APP_SIGNATURE,true,true);
	FBodyLine3->AddString("\")\n");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("{\n}\n");
	FBodyLine4->AddString("int main(int argc, char*argv[])\n");
	FBodyLine4->AddString("{\n\tTBeBuilderApp MyApp;\n");
	FBodyLine4->AddString("\tMyApp.Run();\n\treturn 0;\n}\n");

	DEBUGPRINT("TProjectCodeGenerator::CreateBody before AddLine...\n");
	if (ReallyWriteInFile)
	{
		FBodyLine4->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine3->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine2->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine->AddLine(NULL,NULL,NULL,NULL);
	}	
	DEBUGPRINT("TProjectCodeGenerator::CreateBody quitting\n");
	return true;

}

bool TProjectCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
	DEBUGPRINT("TProjectCodeGenerator::CreateHeader enterring...\n");
	FHeaderLine = new TCodeLine(FHeaderCodeFile);
	FHeaderLine->Copyrights();	
	
	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	
	FHeaderLine2->AddString("#ifndef __"); 
	TProperty *AProperty = FProjectComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FHeaderCodeFile);

//	AProperty = FProjectComponent->FPropertyList->GetProperty(PROP_CLASSNAME);
//	DEBUGPRINT("Inside CreateHeader APropertyValue="<<AProperty->GetValue().c_str());
//	AProperty->AddCodeLine(FHeaderLine2);
	FHeaderLine2->AddProperty(FProjectComponent,PROP_CLASSNAME,true,true);

//	FHeaderLine2->AddProperty(AProperty); 
	FHeaderLine2->AddString("_H__ \n");

	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("#define __");
//	FHeaderLine3->AddProperty(AProperty); 
	FHeaderLine3->AddProperty(FProjectComponent,PROP_CLASSNAME,true,true);
	FHeaderLine3->AddString("_H__ \n");
//	AProperty->AddCodeLine(FHeaderLine3);
	
	
	TCodeLine *FHeaderLine4 = new TCodeLine(FHeaderCodeFile);
	
	FHeaderLine4->AddString("#include <stdio.h>\n");
	FHeaderLine4->AddString("#include <Application.h>\n\n");
	FHeaderLine4->AddString("class TBeBuilderApp : public BApplication \n");
	FHeaderLine4->AddString("{\n\tpublic:\n\t\tTBeBuilderApp();\n};\n#endif\n");
	if (ReallyWriteInFile)
	{
		FHeaderLine4->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine3->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine2->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine->AddLine(NULL,NULL,NULL,NULL);
	}
//	DEBUGPRINT("TProjectCodeGenerator::CreateHeader quitting\n");
	return true;
}

bool TProjectCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	DEBUGPRINT("TProjectCodeGenerator::CreateMakeFile enter.")
	FMakeFileLine = new TCodeLine(FMakeFileCodeFile);
	FMakeFileLine->CopyrightsMakeFile();	
	FMakeFileLine->AddString("## BeOS Generic Makefile v2.0 ##\n");
	FMakeFileLine->AddString("NAME= BeBuilderApp\n");
	FMakeFileLine->AddString("TYPE= APP\n");
	FMakeFileLine->AddString("SRCS= ");

//	TProperty *AProperty = FProjectComponent->FPropertyList->GetProperty(PROP_NAME);
//	DEBUGPRINT("Inside CreateHeader APropertyValue="<<AProperty->GetValue().c_str());
//	AProperty->AddCodeLine(FMakeFileLine);

	TCodeLine *FMakeFileLine2 = new TCodeLine(FMakeFileCodeFile);

	FMakeFileLine2->AddProperty(FProjectComponent,PROP_NAME,true,true);

//	FMakeFileLine2->AddProperty(AProperty); 
//	FMakeFileLine2->AddString(".cpp \\\n");
//	FMakeFileLine2->AddString(".cpp \n");
	FMakeFileLine2->AddString(".cpp ");

	TCodeLine *FMakeFileLine3 = new TCodeLine(FMakeFileCodeFile);

	FMakeFileLine3->AddString("\n# Add your resource files here! \n");
	FMakeFileLine3->AddString("RSRCS= \n");
	FMakeFileLine3->AddString("# Add Your libs here\n");
	FMakeFileLine3->AddString("#	specify additional libraries to link against\n");
	FMakeFileLine3->AddString("#	there are two acceptable forms of library specifications\n");
	FMakeFileLine3->AddString("#	-	if your library follows the naming pattern of:\n");
	FMakeFileLine3->AddString("#		libXXX.so or libXXX.a you can simply specify XXX\n");
	FMakeFileLine3->AddString("#		library: libbe.so entry: be\n");
	FMakeFileLine3->AddString("#	- 	if your library does not follow the standard library\n");
	FMakeFileLine3->AddString("#		naming scheme you need to specify the path to the library\n");
	FMakeFileLine3->AddString("#		and it's name\n");
	FMakeFileLine3->AddString("#		library: my_lib.a entry: my_lib.a or path/my_lib.a\n");
	FMakeFileLine3->AddString("LIBS=\tbe translation stdc++.r4 tracker root\n");
	FMakeFileLine3->AddString("LIBPATHS=\n");
	FMakeFileLine3->AddString("SYSTEM_INCLUDE_PATHS = \n");
	FMakeFileLine3->AddString("LOCAL_INCLUDE_PATHS = \n");
	FMakeFileLine3->AddString("\n#	NONE, SOME, FULL\n");
	FMakeFileLine3->AddString("OPTIMIZE= NONE\n");
	FMakeFileLine3->AddString("SYMBOLS = \n");
	FMakeFileLine3->AddString("DEBUGGER = TRUE\n");
	FMakeFileLine3->AddString("\n# this flag allows you to use the wonderful bdb for x86! \n");	
	FMakeFileLine3->AddString("COMPILER_FLAGS = -gdwarf-2\n");
	FMakeFileLine3->AddString("LINKER_FLAGS = -gdwarf-2\n");
	FMakeFileLine3->AddString("\n## include the Be makefile-engine\n");
	FMakeFileLine3->AddString("include /boot/develop/etc/makefile-engine\n");
	if (ReallyWriteInFile)
	{
		FMakeFileLine3->AddLine(NULL,NULL,NULL,NULL);
		FMakeFileLine->AddLine(NULL,NULL,NULL,NULL);
		
		FMakeFileLine2->AddLine(NULL,"SRCS=",NULL,"\n#");

	}
	DEBUGPRINT("TProjectCodeGenerator::CreateMakeFile quitting...")
	return true;

}

void TProjectCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	

	PrepareCode(APath,ClassName,true);
}

bool TProjectCodeGenerator::PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile)
{
	//------------New dynamic code generation----------
	FHeaderCodeFile = new TCodeFile(AClassName,APath,"h");
	FBodyCodeFile = new TCodeFile(AClassName,APath,"cpp");
	FMakeFileCodeFile = new TCodeFile("makefile",APath,NULL);

	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);	
	return true;
}

