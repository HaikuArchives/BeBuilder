#include <Alert.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

void ShowMessage(const char *);
void ShowMessage(char *);
void ShowMessage(const char *,BRect);
void ShowMessage(const char *,BPoint);
void ShowMessage(const char *,long);
void ShowMessageHexa(const char *, long);
void ShowMessage(const char *, const char *);
void ShowMessage(string);
//-------CONVERSION TOOLS---------------
char *IntToStr(int AInteger);
char *IntToStr(long ALong);
char *FloatToStr(float AFloat);
char *FloatToStr(double ADouble);
int StrToInt(const char *AStr);
long StrToLong(const char *AStr);
double StrToDouble(const char *AStr);
int StrToInt(char *AStr);
long StrToLong(char *AStr);
double StrToDouble(char *AStr);
//-----------STRING MANIPULATION-----------
string StrCopy(const string AString, uint32 Start, uint32 length);
bool IsFoundInside(string AString, const char *AValueToFind);

void ShowMessage(const char *Message)
{
	BAlert*				alert = new BAlert("Debug Only", Message, "OK");
	alert->Go();	
}

void ShowMessage(char * Message)
{
	BAlert*				alert = new BAlert("Debug Only", Message, "OK");
	alert->Go();	
}


void ShowMessage(const char *Message,BRect rect)
{
	char *Message2;
	Message2 = (char *) malloc ((strlen(Message) + 1 + 4 * 20)*sizeof(char));
//	strcpy(Message2,Message);
	sprintf(Message2,"%s : left: %f, top: %f, right: %f, bottom: %f",Message,rect.left,rect.top,rect.right,rect.bottom);	
	BAlert*				alert = new BAlert("Debug Only", Message2, "OK");
	alert->Go();	
}

void ShowMessage(const char *Message,BPoint point)
{
	char *Message2;
	Message2 = (char *) malloc ((strlen(Message) + 1 + 4 * 20)*sizeof(char));
//	strcpy(Message2,Message);
	sprintf(Message2,"%s : x: %f, y: %f",Message,point.x,point.y);	
	BAlert*				alert = new BAlert("Debug Only", Message2, "OK");
	alert->Go();	
}

void ShowMessage(const char *Message, long truc)
{
	char *Message2;
	Message2 = (char *) malloc ((strlen(Message) + 1 + 100)*sizeof(char));
	sprintf(Message2,"%s : %ld",Message,truc);
	BAlert*				alert = new BAlert("Debug Only", Message2, "OK");
	alert->Go();	
}

void ShowMessageHexa(const char *Message, long truc)
{
	char *Message2;
	Message2 = (char *) malloc ((strlen(Message) + 1 + 100)*sizeof(char));
	sprintf(Message2,"%s : %lx",Message,truc);
	BAlert*				alert = new BAlert("Debug Only", Message2, "OK");
	alert->Go();	
}

void ShowMessage(const char *Message, const char *MessageSuite)
{
	char *Message2;
	Message2 = (char *) malloc ((strlen(Message) + 1 +strlen(MessageSuite))*sizeof(char));
	sprintf(Message2,"%s : %s",Message,MessageSuite);

	BAlert*				alert = new BAlert("Debug Only", Message2, "OK");
	alert->Go();	
}

void ShowMessage(string AString)
{
	BAlert*	alert = new BAlert(NULL, AString.c_str(), "OK");
	alert->Go();		
}


//-------CONVERSION TOOLS---------------
char *IntToStr(int AInteger)
{
	char *resultat; //30 is the maximum number of digits
	resultat = (char *)malloc(sizeof(char) *(30+1));
	sprintf(resultat,"%d",AInteger);
	return resultat;
}

char *IntToStr(long ALong)
{
	char *resultat; //30 is the maximum number of digits
	resultat = (char *)malloc(sizeof(char) *(30+1));
	sprintf(resultat,"%ld",ALong);
	return resultat;
}

char *FloatToStr(float AFloat)
{
	char *resultat; //30 is the maximum number of digits
	resultat = (char *)malloc(sizeof(char) *(30+1));
	sprintf(resultat,"%f",AFloat);
	return resultat;
}

char *FloatToStr(double ADouble)
{
	char *resultat; //30 is the maximum number of digits
	resultat = (char *)malloc(sizeof(char) *(30+1));
	sprintf(resultat,"%f",ADouble);
	return resultat;
}

int StrToInt(const char *AStr)
{
	return atoi(AStr);
}

long StrToLong(const char *AStr)
{
	return atol(AStr);
}

double StrToDouble(const char *AStr)
{
	return atof(AStr);
}

int StrToInt(char *AStr)
{
	return atoi(AStr);
}

long StrToLong(char *AStr)
{
	return atol(AStr);
}

double StrToDouble(char *AStr)
{
	return atof(AStr);
}

string StrCopy(string AString, int Start, int length)
{
 string truc = AString;
 string outtruc = "";
// if (Start > truc.length()) return outtruc;
 if (Start > truc.length()) return AString;
 for (long index= Start; index < Start + length; index++)
 {
 	outtruc = outtruc + truc[index];
 }
 return outtruc;
}

void PrintMessage(BMessage *AMessage,int tab)
{
	printf("-- Debut Niveau %d --\n",tab);
	AMessage->PrintToStream();
	BMessage AMessageBuffer;
	char *name;
	uint32 type;
	int32 count;
	for (int32 ind=0;
		AMessage->GetInfo(B_ANY_TYPE,ind,&name,&type,&count)==B_OK; ind++)
	{
//		printf("Niveau %d found name= %s count= %d \n",tab,name,count);
		if (type==B_MESSAGE_TYPE)
		{
			for (int32 index=0;index<count;index++)
			{
				AMessage->FindMessage(name,index,&AMessageBuffer);
				PrintMessage(&AMessageBuffer,tab+1);	
			}
		}
	}
	printf("-- Fin Niveau %d --\n",tab);
}

bool IsFoundInside(string AString, const char *AValueToFind)
{
	long res;
	res = AString.find(AValueToFind);
//	ShowDebug(string("FindPropertyName APropertyName=") + APropertyName + string(" AValueToFind=") + string(AValueToFind) + string(" res=") + IntToStr(res));
	if (res >= 0 )
	{
		return true;
	}
	return false;
}


