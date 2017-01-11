#ifndef __FILEWRITER_H__
#define __FILEWRITER_H__
#include <string>
#include <cstring>
//#include <fstream>
#include <File.h>
#include <stdio.h>
//#include <OS.h> //for the snooze function

using namespace std;


class TFileWriter  
{
	public:
		TFileWriter(const char * TheFileNameAndPath);
		virtual ~TFileWriter();
		bool WriteData (const char *ABuffer,uint32 nbWrite);
		bool WriteALine (string truc);
		void OpenClose(void);
		string FFileNameAndPath;
		BFile *TheBFileWriter;
	protected:
		void OpenW(BFile **ABFile);
		int32 FNbBytesWrite;
//		ofstream *TheFileWriter;
};

#endif
