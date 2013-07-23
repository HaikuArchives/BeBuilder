#include "ProjectComponent.h"

TProjectComponent::TProjectComponent(char *AComponentName, char *AClassName):TComponent(AComponentName,AClassName),BHandler(AComponentName)
//TProjectComponent::TProjectComponent(char *AComponentName, char *AClassName):TComponent(AComponentName,AClassName),BLooper(AComponentName)
{
	FDebugMode=1;
	FDebugMessage= "TProjectComponent ";

	FHandler = this;
	FElement = NULL;
	FCanGenerate = true;
	ShowDebug("Constructeur!");
	FCodeGenerator = new TProjectCodeGenerator(this,true);
	FPropertyList->AddProperty(PROP_NAME,AComponentName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_CLASSNAME,AClassName,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);

	FPropertyList->AddProperty(PROP_GENERATION_PATH,BE_BUILDER_GENERATION,PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FPropertyList->AddProperty(PROP_APP_SIGNATURE,"application/x-vnd.BeBuilderApp",PROP_TYPE_STRING,false,true,"",PROP_GENERAL_GROUP);
	FGenerationPath = "/boot/BeBuilder/Generation/";
	FPathGeneration = FGenerationPath;
	FIndex=0;
	ShowDebug("Constructeur Fin.");
}

TProjectComponent::~TProjectComponent()
{
	ShowDebug("destructor Inside");	
	delete FCodeGenerator;
	ShowDebug("destructor quitting");
}

bool TProjectComponent::RemoveChild(TComponent *AComponent)
{
	ShowDebug("-------- RemoveChild Project -------------");
	if (AComponent!=NULL)
	{
		ShowDebug("Before WhenRemoveChildProject ");
		AComponent->WhenRemoveChild();
		ShowDebug("Before RemoveComponent Project");
		FChildren->RemoveComponent(AComponent);
		ShowDebug("After RemoveComponent Project");
		BMessenger AMessenger(AComponent->FHandler);
		BMessage AMessage(B_QUIT_REQUESTED);
		AMessenger.SendMessage(&AMessage);	
	//	delete AComponent;
		ShowDebug("RemoveChild after SendMessage");

	}
	ShowDebug("----------- RemoveChild Quitting --------------");
	return true;
}



void TProjectComponent::MessageReceived(BMessage *message)
{
	char  *name; 
	const char *data2=NULL;
	uint32  type; 
	int32   count;
	string truc1,truc2; 
//	int ind;
	switch(message->what)
	{
		case MSG_PROPERTY_UPDATE :
				ShowDebug("MessageReceived Message d'update recu!\n");
				for (int32 i = 0; 
				message->GetInfo(B_STRING_TYPE, i, &name, &type, &count) == B_OK; 
				i++ ) 
				{ 				
				    data2 = message->FindString(name);

					if (data2!=NULL)
					{
						truc1 = name;
						truc2 = data2;
						ChangeProperty(truc1,truc2);
					}
				}
			break;
		default: BHandler::MessageReceived(message);
	}
}

//void TProjectComponent::Generate(char *APathName, TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
bool TProjectComponent::Generate(char *APathName)
{
	TJerFile *AJerFile;
	AJerFile = new TJerFile(NULL);
	AJerFile->CreateCompletePath("/",FGenerationPath.c_str());
/*
	if (FCodeGenerator!=NULL)
	{
		printf("TProjectComponent::Generate Call To GenerateAll\n");
		FCodeGenerator->GenerateAll(APathName,FComponentName.c_str(),AParentFileRWHeader,AParentFileRWCPP);
		printf("TProjectComponent::Generate End Of Call To GenerateAll\n");
	}
*/	
//	TComponent::Generate(FGenerationPath.c_str(),AParentFileRWHeader,AParentFileRWCPP);
	return TComponent::Generate(FGenerationPath.c_str());
}

//string TProjectComponent::GetNextComponentIndex(const char *AInitialName)
void TProjectComponent::GetNextComponentIndex(string *AComponentName, string *AClassName)
{
	FIndex++;
//	string truc;
//	truc = AInitialName ;
//	truc = truc + IntToStr(FIndex);
	*AComponentName = *AComponentName + IntToStr(FIndex);
	*AClassName = *AClassName + IntToStr(FIndex);
//	return truc.c_str();
}
const char *TProjectComponent::GetGenerationPath(void)
{
	return FGenerationPath.c_str();
}

void TProjectComponent::SetGenerationPath(const char* AGenerationPath)
{
	FGenerationPath = AGenerationPath;
	int ind = FGenerationPath.length();
	if (ind !=0)
	{
		if (FGenerationPath[ind-1]!='/')
		{
			FGenerationPath = FGenerationPath + '/'	;
		}
	}
	else
		FGenerationPath = "/";
	// this line is a hack to allow modification of the generation path from BeBuilder Window...
	FPropertyList->SetPropertyValue(PROP_GENERATION_PATH,FGenerationPath);		
}

const char *TProjectComponent::GetExe(void)
{
//	string AStr = FGenerationPath + "BeBuilderApp";
	string AStr ="BeBuilderApp";
	return AStr.c_str();
}


bool TProjectComponent::ChangeProperty(string APropertyName, string APropertyValue)
{
	ShowDebug("ChangeProperty Inside.");
//	int ind;
	ShowDebug("ChangeProperty Before SetStandardProperties.");
	SetStandardProperties(APropertyName.c_str(),APropertyValue.c_str());
	ShowDebug("ChangeProperty After SetStandardProperties.");
	FPropertyList->SetPropertyValue(APropertyName,APropertyValue);
	ShowDebug("ChangeProperty After SetPropertyValue.");
	if (FindPropertyName(APropertyName,PROP_GENERATION_PATH))
	{
		ShowDebug("ChangeProperty After FindPropertyName.");
		SetGenerationPath(APropertyValue.c_str());
/*
		ind = APropertyValue.length();
		if (ind !=0)
		{
			if (APropertyValue[ind-1]!='/')
			{
				APropertyValue = APropertyValue + '/'	;
			}
		}
		else
			APropertyValue = "/";
		FGenerationPath = APropertyValue;
*/
		FPathGeneration = FGenerationPath;		
	}
	ShowDebug("ChangeProperty Before Asking a dynamic regeneration.");
	return TComponent::ChangeProperty(APropertyName,APropertyValue);		
	
//	(FPropertyList->GetProperty(APropertyName))->UpdateCode();
//	ShowDebug("TProjectComponent::MessageReceived After Asking a dynamic regeneration.");
//	return true;
}


