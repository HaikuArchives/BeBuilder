#include "Parser.h"
#include <strstream>

TParser::TParser(void):TObject("TParser")
{
	FDebugMode = 0;
	FDebugMessage="TParser ";
}

TParser::~TParser(void)
{

}

bool TParser::DecaleFile(off_t FromLocation, off_t ToLocation, BFile *AFile)
{
	off_t ACurrentReadLocation;
	off_t ACurrentWriteLocation;
	int BufferSize=32;
	char *Buffer1=NULL;
	char *Buffer2=NULL;
	int InsideBuffer1=0;
	int InsideBuffer2=0;
	bool Mode1 = false;
	bool Mode2 = false;
	bool FinalMode = false;
	if (FromLocation < ToLocation)
	{
		while (BufferSize <= (ToLocation-FromLocation))
		{
			BufferSize = 2 * BufferSize;	
		}
		Buffer1 = (char *)malloc(sizeof(char)*BufferSize);
		Buffer2 = (char *)malloc(sizeof(char)*BufferSize);
		ACurrentReadLocation = FromLocation;
		ACurrentWriteLocation = ToLocation;		
		InsideBuffer1 = AFile->ReadAt(ACurrentReadLocation,Buffer1,BufferSize);
		ACurrentReadLocation += InsideBuffer1;
		Mode1 = true;
		for(;;)
		{
			if ((Mode1) && (InsideBuffer1==0)) break;
			if ((Mode2) && (InsideBuffer2==0)) break;
			if ((FinalMode) && (Mode1))
			{
				AFile->WriteAt(ACurrentWriteLocation,Buffer1,InsideBuffer1);
				break;								
			}
			if ((FinalMode) && (Mode2))
			{
				AFile->WriteAt(ACurrentWriteLocation,Buffer2,InsideBuffer2);
				break;				
			}			
			if (Mode1)
			{
				InsideBuffer2 = AFile->ReadAt(ACurrentReadLocation,Buffer2,BufferSize);
				ACurrentReadLocation += InsideBuffer2;
				AFile->WriteAt(ACurrentWriteLocation,Buffer1,InsideBuffer1);
				ACurrentWriteLocation += InsideBuffer1;
				if (ACurrentWriteLocation >= ACurrentReadLocation )
				{
					FinalMode = true;
				}
				Mode1 = false; Mode2 = true;	
			}
			else
			{
				if (Mode2)
				{
					InsideBuffer1 = AFile->ReadAt(ACurrentReadLocation,Buffer1,BufferSize);
					ACurrentReadLocation += InsideBuffer1;
					AFile->WriteAt(ACurrentWriteLocation,Buffer2,InsideBuffer2);
					ACurrentWriteLocation += InsideBuffer2;											
// Added After Release of BeBuilder V0.4a
				if (ACurrentWriteLocation >= ACurrentReadLocation )
				{
					FinalMode = true;
				}
//
					Mode1 = true; Mode2 = false;
				}
			}
		}
	}
	else
	{		
		if(ToLocation < FromLocation)
		{
			BufferSize = 1024;
			Buffer1 = (char *)malloc(sizeof(char)*BufferSize);
			ACurrentReadLocation = FromLocation;
			ACurrentWriteLocation = ToLocation;
			
			for (;;)
			{
				InsideBuffer1 = AFile->ReadAt(ACurrentReadLocation,Buffer1,BufferSize);
				if (InsideBuffer1==0) break;
				ACurrentReadLocation += InsideBuffer1;
				AFile->WriteAt(ACurrentWriteLocation,Buffer1,InsideBuffer1);
				ACurrentWriteLocation += InsideBuffer1;								
			}
			// Set Size
			off_t TailleFichier;
			AFile->GetSize(&TailleFichier);
			TailleFichier -=  (FromLocation - ToLocation);
			AFile->SetSize(TailleFichier);		
		}
	}
	
	if (Buffer1 != NULL) free(Buffer1);
	if (Buffer2 != NULL) free(Buffer2);	
	return true;
}

bool TParser::DeleteString(off_t location,string AStrToDelete,BFile *AFile)
{
	if (AFile==NULL) return false;
	off_t resultat = FindInFile(location,AStrToDelete,AFile);
	if (resultat ==-1) return false;

	int start = resultat + AStrToDelete.length();
	int stop = resultat;
	ShowDebug(string("DeleteFile start=") + IntToStr(start));
	//printf("DeleteFile start=%d stop= %d \n",start,stop);
	DecaleFile(start,stop,AFile);
	return true;
}

bool TParser::ReplaceString(off_t location, string AStrToFind,string AReplaceString,BFile *AFile)
{
	char AChar;
	if (AFile==NULL) return false;
	off_t resultat = FindInFile(location,AStrToFind,AFile);
	if (resultat ==-1) return false;
	int start = 0;
	int stop = 0;
	if (AStrToFind.length()>AReplaceString.length())
	{
		start = resultat + AReplaceString.length();
		stop = start - (AStrToFind.length() - AReplaceString.length());
//		printf("DecaleFile1 start=%d stop=%d \n",start,stop);
		DecaleFile(start,stop,AFile);		
	}
	else
	{
		if (AReplaceString.length() > AStrToFind.length())
		{
			start = resultat + AStrToFind.length();
			stop = start + (AReplaceString.length() - AStrToFind.length());		
//			printf("DecaleFile2 start=%d stop=%d \n",start,stop);
			DecaleFile(start,stop,AFile);
		}		
	}	
//	printf("DecaleFile terminated.\n");
		
	for (int ind=0; ind<AReplaceString.length();ind++)
	{
		AChar = AReplaceString[ind];
		AFile->WriteAt(resultat,&AChar,1);		
		resultat ++;
	}	
	AFile->Sync();
	return true;
}

bool TParser::InsertString(off_t location, string AStr, BFile *AFile)
{
	char AChar;
	off_t ALocation = location;

	int start = location;
	int stop = start + AStr.length();
	
//	printf("Calling DecaleFile start=%d strlength = %d Stop= %d \n",start,AStr.length(),stop);
	DecaleFile(start,stop,AFile);
//	printf("Fichier decale! \n");
	for (int ind=0; ind<AStr.length();ind++)
	{
		AChar = AStr[ind];
		AFile->WriteAt(ALocation,&AChar,1);		
		ALocation ++;
	}
	AFile->Sync();
	return true;
}


off_t TParser::FindInFile(off_t FromLocation, string AStr, BFile *AFile)
{
	off_t Resultat = -1;
	off_t ALocation = FromLocation;
	string AReadString;
	int ABufferLength = AStr.length();
	int AReadLength=0;
//	char *ABuffer = (char *)malloc(sizeof(char)*ABufferLength); // no +1 for \0
	char *ABuffer = (char *)malloc(sizeof(char)*(ABufferLength + 1)); // no +1 for \0
	
	// Go where everything is
//	printf("FindInFile Inside Astr= %s BufferLength= %d ALocation= %d \n",AStr.c_str(),ABufferLength,ALocation);		
	AFile->Seek(ALocation,SEEK_SET);
//	printf("FindInFile Before ReadAt \n");		
	AReadLength = AFile->ReadAt(ALocation,(void *)ABuffer,ABufferLength);
//	printf("FindInFile After ReadAt \n");		
	while(AReadLength > 0)
	{
//		printf("FindInFile ReadLen=%d \n",AReadLength);		
		ABuffer[AReadLength]='\0';
//		printf("FindInFile ABuffer=%c \n",*ABuffer);		
		string UneChaine3(ABuffer);
//		printf("UneChaine3=%s\n",UneChaine3.c_str());

//		printf("FindInFile ABuffer=%s \n",ABuffer);		
		string UneChaine2(ABuffer,0,AReadLength);
//		string UneChaine2((char *)ABuffer,0,AReadLength);
//		string UneChaine2(ABuffer,0,AReadLength-1);
//		printf("UneChaine2=%s\n",UneChaine2.c_str());		
		AReadString += UneChaine2;
		if (AReadString.find(AStr.c_str())!=-1)
		{
//			printf("AReadString=%s \n AStr= %s \n resultat= %d \n",AReadString.c_str(),AStr.c_str(),AReadString.find(AStr.c_str()));
//			return ALocation;
			Resultat = FromLocation + AReadString.find(AStr.c_str());
//			return FromLocation + AReadString.find(AStr.c_str());
			break;
		}
		ALocation += AReadLength;
		AReadLength = AFile->ReadAt(ALocation,ABuffer,ABufferLength);		
	}
	delete ABuffer;	
//	AFile->Unset(); // Never the function that uses this param is reponsible to close it.
	return Resultat;		
}

off_t TParser::FindNextLine(off_t FromLocation, BFile *AFile) //Return the off_set of the \n in the sequence \r\n that finishes a line and a file.
{
//	off_t resultat = FindInFile(FromLocation,"\r\n", AFile);
	off_t resultat = FindInFile(FromLocation,"\n", AFile);
	if (resultat != -1)
	{
//		return resultat + 2; // 2 because length(\r\n)==2
		return resultat + 1; // 2 because length(\r\n)==2
	}
	return -1;
}
