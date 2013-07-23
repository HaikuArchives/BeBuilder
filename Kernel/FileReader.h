#ifndef __FILEREADER_H__
#define __FILEREADER_H__

#include <stdio.h>
#include <string>
#include <fstream>
#include <File.h>

using namespace std;

class TFileReader  
{
public:
	TFileReader(const char* AFileNameAndPath);
	virtual ~TFileReader();
	bool ReadData (char **ABuffer,int nbRead);
	bool ReadDataAt (int32 location,char **ABuffer,int nbRead);
	bool ReadALine (string *truc);
	int32 GetToPosition(int32 APosition);
	BFile *TheBFileReader;

protected :
	void OpenR(BFile **ABFile);
	string FFileNameAndPath;
	ifstream * TheFileReader;
	off_t FFileSize;
	int32 FNbBytesRead;

};

#endif
