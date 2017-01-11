#include "SliderCodeGenerator.h"
#include "SliderComponent.h"

TSliderCodeGenerator::TSliderCodeGenerator(TSliderComponent * ASliderComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FSliderComponent = ASliderComponent;
}
/*
void TSliderCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TSliderCodeGenerator::GenerateAll ClassName : %s \n", ClassName);
	InsertionContructor(AParentFileRWHeader,AParentFileRWCPP);
	printf("Inside TSliderCodeGenerator::GenerateAll before InsertionMessageReceived\n");
	InsertionMessageReceived(AParentFileRWHeader,AParentFileRWCPP);
	printf("Inside TSliderCodeGenerator::GenerateAll before AttachedTowindow\n");
	InsertionAttachedToWindow(AParentFileRWHeader,AParentFileRWCPP);
	printf("TSliderCodeGenerator::GenerateAll After InsertionAttachedToWindow \n");	
}


bool TSliderCodeGenerator::InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TSliderCodeGenerator::InsertionContructor \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TListViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the Header!
	InsideWhich = "#ifndef"; //found the #ifndef
	AfterWhat ="#define"; // found the #define
	MustBeAdded = "#include <Slider.h>\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;

	InsideWhich = "class"; //found the #ifndef
	AfterWhat ="public:"; // found the #define
//	BeforeWhat = "}";
	MustBeAdded = "\t\tBSlider *" + FSliderComponent->FComponentName ;
	MustBeAdded = MustBeAdded + ";\n";
	resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	if (!resultat) return false;
//In the CPP!
	InsideWhich = "{"; //constructor is the first in the file!.... that was generated like that!
//	else InsideWhich = "::" + FViewComponent->FParent->FClassName;
	AfterWhat = "{";
	//BeforeWhat = "}";

	MustBeAdded = "\tBRect ARect" + FSliderComponent->FComponentName + "(";
	MustBeAdded = MustBeAdded +	FSliderComponent->FPropertyList->GetPropertyValue(PROP_LEFT).c_str()+",";
	MustBeAdded = MustBeAdded +	FSliderComponent->FPropertyList->GetPropertyValue(PROP_TOP).c_str()+",";
	MustBeAdded = MustBeAdded +	FSliderComponent->FPropertyList->GetPropertyValue(PROP_RIGHT).c_str()+",";
	MustBeAdded = MustBeAdded +	FSliderComponent->FPropertyList->GetPropertyValue(PROP_BOTTOM).c_str()+");\n";	
	MustBeAdded = MustBeAdded +"\t" +FSliderComponent->FComponentName +" = new BSlider(ARect";
	MustBeAdded = MustBeAdded + FSliderComponent->FComponentName +",\"";
	MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_NAME).c_str() +"\",\"";
	MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_LABEL).c_str() +"\",";
	if (FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{
		MustBeAdded = MustBeAdded + "new BMessage(";
		MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str() +"),";
	}
	else
		MustBeAdded = MustBeAdded + "NULL,";
	MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_MIN).c_str() +",";
	MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_MAX).c_str() +",";
	MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_THUMB).c_str() +",";
	MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_RESIZING_MODE).c_str() +",";
	MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_FLAGS).c_str() +");\n";

	MustBeAdded = MustBeAdded + "\tAddChild("+ FSliderComponent->FComponentName+");\n";
	return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
}

bool TSliderCodeGenerator::InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TButtonCodeGenerator::InsertionMessageReceived \n");
	bool resultat;
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
//	printf("Inside TViewCodeGenerator::InsertionContructor After Test if file are null!\n");
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;

//In the CPP!
	if (FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the Header!
		InsideWhich = "#ifndef"; //found the #ifndef
		AfterWhat ="#define"; // found the #define
		MustBeAdded = "#define ";
		MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " '";		
//		MustBeAdded = MustBeAdded + FButtonComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + StrCopy(FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str();
		MustBeAdded = MustBeAdded + "'\n";		
		resultat = AddInFunctionPlus(AFileRWHeader,InsideWhich.c_str(),AfterWhat.c_str(),NULL,MustBeAdded.c_str());
	
		printf("TSliderCodeGenerator::InsertionMessageReceived Message Existe!\n");
		InsideWhich = "::MessageReceived"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "switch";
		BeforeWhat = "defaut";

		MustBeAdded = "\t case ";
		MustBeAdded = MustBeAdded + FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).c_str();
		MustBeAdded = MustBeAdded + " :\n";
		MustBeAdded = MustBeAdded +	"//Insert the Handler for the button here! \n";
		MustBeAdded = MustBeAdded +	"\t\tbreak;\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}

bool TSliderCodeGenerator::InsertionAttachedToWindow(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP)
{
	printf("Inside TSliderCodeGenerator::InsertionAttachedToWindow \n");
	if (AFileRWHeader==NULL) return false;
	if (AFileRWCPP==NULL) return false;
	string InsideWhich;
	string AfterWhat;
	string BeforeWhat;
	string MustBeAdded;
	if (FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()>0)
	{	
//In the CPP!
		InsideWhich = "::AttachedToWindow"; //constructor is the first in the file!.... that was generated like that!
		AfterWhat = "{";
		BeforeWhat = "BView";
		MustBeAdded = "\t" + FSliderComponent->FComponentName + "->SetTarget(this);\n";
		return AddInFunctionPlus(AFileRWCPP,InsideWhich.c_str(),AfterWhat.c_str(),BeforeWhat.c_str(),MustBeAdded.c_str());
	}
	return false;
}
*/

void TSliderCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	TCodeGenerator::GenerateAll(APath,ClassName);
	ShowDebug(string("GenerateAll ClassName=")+ClassName);
	FHeaderCodeFile = FSliderComponent->FParent->FCodeGenerator->FHeaderCodeFile;
	FBodyCodeFile = FSliderComponent->FParent->FCodeGenerator->FBodyCodeFile;
	ShowDebug(string("GenerateAll ClassName=") + ClassName);
	PrepareCode(APath,ClassName,true);	

}
bool TSliderCodeGenerator::CreateBody(bool ReallyWriteInFile)
{
	return true;
}
bool TSliderCodeGenerator::CreateHeader(bool ReallyWriteInFile)
{
	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#include <Slider.h>\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FHeaderLine2 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine2->AddString("#include <Rect.h>\n");
	if (ReallyWriteInFile) FHeaderLine2->AddLine(NULL,"#ifndef","#define",NULL);


	TCodeLine *FHeaderLine3 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine3->AddString("\t\tBSlider *F");
	FHeaderLine3->AddProperty(FSliderComponent,PROP_NAME,true,true);
	FHeaderLine3->AddString(";\n");
	if (ReallyWriteInFile) FHeaderLine3->AddLine(NULL,"class","public:",NULL);	
	return true;
}
bool TSliderCodeGenerator::CreateMakeFile(bool ReallyWriteInFile)
{
	return true;
}
bool TSliderCodeGenerator::CreateConstructor(bool ReallyWriteInFile)
{
	string ACtorLabel = FSliderComponent->FParent->FClassName + "::" + FSliderComponent->FParent->FClassName;

	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tBRect ARect");
	FBodyLine1->AddProperty(FSliderComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("(");
	FBodyLine1->AddProperty(FSliderComponent,PROP_LEFT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FSliderComponent,PROP_TOP,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FSliderComponent,PROP_RIGHT,true,false);
	FBodyLine1->AddString(",");	 	
	FBodyLine1->AddProperty(FSliderComponent,PROP_BOTTOM,true,false);
	FBodyLine1->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,ACtorLabel.c_str(),"{","}");

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\tF");
	FBodyLine2->AddProperty(FSliderComponent,PROP_NAME,true,true);
	FBodyLine2->AddString("=new BSlider(ARect");
	FBodyLine2->AddProperty(FSliderComponent,PROP_NAME,false,false);
	FBodyLine2->AddString(",\"");	 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_NAME,false,false);
	FBodyLine2->AddString("\",\"");	 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_LABEL,true,false);
	FBodyLine2->AddString("\",");	
	FBodyLine2->BeginBoolean(FSliderComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString("new BMessage(");	
	FBodyLine2->EndBoolean(); 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_MESSAGE,true,false);
	FBodyLine2->BeginBoolean(FSliderComponent,PROP_MESSAGE,DIFF_OPERATION,"NULL",false,false);
	FBodyLine2->AddString(")");	
	FBodyLine2->EndBoolean(); 		
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_MIN,true,false);	
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_MAX,true,false);	
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_THUMB,true,false);	
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_RESIZING_MODE,true,false);
	FBodyLine2->AddString(",");	 	
	FBodyLine2->AddProperty(FSliderComponent,PROP_FLAGS,true,false);
	FBodyLine2->AddString(");\n"); 	

	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

/*
	TCodeLine *FBodyLine3 = new TCodeLine(FBodyCodeFile);
	FBodyLine3->AddString("\tF");
	FBodyLine3->AddProperty(FSliderComponent,PROP_NAME,true,true);
	FBodyLine3->AddString("->MakeDefault(");
	FBodyLine3->AddProperty(FSliderComponent,PROP_DEFAULT,true,false);
	FBodyLine3->AddString(");\n");
	if (ReallyWriteInFile) FBodyLine3->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");
*/
	TCodeLine *FBodyLine4 = new TCodeLine(FBodyCodeFile);
	FBodyLine4->AddString("\tAddChild(F");
	FBodyLine4->AddProperty(FSliderComponent,PROP_NAME,true,true);
	FBodyLine4->AddString(");\n");

	if (ReallyWriteInFile) FBodyLine4->AddLine(NULL,ACtorLabel.c_str(),NULL,"}");

	return true;
}
bool TSliderCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile)
{
	TCodeLine *FBodyLine1 = new TCodeLine(FBodyCodeFile);
	FBodyLine1->AddString("\tF");
	FBodyLine1->AddProperty(FSliderComponent,PROP_NAME,true,true);
	FBodyLine1->AddString("->SetTarget(this);\n");

	if (ReallyWriteInFile) FBodyLine1->AddLine(NULL,"::AttachedToWindow","{",NULL);
	

	TCodeLine *FHeaderLine1 = new TCodeLine(FHeaderCodeFile);
	FHeaderLine1->AddString("#define ");
	FHeaderLine1->AddProperty(FSliderComponent,PROP_MESSAGE,true,true);
	FHeaderLine1->AddString(" '");
	FHeaderLine1->AddString(StrCopy(FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE),FSliderComponent->FPropertyList->GetPropertyValue(PROP_MESSAGE).length()-4,4).c_str());
	FHeaderLine1->AddString("'\n");
	if (ReallyWriteInFile) FHeaderLine1->AddLine(NULL,"#ifndef","#define",NULL);

	TCodeLine *FBodyLine2 = new TCodeLine(FBodyCodeFile);
	FBodyLine2->AddString("\t case ");
	FBodyLine2->AddProperty(FSliderComponent,PROP_MESSAGE,true,true);
	FBodyLine2->AddString(" :\n");
	FBodyLine2->AddString("//Insert the Handler for the Slider here! \n");
	FBodyLine2->AddString("\t\tbreak;\n");	
	if (ReallyWriteInFile) FBodyLine2->AddLine(NULL,"::MessageReceived","switch","\t\tdefault");


	return true;
}
bool TSliderCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile)
{
	TCodeGenerator::PrepareCode(APath,AClassName,ReallyWriteInFile);
	CreateConstructor(ReallyWriteInFile);
//	CreateMessageReceived(ReallyWriteInFile);	//Will be called in the Component Object.
	return true;
}


