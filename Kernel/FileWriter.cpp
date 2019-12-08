#include "FileWriter.h"

TFileWriter::TFileWriter(const char* AFileNameAndPath)
{
	FFileNameAndPath = AFileNameAndPath;
	TheBFileWriter = NULL;
	OpenW(&TheBFileWriter);
//	TheFileWriter = new ofstream(AFileNameAndPath);
//	if (!TheFileWriter) printf("Le fichier %s n'a pas pu etre ouvert!",AFileNameAndPath);
}

TFileWriter::~TFileWriter()
{
	printf("TFileWriter destructor \n");
//	TheFileWriter->close();
//	delete TheFileWriter;
	if (TheBFileWriter!=NULL) delete TheBFileWriter;
}

void TFileWriter::OpenClose(void)
{
	OpenW(&TheBFileWriter);
}

void TFileWriter::OpenW(BFile **ABFile)
{
	if (*ABFile!=NULL) delete (*ABFile);
	(*ABFile) = new BFile;
//	(*ABFile)->SetTo(FFileNameAndPath.c_str(),B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE); 
	(*ABFile)->SetTo(FFileNameAndPath.c_str(),B_READ_WRITE | B_CREATE_FILE ); 
	FNbBytesWrite = 0;	
//	snooze(40000);
	(*ABFile)->Sync();
}


bool TFileWriter::WriteData (const char *ABuffer,uint32 nbWrite)
{
	bool resultat = false;
	if (TheBFileWriter)
	{
		FNbBytesWrite += TheBFileWriter->Write(ABuffer,nbWrite);
		FNbBytesWrite += TheBFileWriter->Write("\0",1);
		TheBFileWriter->Sync();
		resultat = true;
	}
	return resultat;
}

/*
void TFileWriter::WriteData(const char *Array, int nbElement)
{
	if (TheFileWriter)
	{
		const char *buf = Array;
		for (int ind=0;ind<nbElement;ind++)
		{
			TheFileWriter->put(*buf++);
		}
	}
}
*/
bool TFileWriter::WriteALine (string truc)
{
	return WriteData(truc.c_str(),strlen(truc.c_str()));				
}
