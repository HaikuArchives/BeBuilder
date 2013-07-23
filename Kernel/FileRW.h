#ifndef __FILERW_H__
#define __FILERW_H__

#include <stdio.h>
#include <string>
#include <string.h>
#include <File.h>
#include "FileReader.h"
#include "FileWriter.h"
using namespace std;

class TFileRW  : public TFileWriter, public TFileReader 
{
public:
	TFileRW(const char* AFileNameAndPath);
	virtual ~TFileRW();
//	bool ReadData (char **ABuffer,uint32 nbRead);

//	void WriteData (const char *ABuffer,uint32 nbRead);
//	bool ReadALine (string *truc);
//	bool WriteALine (string truc);
	bool InsertALine (string truc);	
//	bool InsertALine2 (string truc);	
	int GetPositionReader(void);
	int GetPositionWriter(void);
	const char *GetFileName(void);
	int32 ResetReader(void);
	
//	int32 FNbBytesRead;
//	BFile *TheBFileRW;	
private:
	void OpenRW(BFile **ABFile);	
//	void OpenR(BFile **ABFile);	
//	string FFileNameAndPath;
//	off_t FFileSize;
//	int32 FNbBytesWrite;
};
#endif