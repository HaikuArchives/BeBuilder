//-------------------------------
// Electronic BizCardz Enr.
// Copyright (C) 1998, All Rights Reserved.
//
// Created by J. Fillon August 98.
//-------------------------------
#include <string>
#include <File.h>
#include <Path.h>
#include <Directory.h>
#include <List.h>
#include <Invoker.h>
#include <stdio.h>
#include <fs_attr.h>
#include <Roster.h>
#include <string.h>
#include <string>
#include <malloc.h>
#include "Global.h"
#include "GeneralException.h"
#include "GlobalVar.h"
using namespace std;
//#include "BConfigOption.h"

class TJerFile 
{
	public:
		char *ZIPPathName;

		TJerFile(BHandler *AHandler);
		~TJerFile(void);
		void GetAllFile(node_ref DirRef,entry_ref FileRef, BList *ListDir);
		void GetAllFile(const char *ADirName, BList *ListDir);	
		void GetDirectoryName(BDirectory *dir);		
		void GetDiffFile(const char *ASrcDir,const char *ADestDir,BList *Diff);
		int32 CRCFile(const char * AFileNameAndPath);
		int32 CRCFile(BFile *fichier);		
		void CopyStrucFile(const char *SrcDir, const char *DestDir, BList *Diff);
		void GetRelativePath(const char *BeginDir,const char *Path,char **TheRelativePath);	
		void GetRelativePathAndName(const char *BeginDir,const char *Path,char **TheRelativePathAndName);		
		void CreateCompletePath(const char *BeginDir, const char *RelativePath);
		void AddFileToZIP(const char *FileAndPathToAdd,const char *ZipFileAndPath);
		void CopyFile( const char *sourcepath, const char *destinationpath );


		int32 GoGetDiff(const char *ASrcDir,const char *ADestDir);
		int32 GoCopyStructFile(const char *sourcepath, const char *destinationpath, BList *AList);


		void CopyStrucFile(void);
		void GetDiffFile(void);

		
	private:
		bool CalculateCRC;
		bool CreateZIP;
		BInvoker MyInvoker;
		BList *TheListDir;
		char *SrcDir;
		char *DestDir;
		char *FBackupName;
		BList *ListFile;
	
		//------------
		thread_id my_thread; 		
		static int32 GetDiffMulti(void *arg); 
		static int32 CopyFileMulti(void *arg); 		
		
};


