#include "ViewCodeGenerator.h"
#include "ViewComponent.h"
TViewCodeGenerator::TViewCodeGenerator(TViewComponent * AViewComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FViewComponent = AViewComponent;
}
/*
void TViewCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TViewCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	GenerateH(APath,ClassName);
	GenerateCPP(APath,ClassName);	
	GenerateMakeFile(APath,"makefile"); // To get a handle to the makefile file!		
	//---------NEW METHOD!
	SkeletonCPP(FCPPRW);
	SkeletonH(FHeaderRW);
	GenerateH(APath,ClassName); //To open normaly the file in reading....
	GenerateCPP(APath,ClassName);	

	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("TViewCodeGenerator::GenerateAll Before InsertionMessageREceived \n");
	InsertionMessageReceived(AParentFileRWHeader,AParentFileRWCPP);
	printf("TViewCodeGenerator::GenerateAll After InsertionMessageREceived \n");

	BEntry entry(FCPPRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	printf("TViewCodeGenerator::GenerateAll Before InsertionMakeFile \n");
	InsertionMakeFile(FMakeRW,name);		
	printf("TViewCodeGenerator::GenerateAll After InsertionMakeFile \n");
	
// ------- COMPONENT LIST! --------------
	TComponent *AComponent = FViewComponent->FChildren->NextComponent(true);
	printf("TViewCodeGenerator::GenerateAll After NextComponent \n");
	while(AComponent!=NULL)
	{
		printf("TViewCodeGenerator::GenerateAll Before GEnerate \n");		
		AComponent->Generate(APath,FHeaderRW,FCPPRW);
		printf("TViewCodeGenerator::GenerateAll After GEnerate \n");		
		AComponent = FViewComponent->FChildren->NextComponent(false);	
	}
	printf("TViewCodeGenerator::GenerateAll Exit from While\n");
}
*/
/*
bool TViewCodeGenerator::SkeletonCPP(TFileRW *AFileRW)
{
	printf("Inside TViewCodeGenerator::SkeletonCPP \n");
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
	printf("TViewCodeGenerator::SkeletonCPP Apres copyrights\n");
	BEntry entry(FHeaderRW->GetFileName());
	char name[B_FILE_NAME_LENGTH]; 
   	entry.GetName(name);	
	printf("TViewCodeGenerator::SkeletonCPP Avant WriteLine\n");   	
	AFileRW->WriteALine("#include \"");
	AFileRW->WriteALine(name);
	AFileRW->WriteALine("\"\n");
//--------- Contructor
	AFileRW->WriteALine(FViewComponent->FClassName + "::" + FViewComponent->FClassName + "(BRect AFrame): BView(AFrame,NULL,");
	AFileRW->WriteALine(FViewComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str());
	AFileRW->WriteALine(",");
	AFileRW->WriteALine(FViewComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str());
	AFileRW->WriteALine(")\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
//--------- Destructor
	AFileRW->WriteALine(FViewComponent->FClassName + "::~" + FViewComponent->FClassName + "(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("}\n");
//--------- Message Received
	AFileRW->WriteALine("void " + FViewComponent->FClassName + "::MessageReceived(BMessage *message)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tswitch(message->what)\n");
	AFileRW->WriteALine("\t{\n");
	AFileRW->WriteALine("\t\tdefaut :\n");
	AFileRW->WriteALine("\t\t\t BView::MessageReceived(message);\n");
	AFileRW->WriteALine("\t\t\tbreak;\n");
	AFileRW->WriteALine("\t}\n");
	AFileRW->WriteALine("}\n");
//--------- Attached to Window
	AFileRW->WriteALine("void " + FViewComponent->FClassName + "::AttachedToWindow(void)\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tBView::AttachedToWindow();\n"); 
	AFileRW->WriteALine("}\n");
	printf("TViewCodeGenerator::SkeletonCPP fin\n");   	
	return true;
}

bool TViewCodeGenerator::SkeletonH(TFileRW *AFileRW)
{
	if (AFileRW==NULL) return false;
	Copyrights(AFileRW);
	AFileRW->WriteALine("#ifndef __" + FViewComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#define __" + FViewComponent->FClassName +"_H__ \n");	
	AFileRW->WriteALine("#include <View.h>\n");	
	AFileRW->WriteALine("class " + FViewComponent->FClassName + ": public BView\n");
	AFileRW->WriteALine("{\n");
	AFileRW->WriteALine("\tpublic:\n");
	AFileRW->WriteALine("\t\t" + FViewComponent->FClassName + "(BRect AFrame);\n");
	AFileRW->WriteALine("\t\t~" + FViewComponent->FClassName + "(void);\n");
	AFileRW->WriteALine("\t\tvoid MessageReceived(BMessage *message);\n");
	AFileRW->WriteALine("\t\tvoid AttachedToWindow(void);\n");
	AFileRW->WriteALine("};\n");		
	AFileRW->WriteALine("#endif\n");	
	return true;
}

bool TViewCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
//	printf("Inside TViewCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <View.h>\n";

//	printf("TViewCodeGenerator::InsertionContructor Before AddInFunction\n");
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
//	printf("TViewCodeGenerator::InsertionContructor After AddInFunction\n");
	if (!resultat) return false;
//	printf("TViewCodeGenerator::InsertionContructor continue!\n");

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBView *" + FViewComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;


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

	if (FViewComponent->FParent==NULL) InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
	else InsideWhich = "::" + FViewComponent->FParent->FClassName;
	AfterWhat = "{";
	BeforeWhat = "}";
	MustBeAdded = "\t" + FViewComponent->FComponentName + " = new " +FViewComponent->FClassName;
	MustBeAdded = MustBeAdded + "(Bounds());\n";
//	MustBeAdded = MustBeAdded + "\trgb_color kDarkGray = {100,100,100,255};\n\t";
	MustBeAdded = MustBeAdded + "\trgb_color kGray = {219,219,219,255};\n\t";
	MustBeAdded = MustBeAdded + FViewComponent->FComponentName;
//	MustBeAdded = MustBeAdded + "->SetViewColor(kDarkGray);\n";
	MustBeAdded = MustBeAdded + "->SetViewColor(kGray);\n";
	MustBeAdded = MustBeAdded + "\tAddChild(" + FViewComponent->FComponentName;
	MustBeAdded = MustBeAdded + ");\n";
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
}
*/
//New Functions

bool TViewCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	TCodeLine *FBodyLine = new TCodeLine(FBodyCodeFile);
	FBodyLine->Copyrights();

	TProperty *AProperty = FViewComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FBodyCodeFile);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("#include \"");
	FBodyLine2->AddProperty(FViewComponent,PROP_NAME,true,true);	
	FBodyLine2->AddString(".h\"\n");

	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
	FBodyLine3->AddString("::");
	FBodyLine3->AddProperty(FViewComponent,PROP_CLASSNAME,false,false);	
	FBodyLine3->AddString("(BRect AFrame): BView(AFrame,NULL,");
	FBodyLine3->AddProperty(FViewComponent,PROP_RESIZING_MODE,true,true);	
	FBodyLine3->AddString(",");
	FBodyLine3->AddProperty(FViewComponent,PROP_FLAGS,true,true);	
	FBodyLine3->AddString(")\n");

	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("{\n");

	TCodeLine *FBodyLine5 = new TCodeLine(FBodyCodeFile);
	FBodyLine5->AddString("}\n");

	TCodeLine *FBodyLine6 = new TCodeLine(FBodyCodeFile);
	FBodyLine6->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
	FBodyLine6->AddString("::~");
	FBodyLine6->AddProperty(FViewComponent,PROP_CLASSNAME,false,false);	
	FBodyLine6->AddString("(void)\n");

	TCodeLine *FBodyLine7 = new TCodeLine(FBodyCodeFile);
	FBodyLine7->AddString("{\n");

	TCodeLine *FBodyLine8 = new TCodeLine(FBodyCodeFile);
	FBodyLine8->AddString("}\n");

	TCodeLine *FBodyLine9 = new TCodeLine(FBodyCodeFile);
	FBodyLine9->AddString("void ");
	FBodyLine9->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
	FBodyLine9->AddString("::MessageReceived(BMessage *message)\n");

	TCodeLine *FBodyLine10 = new TCodeLine(FBodyCodeFile);
	FBodyLine10->AddString("{\n");

	TCodeLine *FBodyLine11 = new TCodeLine(FBodyCodeFile);
	FBodyLine11->AddString("\tswitch(message->what)\n");

	TCodeLine *FBodyLine12 = new TCodeLine(FBodyCodeFile);
	FBodyLine12->AddString("\t{\n");

	TCodeLine *FBodyLine13 = new TCodeLine(FBodyCodeFile);
	FBodyLine13->AddString("\t\tdefault :\n");

	TCodeLine *FBodyLine14 = new TCodeLine(FBodyCodeFile);
	FBodyLine14->AddString("\t\t\tBView::MessageReceived(message);\n");

	TCodeLine *FBodyLine15 = new TCodeLine(FBodyCodeFile);
	FBodyLine15->AddString("\t\t\tbreak;\n");

	TCodeLine *FBodyLine16 = new TCodeLine(FBodyCodeFile);
	FBodyLine16->AddString("\t}\n");

	TCodeLine *FBodyLine17 = new TCodeLine(FBodyCodeFile);
	FBodyLine17->AddString("}\n");

	TCodeLine *FBodyLine18 = new TCodeLine(FBodyCodeFile);
	FBodyLine18->AddString("void ");
	FBodyLine18->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
	FBodyLine18->AddString("::AttachedToWindow(void)\n");

	TCodeLine *FBodyLine19 = new TCodeLine(FBodyCodeFile);
	FBodyLine19->AddString("{\n");

	TCodeLine *FBodyLine20 = new TCodeLine(FBodyCodeFile);
	FBodyLine20->AddString("\tBView::AttachedToWindow();\n");

	TCodeLine *FBodyLine21 = new TCodeLine(FBodyCodeFile);
	FBodyLine21->AddString("}\n");

	if (ReallyWriteInFile)
	{
		FBodyLine21->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine20->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine19->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine18->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine17->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine16->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine15->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine14->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine13->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine12->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine11->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine10->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine9->AddLine(NULL,NULL,NULL,NULL);
		FBodyLine8->AddLine(NULL,NULL,NULL,NULL);
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
bool TViewCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
/*	FHeaderCodeFile = new TCodeFile(APath,ClassName,"h");
	FBodyCodeFile = new TCodeFile(APath,ClassName,"cpp");
	FMakeFileCodeFile = new TCodeFile(APath,"makefile",NULL);
*/
	TCodeLine *FHeaderLine = new TCodeLine(FHeaderCodeFile);
	FHeaderLine->Copyrights();

	TProperty *AProperty = FViewComponent->FPropertyList->GetProperty(PROP_NAME);
	AProperty->AddCodeFile(FHeaderCodeFile);
	
	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
//	AProperty->AddCodeLine(FHeaderLine2);
	FHeaderLine2->AddString("#ifndef __");
	FHeaderLine2->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
//	FHeaderLine2->AddProperty(AProperty); 
	FHeaderLine2->AddString("_H__ \n");

	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
//	AProperty->AddCodeLine(FHeaderLine3);
	FHeaderLine3->AddString("#define __");
	FHeaderLine3->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
//	FHeaderLine3->AddProperty(AProperty); 
	FHeaderLine3->AddString("_H__ \n");

	TCodeLine *FHeaderLine4 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine4->AddString("#include <View.h>\n");

	TCodeLine *FHeaderLine5 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine5->AddString("class ");
	FHeaderLine5->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
//	AProperty->AddCodeLine(FHeaderLine5);
//	FHeaderLine5->AddProperty(AProperty);
	FHeaderLine5->AddString(": public BView\n");
	
	TCodeLine *FHeaderLine6 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine6->AddString("{\n");
	
	TCodeLine *FHeaderLine7 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine7->AddString("\tpublic:\n");
	
	TCodeLine *FHeaderLine8 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine8->AddString("\t\t");
	FHeaderLine8->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
//	AProperty->AddCodeLine(FHeaderLine8);
//	FHeaderLine8->AddProperty(AProperty);
	FHeaderLine8->AddString("(BRect AFrame);\n");
	
	TCodeLine *FHeaderLine9 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine9->AddString("\t\t~");
	FHeaderLine9->AddProperty(FViewComponent,PROP_CLASSNAME,true,true);	
//	AProperty->AddCodeLine(FHeaderLine9);
//	FHeaderLine9->AddProperty(AProperty);
	FHeaderLine9->AddString("(void);\n");
	
	TCodeLine *FHeaderLine10 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine10->AddString("\t\tvoid MessageReceived(BMessage *message);\n");

	TCodeLine *FHeaderLine11 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine11->AddString("\t\tvoid AttachedToWindow(void);\n");

	TCodeLine *FHeaderLine12 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine12->AddString("};\n");
	
	TCodeLine *FHeaderLine13 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine13->AddString("#endif\n");
		
	if (ReallyWriteInFile)
	{
		FHeaderLine13->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine12->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine11->AddLine(NULL,NULL,NULL,NULL);
		FHeaderLine10->AddLine(NULL,NULL,NULL,NULL);
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

bool TViewCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	ShowDebug("CreateMakeFile Inside.");
	TCodeLine *FMakeFileLine = new TCodeLine(FMakeFileCodeFile);
	FMakeFileLine->AddString(""); 
	FMakeFileLine->AddProperty(FViewComponent,PROP_NAME,true,true);
	FMakeFileLine->AddString(".cpp "); 
	if (ReallyWriteInFile)
	{
//		FMakeFileLine->AddLine(NULL,"SRCS=",NULL,NULL);
		FMakeFileLine->AddLine(NULL,"SRCS=",NULL,"\n#");
	}
	ShowDebug("CreateMakeFile Quitting.");	
	return true;
}

bool TViewCodeGenerator::CreateConstructor(bool ReallyWriteInFile)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FHeaderCodeFile);
	FHeaderLine1->AddString("#include <View.h>\n"); 
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FHeaderCodeFile);
	FHeaderLine2->AddString("\t\tBView *"); 
	FHeaderLine2->AddProperty(FViewComponent,PROP_NAME,true,true); 
	FHeaderLine2->AddString(";\n"); 	
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"class","public:","}");

	TCodeLine *FBodyLine1 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine1->AddString("#include \""); 
	FBodyLine1->AddProperty(FViewComponent,PROP_NAME,true,true);
	FBodyLine1->AddString(".h\"\n"); 
	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"#",NULL,NULL);

	string ACtorLabel = FViewComponent->FParent->FClassName + "::";
	
	TCodeLine *FBodyLine2 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine2->AddString("\t"); 
	FBodyLine2->AddProperty(FViewComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new "); 
	FBodyLine2->AddProperty(FViewComponent,PROP_CLASSNAME,true,false);
//	FBodyLine2->AddString("(Bounds());\n"); 	
	FBodyLine2->AddString("(BRect(");	 	
	FBodyLine2->AddProperty(FViewComponent,PROP_LEFT,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FViewComponent,PROP_TOP,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FViewComponent,PROP_RIGHT,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FViewComponent,PROP_BOTTOM,true,false);
	FBodyLine2->AddString("));\n"); 	
	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine3 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine3->AddString("\trgb_color kDarkGray = {100,100,100,255};\n"); 
	if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine4 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine4->AddString("\trgb_color kGray = {219,219,219,255};\n"); 
	if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,"kDarkGray",";","}");

	TCodeLine *FBodyLine5 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine5->AddString("\t"); 
	FBodyLine5->AddProperty(FViewComponent,PROP_NAME,true,true);
	FBodyLine5->AddString("->SetViewColor(kGray);\n"); 	
	if (ReallyWriteInFile) FBodyLine5->AddLine(NULL," kGray","};","}");

	TCodeLine *FBodyLine6 = new TCodeLine(FViewComponent->FParent->FCodeGenerator->FBodyCodeFile);
	FBodyLine6->AddString("\tAddChild("); 
	FBodyLine6->AddProperty(FViewComponent,PROP_NAME,true,true);
	FBodyLine6->AddString(");\n"); 	
	if (ReallyWriteInFile) FBodyLine6->AddLine(NULL,ACtorLabel.c_str(),"SetViewColor","}");

	return true;
}

bool TViewCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile)
{
	return true;
}

void TViewCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);
/*	
// ------- COMPONENT LIST! --------------
	TComponent *AComponent = FViewComponent->FChildren->NextComponent(true);
	ShowDebug("TViewCodeGenerator::GenerateAll After NextComponent");
	while(AComponent!=NULL)
	{
		ShowDebug("TViewCodeGenerator::GenerateAll Before Generate");		
		AComponent->Generate(APath);
		ShowDebug("TViewCodeGenerator::GenerateAll After Generate");		
		AComponent = FViewComponent->FChildren->NextComponent(false);	
	}
*/
	ShowDebug("TViewCodeGenerator::GenerateAll Exit from While");
}


bool TViewCodeGenerator::PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile)
{
	FHeaderCodeFile = new TCodeFile(AClassName,APath,"h");
	FBodyCodeFile = new TCodeFile(AClassName,APath,"cpp");
	FMakeFileCodeFile = new TCodeFile("makefile",APath,NULL);

	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);

	CreateConstructor(ReallyWriteInFile);
	CreateMessageReceived(ReallyWriteInFile);	
	return true;
}


