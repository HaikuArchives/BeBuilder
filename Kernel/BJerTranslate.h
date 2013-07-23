//---------------------------------------
// File Created By J. Fillon in August 98
// Purpose : Wrap the Translator Kit.
//---------------------------------------
#ifndef _BJerTranslateH_
#define _BJerTranslateH_
#include <TranslatorRoster.h>
#include <TranslationDefs.h>
#include <Bitmap.h>
#include <fs_attr.h>
#include <Node.h>
#include <NodeInfo.h>
#include <File.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <BitmapStream.h>
#include <string>
#include <map>
#include "Global.h"
#include <TranslationDefs.h>
/*
 : 
   struct translation_format { 
      uint32 type; 
      uint32 group; 
      float  quality; 
      float  capability; 
      char   MIME[251]; 
      char   name[251]; 
   } 
   
   struct translator_info { 
      uint32        type; 
      translator_id translator; 
      uint32        group; 
      float         quality; 
      float         capability; 
      char          name[251]; 
      char          MIME[251]; 
   }
*/

class TTranslator
{
	public :
		string FNom;
		translator_id FID;
		uint32 FType;
		int32 FVersion;
		struct translator_info FInfo;			 
	//	struct translation_format FFormat;
		string ShowInformation(void);
};

typedef map<string,TTranslator *> TStringTranslator;
typedef map<string,TTranslator *>::const_iterator CITranslator;
class BJerTranslate 
{
	public:
		BTranslatorRoster *MyRoster;
		BJerTranslate();
		void AddTranslators(char *TranslatorPath);
//		int GetImageType(char *FileNameAndPath);
		int GetImageType(BFile *fichier);
		BBitmap *LoadBitmap(entry_ref *ref);
		BBitmap *LoadBitmap(char *FileNameAndPath);
		BBitmap *LoadBitmap(BFile *fichier);
		void SaveBitmap(char *FileNameandPath, BBitmap *ABitmap, char * Format);
		void ShowLoadedTranslators(void);
		void ShowLoadedTranslators2(void);
//		status_t DoSaveAs( BBitmap *ABitmap, char *FileNameAndPath, BMessage * save_as); 
		status_t DoSaveAs( BBitmap *ABitmap, entry_ref *ref, BMessage * save_as); 
		
	private:
		TStringTranslator ListTranslator;
		void LoadTTranslator(void);
		status_t SetFileType(BFile * file, int32 translator, uint32 type); 
		
};
#endif
