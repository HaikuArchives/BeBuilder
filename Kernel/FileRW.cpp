#include "FileRW.h"
//#define MAX_LINE_SIZE 50

TFileRW::TFileRW(const char* AFileNameAndPath):TFileWriter(AFileNameAndPath),TFileReader(AFileNameAndPath)
{
//	FFileNameAndPath = AFileNameAndPath;
//	FFileSize = 0;
//	FNbBytesRead = 0;
//	FNbBytesWrite = 0;	
//	TheBFileRW = NULL;	
//	OpenRW(&TheBFileRW);		
}

TFileRW::~TFileRW()
{
	printf("TFileRW Destructor\n");
//	if (TheBFileRW!=NULL) delete TheBFileRW;
}

void TFileRW::OpenRW(BFile **ABFile)
{
	if (*ABFile!=NULL) delete (*ABFile);
	(*ABFile) = new BFile;
	(*ABFile)->SetTo(TFileReader::FFileNameAndPath.c_str(),B_READ_WRITE); 
	(*ABFile)->GetSize(&FFileSize);
}
/*
void TFileRW::OpenR(BFile **ABFile)
{
	if (*ABFile!=NULL) delete (*ABFile);
	(*ABFile) = new BFile;
	(*ABFile)->SetTo(FFileNameAndPath.c_str(),B_READ_ONLY); 
	(*ABFile)->GetSize(&FFileSize);
}
*/
/*
bool TFileRW::ReadData (char **ABuffer,uint32 nbRead)
{
	bool resultat = false;
	char *sav;
	uint32 truc;
	if (TheBFileRW)
	{
		*ABuffer = (char *)malloc(sizeof(char)* (nbRead+1));
		truc = TheBFileRW->Read(*ABuffer,nbRead);
		if (truc!=nbRead) resultat = false;
		FNbBytesRead += truc;
//		*sav='\0';		
	}
	return resultat;
}
*/
/*
bool TFileRW::ReadALine (string *truc)
{
	bool resultat = false;
	if (TheBFileRW)
	{
		char ch;
		*truc = "";
		if (FNbBytesRead>=FFileSize)
		{
			resultat = false;		
		}
		else
		{
			resultat = true;
			for (;;)
			{
				TheBFileRW->Read(&ch,1);
				FNbBytesRead++;
				if ((ch=='\0') || (ch=='\n')) break;
				else
				{
					*truc = *truc + ch;			
					if (TheBFileRW->Position()==(FFileSize)) break;
				}
			}		
		}
	}
	return resultat;	
}
*/
/*
bool TFileRW::WriteALine (string truc)
{
	bool resultat = false;
	if (TheBFileRW)
	{
		resultat = true;
		WriteData(truc.c_str(),strlen(truc.c_str()));				
	}
	return resultat;	
}
*/
/*
bool TFileRW::InsertALine (string truc)	
{
	bool IsTrucWritten = false;
	char *buf;
	int NbBytesToRead = truc.length();
	TFileReader *AFileReader;
	AFileReader = new TFileReader(FFileNameAndPath.c_str());
//	printf("TFileRW::InsertALine Nouvelle Pos : %d\n",TheBFileRW->Position());
	AFileReader->GetToPosition(TheBFileRW->Position());
//	printf("NbBytesToRead: %d\n",NbBytesToRead);
	while (AFileReader->ReadDataAt(TheBFileRW->Position(),&buf,NbBytesToRead))	
	{
//		printf("----->Read: %s \n ---> Will be written %s \n", buf, truc.c_str());
		TheBFileRW->Write(truc.c_str(),truc.length());
		truc = buf;		
		IsTrucWritten = true;
	}
	if (IsTrucWritten==false)
	{
		TheBFileRW->Write(truc.c_str(),truc.length());
	}
//	printf("Read: %s , Will be written %s \n", buf, truc.c_str());
	TheBFileRW->Write(buf,strlen(buf));

}
*/
bool TFileRW::InsertALine (string truc)	
{
	bool IsTrucWritten = false;
	char *buf;
	int NbBytesToRead = truc.length();
	GetToPosition(GetPositionWriter()); //Reader is set at position
//	printf("NbBytesToRead: %d\n",NbBytesToRead);
	while (ReadDataAt(GetPositionWriter(),&buf,NbBytesToRead))	
	{
//		printf("----->Read: %s \n ---> Will be written %s \n", buf, truc.c_str());
		WriteData(truc.c_str(),truc.length());
		truc = buf;		
		IsTrucWritten = true;
	}
//	printf("Before LastWrite: %s \n", truc.c_str());
	WriteData(truc.c_str(),truc.length());
//	printf("LastWrite: %s \n", buf);
	WriteData(buf,strlen(buf));
	return true;
}

int TFileRW::GetPositionReader(void)
{
	return TheBFileReader->Position();
}

int TFileRW::GetPositionWriter(void)
{
	return TheBFileWriter->Position();
}

const char *TFileRW::GetFileName(void)
{
	return TFileWriter::FFileNameAndPath.c_str();
}

int32 TFileRW::ResetReader(void)
{
	return GetToPosition(0);
}
