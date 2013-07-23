#ifndef __CODE_GENERATOR_H__
#define __CODE_GENERATOR_H__
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include <Entry.h>
#include "FileRW.h"
#include "GlobalVar.h"
#include "Object.h"
#include "CodeFile.h"
#include "CodeLine.h"
#include "StringList.h"

class TCodeGenerator : public TObject
{
	public :
		TCodeGenerator(bool CanCreateSourceFile);
		virtual ~TCodeGenerator(void);
//		virtual TFileRW *GenerateH(const char * APath,const char *ClassName); // cette fonction est appelee pour lancer la generation elle sert que si le CanCreateSoruceFile est vrai! 
//		virtual TFileRW *GenerateCPP(const char * APath,const char *ClassName); // cette fonction est appelee pour lancer la generation elle sert que si le CanCreateSoruceFile est vrai! 
//		virtual void GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP) {};
		
		
		//Dynamic Generation Functions
		
/*		
		virtual void BeginH(TFileRW *AFileRW) ;
		virtual void FooterH(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!		
		virtual void ConstructorBeginH(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!
		virtual void ConstructorBodyH(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!
		virtual void ConstructorEndH(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!
		virtual void BeginCPP(TFileRW *AFileRW);
		virtual void FooterCPP(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!
		virtual void ConstructorBeginCPP(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!
		virtual void ConstructorBodyCPP(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!
		virtual void ConstructorEndCPP(TFileRW *AFileRW) {} ; // Cette est abstraite??? enfin c'est un work-around!
*/
//--------Application Main Program-------------//
//		virtual TFileRW *GenerateMainApp(char * APath,char *ClassName); // cette fonction est appelee pour lancer la generation elle sert que si le CanCreateSoruceFile est vrai! 
/*		virtual void BeginMainApp(TFileRW *AFileRW);
		virtual void BodyMainApp(TFileRW *AFileRW) {};
		virtual void EndMainApp(TFileRW *AFileRW);		
*/
//--------Application MakeFile ----------------//		
//		virtual TFileRW *GenerateMakeFile(const char * APath,const char *ClassName); // cette fonction est appelee pour lancer la generation elle sert que si le CanCreateSoruceFile est vrai! 
/*		virtual void BeginMakeFile(TFileRW *AFileRW);
		virtual void BodyMakeFile(TFileRW *AFileRW){};
		virtual void EndMakeFile(TFileRW *AFileRW);
*/		
//		bool AddInFunction(TFileRW *AFileRW,const char *AFunctionName, const char *ALocation,const char *AValue);
//		bool AddInFunctionPlus(TFileRW *AFileRW,const char *AFunctionName,const char *AnAfterLocation, const char *ABeforeLocation,const char *AValue);
//---------NEW VERSION ----------------------//
//		virtual bool SkeletonCPP(TFileRW *AFileRW){return true;};
//		virtual bool SkeletonH(TFileRW *AFileRW){return true;};
//		virtual bool SkeletonMakeFile(TFileRW *AFileRW){return true;};
//		virtual bool InsertionMakeFile(TFileRW *AFileRW,const char *AFileName);		
//		virtual bool InsertionContructor(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP){return true;};
//		virtual bool InsertionMessageReceived(TFileRW *AFileRWHeader, TFileRW *AFileRWCPP){return true;};
//---------------------Dynamic Code Generation ---------------------
		virtual bool CreateBody(bool ReallyWriteInFile = true) {return true;};
		virtual bool CreateHeader(bool ReallyWriteInFile = true) {return true;};
		virtual bool CreateMakeFile(bool ReallyWriteInFile = true) {return true;};
		virtual bool PrepareCode(const char *APath, const char *AClassName,bool ReallyWriteInFile = true) ;
		virtual void GenerateAll(const char *APath,const char *ClassName);
		virtual BMessage *SaveData(void);
		virtual bool LoadData(BMessage *AMessage, BHandler *AGuiHandler);
		virtual bool AddCodeLine(TCodeLine *ACodeLine);

//-------------------------------------------------------------------		
//	private :
//	protected :
		bool FCanCreateSourceFile;
		TFileRW *FHeaderRW;
		TFileRW *FCPPRW;		
		TFileRW *FAppRW;
		TFileRW *FMakeRW;
		TCodeFile *FHeaderCodeFile;
		TCodeFile *FBodyCodeFile;
		TCodeFile *FMakeFileCodeFile;		
		void Copyrights(TFileRW *AFileRW);		
		void CopyrightsForMakeFile(TFileRW *AFileRW);
	protected :
		string FPathToGenerate;
		string FClassNameToGenerate;
		bool FHasBeenGenerated;
		TStringList *FCodeLineList;	
};

#endif