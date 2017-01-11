#ifndef __PARSER_H__
#define __PARSER_H__
#include <string>
using namespace std;
#include <File.h>
#include "Object.h"
#include <cstdlib>

class TParser : public TObject
{
	public:
		TParser(void);
		~TParser(void);
		bool DeleteString(off_t location,string AStrToDelete,BFile *AFile);
		bool ReplaceString(off_t location, string AStrToFind,string AReplaceString,BFile *AFile);
		bool InsertString(off_t location, string AStr, BFile *AFile);
		off_t FindInFile(off_t FromLocation, string AStr, BFile *AFile);
		off_t FindNextLine(off_t FromLocation, BFile *AFile); //Return the off_set of the \n in the sequence \r\n that finishes a line and a file.
	protected:
		bool DecaleFile(off_t FromLocation, off_t ToLocation, BFile *AFile);

		
};
#endif 
