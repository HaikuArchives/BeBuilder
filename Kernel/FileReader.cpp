#include "FileReader.h"
//#define MAX_LINE_SIZE 50

TFileReader::TFileReader(const char* AFileNameAndPath)
{
	FFileNameAndPath = AFileNameAndPath;
	FFileSize = 0;
	FNbBytesRead = 0;
	TheBFileReader = NULL;
	OpenR(&TheBFileReader);
}

TFileReader::~TFileReader()
{
//	printf("TFileReader Destructor\n");
	if (TheBFileReader!=NULL) delete TheBFileReader;
}

void TFileReader::OpenR(BFile **ABFile)
{
	if (*ABFile!=NULL) delete (*ABFile);
	(*ABFile) = new BFile;
	(*ABFile)->SetTo(FFileNameAndPath.c_str(),B_READ_ONLY); 
	(*ABFile)->GetSize(&FFileSize);
}

bool TFileReader::ReadData (char **ABuffer,int nbRead)
{
	bool resultat = false;
//	char *sav;
	int truc;
	if (TheBFileReader)
	{
		*ABuffer = (char *)malloc(sizeof(char)* (nbRead+1));
		truc = TheBFileReader->Read(*ABuffer,nbRead);
		if (truc!=nbRead) resultat = false;
		FNbBytesRead += truc;
	}
	return resultat;
}

bool TFileReader::ReadDataAt (int32 location,char **ABuffer,int nbRead)
{
	bool resultat = false;
	char *sav;
	int newNb;
	int truc;
	if (TheBFileReader)
	{
		
//	off_t FFileSize;
//	int32 FNbBytesRead;
	//	printf("TFileReader::ReadDataAt nbRead: %d, Diff: %d\n",nbRead,(FFileSize - FNbBytesRead));		
		TheBFileReader->GetSize(&FFileSize);
		if (nbRead>(FFileSize - FNbBytesRead))
			newNb = (FFileSize - FNbBytesRead); //pour eliminer le garbage... si on depasse la fin du fichier!
		else
			newNb = nbRead;
		*ABuffer = (char *)malloc(sizeof(char)* (newNb+1));
		sav = *ABuffer;

		truc = TheBFileReader->ReadAt(location,*ABuffer,newNb);
		if (truc==nbRead) resultat = true; //Il faut conserver le test avec nbRead et non pas avec newNb
		if (newNb!=nbRead)
		{
			sav = sav + (newNb);
			*sav ='\0';
		}
	//	printf("TFileReader::ReadDataAt lecture de %d bytes sur %d demandes! \n",truc,nbRead);
		FNbBytesRead += truc;
	}
	return resultat;
}


bool TFileReader::ReadALine (string *truc)
{
	bool resultat = false;
	if (TheBFileReader)
	{
		char ch;
		*truc = "";
		TheBFileReader->GetSize(&FFileSize);
		if (FFileSize==0) return false;
		if (FNbBytesRead>=FFileSize)
		{
			resultat = false;		
		}
		else
		{
			resultat = true;
			for (;;)
			{
				TheBFileReader->Read(&ch,1);
				FNbBytesRead++;
				if ((ch=='\0') || (ch=='\n')) break;
				else
				{
					*truc = *truc + ch;			
					if (TheBFileReader->Position()==(FFileSize)) break;
				}
			}		
		}
	}
	return resultat;	
}


int32 TFileReader::GetToPosition(int32 APosition)
{
	if (TheBFileReader)	
	{
		FNbBytesRead = TheBFileReader->Seek(APosition,SEEK_SET);
		return FNbBytesRead;
	}
	return -1;
}
