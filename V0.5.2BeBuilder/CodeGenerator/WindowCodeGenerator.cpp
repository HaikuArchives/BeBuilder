#include "WindowCodeGenerator.h"
#include "WindowComponent.h"
TWindowCodeGenerator::TWindowCodeGenerator(TWindowComponent * AWindowComponent, bool CanCreateSourceFile)
:TCodeGenerator(CanCreateSourceFile)
{
	FDebugMode = 1;
	FDebugMessage= "TWindowCodeGenerator ";

	FWindowComponent = AWindowComponent;
	FHeaderCodeFile = NULL;
	FBodyCodeFile = NULL;
	FMakeFileCodeFile = NULL;	
}

//void TWindowCodeGenerator::GenerateAll(char *APath,char *ClassName)
/*
void TWindowCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	//------------New dynamic code generation----------
	FHeaderCodeFile = new TCodeFile(APath,ClassName,"h");
	FBodyCodeFile = new TCodeFile(APath,ClassName,"cpp");
	FMakeFileCodeFile = new TCodeFile(APath,"makefile",NULL);
	CreateBody(true);
	CreateHeader(true);
	CreateMakeFile(true);
	CreateConstructeur(true);	
	
	//-------------------------------------------------


	TComponent *AComponent;
	printf("TWindowCodeGenerator ClassName : %s \n", ClassName);
	GenerateH(APath,ClassName);
	GenerateCPP(APath,ClassName);	
	GenerateMakeFile(APath,"makefile"); // To get a handle to the makefile file!		
	//---------NEW METHOD!
	SkeletonCPP(FCPPRW);
	SkeletonH(FHeaderRW);
	GenerateH(APath,ClassName); //To open normaly the file in reading....
	GenerateCPP(APath,ClassName);		
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);

	BEntry entry(FCPPRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	printf("TWindowCodeGenerator::GenerateAll Before Adding to MakeFile: %s \n",name);
	InsertionMakeFile(FMakeRW,name);		
	printf("TWindowCodeGenerator::GenerateAll After Adding To MakeFile\n");
	
	AComponent = FWindowComponent->FChildren->NextComponent(true);
	while(AComponent!=NULL)
	{
		AComponent->Generate(APath,FHeaderRW,FCPPRW);
		AComponent = FWindowComponent->FChildren->NextComponent(false);	
	}
	printf("TWindowCodeGenerator::GenerateAll Exit from While\n");

}
*/
//---------NEW FUNCTION----------
/*
bool TWindowCodeGenerator::SkeletonCPP(TFileRW *AFileRW)
{
	printf("Inside TWindowCodeGenerator::SkeletonCPP \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
// Constructeur!	
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	AFileRW->WriteALine("#include \"");
	AFileRW->WriteALine(name);
	AFileRW->WriteALine("\"\n");
//	AFileRW->WriteALine(FWindowComponent->FClassName + "::" + FWindowComponent->FClassName + "(char *AWindowTitle, BRect AFrame): BWindow(AFrame,AWindowTitle,B_TITLED_WINDOW,0)\n");
	AFileRW->WriteALine(FWindowComponent->FClassName + "::" + FWindowComponent->FClassName + "(char *");
//	AFileRW->WriteALine("\"");
//	AFileRW->WriteALine(FWindowComponent->FPropertyList->GetPropertyValue(PROP_TITLE).c_str());
//	AFileRW->WriteALine("\", BRect AFrame): BWindow(AFrame,AWindowTitle,");
	AFileRW->WriteALine("AWindowTitle, BRect AFrame): BWindow(AFrame,AWindowTitle,");

//	AFileRW->WriteALine(FWindowComponent->FPropertyList->GetPropertyValue(PROP_TITLE).c_str());
//	AFileRW->WriteALine(",");
	AFileRW->WriteALine(FWindowComponent->FPropertyList->GetPropertyValue(PROP_WINDOWTYPE).c_str());
	AFileRW->WriteALine(",");
	AFileRW->WriteALine(FWindowComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str());
	AFileRW->WriteALine(")\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
// Destructeur!	
	AFileRW->WriteALine(FWindowComponent->FClassName + "::~" + FWindowComponent->FClassName + "(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
// Quitting App!
	AFileRW->WriteALine("bool " + FWindowComponent->FClassName + "::QuitRequested(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tbe_app->PostMessage(B_QUIT_REQUESTED);\n");	
	AFileRW->WriteALine("\treturn (TRUE);\n");	
	AFileRW->WriteALine("}\n");

	return true;
}

bool TWindowCodeGenerator::SkeletonH(TFileRW *AFileRW)
{
	printf("Inside TWindowCodeGenerator::SkeletonH \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
	AFileRW->WriteALine("#ifndef __" + FWindowComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#define __" + FWindowComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#include <Window.h>\n");	
	AFileRW->WriteALine("#include <Application.h>\n");	
	AFileRW->WriteALine("class " + FWindowComponent->FClassName + ": public BWindow\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tpublic: \n");	
	AFileRW->WriteALine("\t\t" + FWindowComponent->FClassName + "(char *AWindowTitle, BRect AFrame);\n");
	AFileRW->WriteALine("\t\t~" + FWindowComponent->FClassName + "(void);\n");
	AFileRW->WriteALine("\t\tbool QuitRequested(void);\n");
	AFileRW->WriteALine("};\n");		
	AFileRW->WriteALine("#endif\n");	
	return true;
}

bool TWindowCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TWindowCodeGenerator::InsertionContructor \n");

	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	bool resultat;
//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <Window.h>\n";
//	printf("TWindowCodeGenerator::InsertionContructor before AddInfunction \n");
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
//	printf("TWindowCodeGenerator::InsertionContructor continue \n");
	
	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
	MustBeAdded = "\t\tBWindow *F" + FWindowComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
//	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
//	printf("TWindowCodeGenerator::InsertionContructor continue \n");


//In the CPP!
	InsideWhich = "#"; //found the #ifndef
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);		
	MustBeAdded = "#include \"" ;
	MustBeAdded = MustBeAdded + name;	
	MustBeAdded = MustBeAdded + "\"\n";
	resultat = AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),NULL,NULL,MustBeAdded.c_str());
//	printf("TWindowCodeGenerator::InsertionContructor after AddInfunction \n");
	if (!resultat)
	{
		return resultat;
	}
//	printf("TWindowCodeGenerator::InsertionContructor continue \n");

	InsideWhich = "TBeBuilderApp::"; //constructor is the first in the file!.... that was generated like that!
	AfterWhat = "{";
	BeforeWhat = "}";
	MustBeAdded = "\t" + FWindowComponent->FClassName + " * F" + FWindowComponent->FComponentName + ";\n";
	MustBeAdded = MustBeAdded + "\tBRect ARect" + FWindowComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FWindowComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FWindowComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FWindowComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FWindowComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	MustBeAdded = MustBeAdded + "\tF" + FWindowComponent->FComponentName + " = new " + FWindowComponent->FClassName;
	MustBeAdded = MustBeAdded + "(\"";
	MustBeAdded = MustBeAdded +	FWindowComponent->FPropertyList->GetPropertyValue(PROP_TITLE).c_str();
	MustBeAdded = MustBeAdded + "\",ARect"+ FWindowComponent->FComponentName +");\n";
	MustBeAdded = MustBeAdded + "\tF" + FWindowComponent->FComponentName + "->Show();\n";
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());

}
*/
//-------- Dynamic Code --------------

bool TWindowCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	FBodyLine = new TCodeLine(FBodyCodeFile);

	TProperty *AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FBodyCodeFile);

	FBodyLine->Copyrights();	
	FBodyLine->AddString("#include \""); 
	FBodyLine->AddProperty(FWindowComponent,PROP_NAME,true,true);
	FBodyLine->AddString(".h\"\n");

/*
	FBodyLine->Copyrights();	
	FBodyLine->AddString("#include \""); 
	TProperty *AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FBodyCodeFile);
	AProperty->AddCodeLine(FBodyLine);
	FBodyLine->AddProperty(AProperty); 
	FBodyLine->AddString(".h\"\n");
*/
	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
	FBodyLine2->AddString("::");
	FBodyLine2->AddProperty(FWindowComponent,PROP_CLASSNAME,false,false);
	FBodyLine2->AddString("(char *AWindowTitle, BRect AFrame): BWindow(AFrame,AWindowTitle,");
	FBodyLine2->AddProperty(FWindowComponent,PROP_WINDOWTYPE,true,false);
	FBodyLine2->AddString(",");
	FBodyLine2->AddProperty(FWindowComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(")\n");

/*	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_CLASSNAME);
	AProperty->AddCodeLine(FBodyLine2);	
	FBodyLine2->AddProperty(AProperty); 
	FBodyLine2->AddString("::");
	FBodyLine2->AddProperty(AProperty); 
	FBodyLine2->AddString("(char *AWindowTitle, BRect AFrame): BWindow(AFrame,AWindowTitle,");
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_WINDOWTYPE);
	AProperty->AddCodeLine(FBodyLine2);
	FBodyLine2->AddProperty(AProperty); 
	FBodyLine2->AddString(",");
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_FLAGS);
	AProperty->AddCodeLine(FBodyLine2);
	FBodyLine2->AddProperty(AProperty); 
	FBodyLine2->AddProperty(AProperty);
	FBodyLine2->AddString(")\n");
*/	
	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddString("{\n}\n");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
	FBodyLine4->AddString("::~");
	FBodyLine4->AddProperty(FWindowComponent,PROP_CLASSNAME,false,false);
	FBodyLine4->AddString("(void)\n");

/*	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_CLASSNAME);
	AProperty->AddCodeLine(FBodyLine4);
	FBodyLine4->AddProperty(AProperty); 
	FBodyLine4->AddString("::~");
	FBodyLine4->AddProperty(AProperty); 
	FBodyLine4->AddString("(void)\n");
*/	
	TCodeLine *FBodyLine5 = new TCodeLine(FBodyCodeFile);
	FBodyLine5->AddString("{\n}\n");
	
	TCodeLine *FBodyLine6 = new TCodeLine(FBodyCodeFile);
	FBodyLine6->AddString("bool ");
	FBodyLine6->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
//	FBodyLine6->AddProperty(AProperty); 
//	AProperty->AddCodeLine(FBodyLine6);
	FBodyLine6->AddString("::QuitRequested(void)\n");
	
	TCodeLine *FBodyLine7 = new TCodeLine(FBodyCodeFile);
	FBodyLine7->AddString("{\n\tbe_app->PostMessage(B_QUIT_REQUESTED);\n");
	FBodyLine7->AddString("\treturn (TRUE);\n}\n");

	if (ReallyWriteInFile)
	{
		FBodyLine7->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine6->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine5->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine4->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine3->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine2->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine->AddLine(NULL,NULL,NULL,NULL);
	}
	return true;
}

bool TWindowCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	FHeaderLine = new TCodeLine(FHeaderCodeFile);
	FHeaderLine->Copyrights();	

	TProperty *AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FHeaderCodeFile);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#ifndef __");
	FHeaderLine2->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
	FHeaderLine2->AddString("_H__ \n");

/*	TProperty *AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_CLASSNAME);
	AProperty->AddCodeFile(FHeaderCodeFile);
	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	AProperty->AddCodeLine(FHeaderLine2);
	FHeaderLine2->AddString("#ifndef __");
	FHeaderLine2->AddProperty(AProperty); 
	FHeaderLine2->AddString("_H__ \n");
*/
	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("#define __");
	FHeaderLine3->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
	FHeaderLine3->AddString("_H__ \n");

/*
	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	AProperty->AddCodeLine(FHeaderLine3);
	FHeaderLine3->AddString("#define __");
	FHeaderLine3->AddProperty(AProperty); 
	FHeaderLine3->AddString("_H__ \n");
*/
	TCodeLine *FHeaderLine4 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine4->AddString("#include <Window.h>\n#include <Application.h>\n");

	TCodeLine *FHeaderLine5 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine5->AddString("class ");	
	FHeaderLine5->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
//	FHeaderLine5->AddProperty(AProperty); 
	FHeaderLine5->AddString(": public BWindow");
//	AProperty->AddCodeLine(FHeaderLine5);
	
	TCodeLine *FHeaderLine6 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine6->AddString("\n{\n\tpublic: \n");
	
	TCodeLine *FHeaderLine7 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine7->AddString("\t\t");
	FHeaderLine7->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
//	FHeaderLine7->AddProperty(AProperty); 
	FHeaderLine7->AddString("(char *AWindowTitle, BRect AFrame);\n");
//	AProperty->AddCodeLine(FHeaderLine7);

	TCodeLine *FHeaderLine8 = new TCodeLine(FHeaderCodeFile);
//	AProperty->AddCodeLine(FHeaderLine8);
	FHeaderLine8->AddString("\t\t~");
	FHeaderLine8->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
//	FHeaderLine8->AddProperty(AProperty); 
	FHeaderLine8->AddString("(void);\n");

	TCodeLine *FHeaderLine9 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine9->AddString("\t\tbool QuitRequested(void);\n};\n#endif\n");

	if (ReallyWriteInFile)
	{
		FHeaderLine9->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine8->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine7->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine6->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine5->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine4->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine3->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine2->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine->AddLine(NULL,NULL,NULL,NULL);
	}
	return true;
}

bool TWindowCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	ShowDebug("CreateMakeFile Inside.");
	FMakeFileLine = new TCodeLine(FMakeFileCodeFile);
	FMakeFileLine->AddString(""); 
	FMakeFileLine->AddProperty(FWindowComponent,PROP_NAME,true,true);

//	TProperty *AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
//	FMakeFileLine->AddProperty(AProperty); 
//	FMakeFileLine->AddString(".cpp \\"); 
	FMakeFileLine->AddString(".cpp "); 
//	AProperty->AddCodeLine(FMakeFileLine);	
	if (ReallyWriteInFile)
	{
//		FMakeFileLine->AddLine(NULL,"SRCS=","\\",NULL);
		FMakeFileLine->AddLine(NULL,"SRCS=",NULL,"\n#");
	}
	ShowDebug("CreateMakeFile Quitting.");	
	return true;
}

bool TWindowCodeGenerator::CreateConstructeur(bool ReallyWriteInFile = true)
{
//bool AddProperty(TComponent *AComponent, const char *APropertyName,bool AddToProperty, bool AddToCodeGeneratorList);
ShowDebug("CreateConstructeur Inside.");
	//Header
/*	if (FWindowComponent==NULL) ShowDebug("CreateConstructeur FWindowComponent is NULL.");
	else ShowDebug("CreateConstructeur FWindowComponent is NOT NULL.");
	if (FWindowComponent->FParent==NULL) ShowDebug("CreateConstructeur FWindowComponent->FParent is NULL.");
	else ShowDebug("CreateConstructeur FWindowComponent->FParent is NOT NULL.");

	if (FWindowComponent->FParent->FCodeGenerator==NULL)
	{
		ShowDebug("CreateConstructeur FCodeGenerator is NULL.");	
	}
	else
	{
		ShowDebug("CreateConstructeur FCodeGenerator is NOT NULL.");		
	}

	if (FWindowComponent->FParent->FCodeGenerator->FHeaderCodeFile==NULL)
	{
		ShowDebug("CreateConstructeur FHeaderCodeFile is NULL.");	
	}
	else
	{
		ShowDebug("CreateConstructeur FCodeGenerator is NOT NULL.");		
	}
*/
	
	FHeaderConstructeurLine1 = new TCodeLine(FWindowComponent->FParent->FCodeGenerator->FHeaderCodeFile);
ShowDebug("CreateConstructeur Inside2!");
	FHeaderConstructeurLine1->AddString("#include <Window.h>\n"); 
	if (ReallyWriteInFile) FHeaderConstructeurLine1->AddLine(NULL,"#ifndef","#define",NULL);

/*
	FHeaderConstructeurLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderConstructeurLine2->AddString("\t\tBWindow *F"); 
	TProperty *AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeLine(FHeaderConstructeurLine2);
	FHeaderConstructeurLine2->AddProperty(AProperty); 
	FHeaderConstructeurLine2->AddString(";\n"); 

*/

	FHeaderConstructeurLine2 = new TCodeLine(FWindowComponent->FParent->FCodeGenerator->FHeaderCodeFile);
	FHeaderConstructeurLine2->AddString("\t\tBWindow *F"); 
	FHeaderConstructeurLine2->AddProperty(FWindowComponent,PROP_NAME,true,true);
	FHeaderConstructeurLine2->AddString(";\n"); 
	if (ReallyWriteInFile) FHeaderConstructeurLine2->AddLine(NULL,"class","public:",NULL);

	//Body

	TCodeLine *FBodyConstructeurLine3 = new TCodeLine(FWindowComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyConstructeurLine3->AddString("#include \""); 
	FBodyConstructeurLine3->AddProperty(FWindowComponent,PROP_NAME,true,true);
	FBodyConstructeurLine3->AddString(".h\"\n"); 

/*	TCodeLine *FBodyConstructeurLine3 = new TCodeLine(FBodyCodeFile);
	FBodyConstructeurLine3->AddString("#include \""); 
	FBodyConstructeurLine3->AddProperty(AProperty); 
	FBodyConstructeurLine3->AddString(".h\"\n"); 
	AProperty->AddCodeLine(FBodyConstructeurLine3);
*/
	if (ReallyWriteInFile)	FBodyConstructeurLine3->AddLine(NULL,"#",NULL,NULL);


//bool AddProperty(TComponent *AComponent, const char *APropertyName,bool AddToProperty, bool AddToCodeGeneratorList);
/*
	TCodeLine *FBodyConstructeurLine4 = new TCodeLine(FWindowComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyConstructeurLine4->AddString("\t"); 
	FBodyConstructeurLine4->AddProperty(FWindowComponent,PROP_CLASSNAME,true,true);
	FBodyConstructeurLine4->AddString(" *F"); 
	FBodyConstructeurLine4->AddProperty(FWindowComponent,PROP_NAME,true,false);
	FBodyConstructeurLine4->AddString(";\n"); 


	if (ReallyWriteInFile) FBodyConstructeurLine4->AddLine(NULL,"TBeBuilderApp::","{","}");
*/
//bool AddProperty(TComponent *AComponent, const char *APropertyName,bool AddToProperty, bool AddToCodeGeneratorList);

	TCodeLine *FBodyConstructeurLine5 = new TCodeLine(FWindowComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyConstructeurLine5->AddString("\tBRect ARect"); 
	FBodyConstructeurLine5->AddProperty(FWindowComponent,PROP_NAME,true,true);
	FBodyConstructeurLine5->AddString("("); 
	FBodyConstructeurLine5->AddProperty(FWindowComponent,PROP_LEFT,true,false);
	FBodyConstructeurLine5->AddString(","); 
	FBodyConstructeurLine5->AddProperty(FWindowComponent,PROP_TOP,true,false);
	FBodyConstructeurLine5->AddString(","); 
	FBodyConstructeurLine5->AddProperty(FWindowComponent,PROP_RIGHT,true,false);
	FBodyConstructeurLine5->AddString(","); 
	FBodyConstructeurLine5->AddProperty(FWindowComponent,PROP_BOTTOM,true,false);
	FBodyConstructeurLine5->AddString(");\n"); 

/*	
	TCodeLine *FBodyConstructeurLine5 = new TCodeLine(FBodyCodeFile);
	FBodyConstructeurLine5->AddString("\tBRect ARect"); 
	FBodyConstructeurLine5->AddProperty(AProperty); 
	AProperty->AddCodeLine(FBodyConstructeurLine5);
	FBodyConstructeurLine5->AddString("("); 
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_LEFT);
	AProperty->AddCodeLine(FBodyConstructeurLine5);
	FBodyConstructeurLine5->AddProperty(AProperty); 
	FBodyConstructeurLine5->AddString(","); 
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_TOP);
	AProperty->AddCodeLine(FBodyConstructeurLine5);
	FBodyConstructeurLine5->AddProperty(AProperty); 
	FBodyConstructeurLine5->AddString(","); 
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_RIGHT);
	AProperty->AddCodeLine(FBodyConstructeurLine5);
	FBodyConstructeurLine5->AddProperty(AProperty); 
	FBodyConstructeurLine5->AddString(","); 
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_BOTTOM);
	AProperty->AddCodeLine(FBodyConstructeurLine5);
	FBodyConstructeurLine5->AddProperty(AProperty); 
	FBodyConstructeurLine5->AddString(");\n"); 
*/
	if (ReallyWriteInFile) FBodyConstructeurLine5->AddLine(NULL,"TBeBuilderApp::","{","}");
	

	TCodeLine *FBodyConstructeurLine6 = new TCodeLine(FWindowComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyConstructeurLine6->AddString("\tF"); 
	FBodyConstructeurLine6->AddProperty(FWindowComponent,PROP_NAME,true,true);
//bool AddProperty(TComponent *AComponent, const char *APropertyName,bool AddToProperty, bool AddToCodeGeneratorList);
	FBodyConstructeurLine6->AddString(" = new "); 
	FBodyConstructeurLine6->AddProperty(FWindowComponent,PROP_CLASSNAME,true,false);
	FBodyConstructeurLine6->AddString("(\""); 
	FBodyConstructeurLine6->AddProperty(FWindowComponent,PROP_TITLE,true,false);
	FBodyConstructeurLine6->AddString("\",ARect"); 
	FBodyConstructeurLine6->AddProperty(FWindowComponent,PROP_NAME,false,false);
	FBodyConstructeurLine6->AddString(");\n");
	if (ReallyWriteInFile) FBodyConstructeurLine6->AddLine(NULL,"TBeBuilderApp::","{","}");

/*
	TCodeLine *FBodyConstructeurLine6 = new TCodeLine(FBodyCodeFile);
	FBodyConstructeurLine6->AddString("\tF"); 
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeLine(FBodyConstructeurLine6);
	FBodyConstructeurLine6->AddProperty(AProperty); 
	FBodyConstructeurLine6->AddString(" = new "); 

	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_CLASSNAME);
	AProperty->AddCodeLine(FBodyConstructeurLine6);
	FBodyConstructeurLine6->AddProperty(AProperty); 
	FBodyConstructeurLine6->AddString("(\""); 
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_TITLE);
	AProperty->AddCodeLine(FBodyConstructeurLine6);
	FBodyConstructeurLine6->AddProperty(AProperty); 
	FBodyConstructeurLine6->AddString("\",ARect"); 

	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeLine(FBodyConstructeurLine6);
	FBodyConstructeurLine6->AddProperty(AProperty); 
	FBodyConstructeurLine6->AddString(");\n");
	if (ReallyWriteInFile) FBodyConstructeurLine6->AddLine(NULL,"TBeBuilderApp::","{","}");

*/	

	TCodeLine *FBodyConstructeurLine7 = new TCodeLine(FWindowComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyConstructeurLine7->AddString("\tF"); 
	FBodyConstructeurLine7->AddProperty(FWindowComponent,PROP_NAME,true,true);
	FBodyConstructeurLine7->AddString("->Show();\n"); 	
/*
	FBodyConstructeurLine7->AddString("\tF"); 
	AProperty = FWindowComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeLine(FBodyConstructeurLine7);
	FBodyConstructeurLine7->AddProperty(AProperty); 
	FBodyConstructeurLine7->AddString("->Show();\n"); 	
*/
	if (ReallyWriteInFile) FBodyConstructeurLine7->AddLine(NULL,"TBeBuilderApp::","{","}");

	return true;	
}

void TWindowCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	ShowDebug(string("GenerateAll Inside. APath=") + string(APath) + string(" ClassName=") + string(ClassName));
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug("GenerateAll Before PrepareCode.");
	PrepareCode(APath,ClassName,true);
}

bool TWindowCodeGenerator::PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile = true)
{
	//------------New dynamic code generation----------

	FHeaderCodeFile = new TCodeFile(AClassName,APath,"h");
	FBodyCodeFile = new TCodeFile(AClassName,APath,"cpp");
	FMakeFileCodeFile = new TCodeFile("makefile",APath,NULL);

	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructeur(ReallyWriteInFile);	
	return true;
}