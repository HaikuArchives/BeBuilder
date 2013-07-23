#include "JerFiles.h"

int32 TJerFile::CRCFile(BFile *fichier)
{
/*int32 CRCTbl[256] =
  { 0x00000000, 0x77073096, 0xee0e612c, 0x990951ba,
    0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
    0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,
    0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
    0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
    0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940,
    0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
   	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116,
    0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
    0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a,
    0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818,
    0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
    0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
    0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c,
    0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
    0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
    0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
    0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086,
    0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4,
    0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
    0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
    0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
    0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe,
    0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
    0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
    0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252,
    0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60,

    0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
    0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
    0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04,
    0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a,
    0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
    0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
    0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e,
    0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
    0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
    0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
    0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0,
    0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6,
    0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
    0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
    };
*/
//int32 BJerFile::CRCFile(BFile *fichier)
//{
	char buffer[1024];
	ssize_t amt_read;	
	int32 CRCNbr = -1;	
//---------------------
	return CRCNbr;
//----------------------
	for (;;)
	{
		amt_read = fichier->Read(buffer, 1024); 
		if ( amt_read < 0 )
		{
			string truc("Error in reading File.");
			GeneralException excep(truc.c_str(),"BJerFile::CRCFile");
			throw(excep);
		}
		else 
		{
			if (amt_read==0) break; //Normal exit...
			for (int ind=0;ind<amt_read;ind++)
			{
//				CRCNbr = CRCTbl[int8(CRCNbr xor int32(buffer[ind]))] xor ((CRCNbr >> 8) and 0x00FFFFFF);
//				ShowMessage("CRCNbr: ",CRCNbr);
			}
		}		
	}
	return CRCNbr;
}


TJerFile::TJerFile(BHandler *AHandler)
{
	MyInvoker.SetTarget(AHandler);
	TheListDir = new BList;
/*
	BConfigOption *truc;
	truc = new BConfigOption(PREFS_PATH,CONFIG_PREFS);
	CalculateCRC = truc->CalculateCRC;
	CreateZIP = truc->CreateZIP;
	ZIPPathName = (char *) malloc(sizeof(char) * (strlen(truc->ZIPExePath)+1));
	strcpy(ZIPPathName,truc->ZIPExePath);
	FBackupName = (char *) malloc(sizeof(char) * (strlen(truc->BackupName)+1));	
	strcpy(FBackupName,truc->BackupName);
*/
}

TJerFile::~TJerFile(void)
{
	void *anItem; 
	for ( int32 i = 0; (anItem = TheListDir->ItemAt(i)); i++ ) 
	{
		delete anItem; 
	}
	delete TheListDir;
}

void TJerFile::GetAllFile(node_ref DirRef,entry_ref FileRef, BList *ListDir)
{
	BDirectory dir(&DirRef);
	char buf[4096]; 
   	dirent *dent; 
	node_ref nref;    
	entry_ref ref,*ToBeAdded;
	int32 count;
	bool enter=false;
	while ((count = dir.GetNextDirents((dirent *)buf, 4096)) > 0) 
	{ 
	//	ShowMessage("Inside the While");
		dent = (dirent *)buf;       
		while (count-- > 0) 
		{ 
			enter = true; 	
			nref.device = dent->d_dev; 
			nref.node = dent->d_ino; 
			ref.device = dent->d_pdev; 
			ref.directory = dent->d_pino; 
			ref.set_name(dent->d_name);  		    	
			if ((strcmp(dent->d_name,".")!=0) && (strcmp(dent->d_name,"..")!=0))
			{
				GetAllFile(nref,ref,ListDir);	
			} 	
			dent = (dirent *)((char *)dent + dent->d_reclen); 
		} 
	}	
	if (enter==false)
	{
		ToBeAdded = new entry_ref;
		*ToBeAdded = FileRef;
		ListDir->AddItem(ToBeAdded);		
	}
}		

void TJerFile::GetAllFile(const char *ADirName, BList *ListDir)
{
/*
	BPath path(ADirName,NULL, true);
	ShowMessage("Path...",path.Path());
	if (path.SetTo(ADirName,NULL, true)==B_BAD_VALUE)
	{
		ShowMessage("Directory doesn'texist...");		
	}

	if (path.Path()==NULL)
	{
		ShowMessage("Directory doesn'texist...");
		CreateCompletePath("/",ADirName);		
	}
*/
	// dumb but as soon as the BPath will be bugged for the normalization...
	CreateCompletePath("/",ADirName);	
	BDirectory dir(ADirName);
	node_ref nref;
	entry_ref voidref;

	dir.GetNodeRef(&nref);
//	ShowMessage("Before GeTaLL file with nref");	
	GetAllFile(nref,voidref,ListDir);
}	

void TJerFile::GetDirectoryName(BDirectory *dir)
{
	BEntry entry;
	char name[B_FILE_NAME_LENGTH];
	dir->GetEntry(&entry);
	entry.GetName(name);
}


void TJerFile::GetDiffFile(const char *ASrcDir,const char *ADestDir,BList *Diff)
{
	//-----------------------------------------
	//	We are looking for files not found in Dest...
	//-----------------------------------------
	BList ASrcList;
	BList ADestList;
	char name1[B_FILE_NAME_LENGTH];
	char name2[B_FILE_NAME_LENGTH];
	off_t Size1;
	off_t Size2;
	int32 CRC1,CRC2;
	BPath P1;
	BPath P2;
	char *RelativePath1;
	char *RelativePath2;
	bool EntryFound = false;
	entry_ref *buf_entry,*buf_entry2,*copy_entry;
	BMessage *AMessage;
	BFile *file2;
	BFile *file1;	
	GetAllFile(ASrcDir,&ASrcList);
	GetAllFile(ADestDir,&ADestList);

	AMessage = new BMessage(B_RESET_STATUS_BAR);
	AMessage->AddFloat("maximum",ASrcList.CountItems());
	MyInvoker.Invoke(AMessage);		
	delete AMessage;				

	for (int ind=0;ind < ASrcList.CountItems();ind++ )
	{	
		buf_entry = (entry_ref *)(ASrcList.ItemAt(ind));
		if (buf_entry!=NULL)
		{
			BEntry E1(buf_entry);
			E1.GetName(name1);
			E1.GetPath(&P1);

			GetRelativePath(ASrcDir,P1.Path(),&RelativePath1);
			file1 = new BFile(buf_entry,B_READ_ONLY);
//			printf("Checking file ....%s \n",P1.Path());			
			// The Message is put here to update when the link files are found too.
			AMessage = new BMessage(B_UPDATE_STATUS_BAR);
			AMessage->AddFloat("delta",1.0);
			AMessage->AddString("text","Checking...");				
			AMessage->AddString("trailingtext",P1.Path());				
			MyInvoker.Invoke(AMessage);		
			delete AMessage;							

			if (file1->InitCheck()==B_NO_ERROR) //Because of linkfiles....
			{
				try
				{
					file1->GetSize(&Size1);			
					if (CalculateCRC==true) 
					{
						printf("CRC Calculation First File...\n");									
						CRC1 = CRCFile(file1);
					}
	//				printf("Checking file ....%s Size: %d CRC: %d \n",P1.Path(),Size1,CRC1);
					EntryFound = false;
				}
				catch(GeneralException &e)
				{
					delete file1;
					printf("Exception in File1...");
					throw;
				}
				delete file1;
				
				
				for (int ind2=0;ind2 < ADestList.CountItems();ind2++ )
				{
					buf_entry2 = (entry_ref *)(ADestList.ItemAt(ind2));
					if (buf_entry2!=NULL)
					{
						BEntry E2(buf_entry2);
						E2.GetName(name2);
						E2.GetPath(&P2);
						GetRelativePath(ADestDir,P2.Path(),&RelativePath2);					
						if ((strcmp(name1,name2)==0) && (strcmp(RelativePath1,RelativePath2)==0))
						{
	//						printf("name1 : %s, name2 : %s \n",name1,name2);
	//						printf("RP1 : %s, RP2 : %s \n",RelativePath1,RelativePath2);
	//						printf("PAth1 : %s, Path2 : %s \n",P1.Path(),P2.Path());
							file2 = new BFile(buf_entry2,B_READ_ONLY);
							file2->GetSize(&Size2);
	//						printf("Size2 %d\n",Size2);
							if (Size1==Size2)
							{						
							//CRC Test
								try
								{
									if (CalculateCRC==true) 
									{
										printf("CRC Calculation Second File...\n");									
										CRC2 = CRCFile(file2);
										if (CRC1==CRC2)	
										{
											EntryFound = true;
											delete file2;
											break; //Data found...								
										}
									}
								}
								catch(GeneralException &e)
								{
									printf("Error in GetDiffFile %s\n",P2.Path());
									throw;							
								}
							}
							delete file2;				
						}
					}				
				}	
				if (EntryFound==false)
				{
					copy_entry = new entry_ref;
					*copy_entry = *buf_entry;
					Diff->AddItem(copy_entry);
			
/*					BMessage AMessage(GET_FILES);
					AMessage.AddRef("ref",copy_entry);
					int result = MyInvoker.Invoke(&AMessage);		
					if (result!= B_OK)
					{
						if (result == B_BAD_PORT_ID)
						{
							ShowMessage("Bad Port");
						}
						else
						if (result == B_TIMED_OUT)
						{
							ShowMessage("TIMED_OUT");
						}
						else
							ShowMessage("Other Error");
					}
*/					
				}
			} // End of InitCheck
		}		
	}	
	// Just to let the main loop that we have finished checking... for the moment we only
	// use it to test if the OutLineList is void....
/*
	BMessage AMessage2(END_CHECKING);
	int result2 = MyInvoker.Invoke(&AMessage2);		
	if (result2!= B_OK)
	{
		if (result2 == B_BAD_PORT_ID)
		{
			ShowMessage("Bad Port");
		}
		else
			if (result2 == B_TIMED_OUT)
			{
				ShowMessage("TIMED_OUT");
			}
			else
				ShowMessage("Other Error");	
	}
*/	
}

void TJerFile::GetRelativePath(const char *BeginDir,const char *Path,char **TheRelativePath)
{
	BPath BeginPath(BeginDir);
	BPath PathPath(Path);
	string Begin(BeginPath.Path());
	string Chemin(PathPath.Path());
	string RelativePathBuffer("");
	string RelativePath("");
	int indSav;
	for (uint32 ind=Begin.length();ind<Chemin.length();ind++)
	{
		RelativePathBuffer = RelativePathBuffer + Chemin[ind];
	}
	for (int ind=RelativePathBuffer.length()-1;ind>=0;ind--)
	{
		if (RelativePathBuffer[ind]=='/')
		{
			indSav = ind;
			break;
		}
	}
	for (int ind=0;ind<indSav;ind++)
	{
		RelativePath = RelativePath + RelativePathBuffer[ind];
	}
	*TheRelativePath = (char *)malloc(sizeof(char)*(RelativePath.length()+1));
	strcpy(*TheRelativePath,RelativePath.c_str());
}

void TJerFile::GetRelativePathAndName(const char *BeginDir,const char *Path,char **TheRelativePathAndName)
{
	BPath BeginPath(BeginDir);
	BPath PathPath(Path);
	string Begin(BeginPath.Path());
	string Chemin(PathPath.Path());
	string RelativePathBuffer("");
	string RelativePath("");
	for (uint32 ind=Begin.length();ind<Chemin.length();ind++)
	{
		RelativePathBuffer = RelativePathBuffer + Chemin[ind];
	}
	*TheRelativePathAndName = (char *)malloc(sizeof(char)*(RelativePathBuffer.length()+1));
	strcpy(*TheRelativePathAndName,RelativePathBuffer.c_str());
}


void TJerFile::CreateCompletePath(const char *BeginDir, const char *RelativePath)
{
	BPath path(BeginDir);
	BDirectory dir(BeginDir);
	string Relative(RelativePath);
	string PathToCreate(path.Path());
	int indstart = 0;
	if (Relative.length()!=0)
	{	
		if (Relative[0]=='/')
		{
			indstart = 1;
		}
		PathToCreate = PathToCreate + "/";
		for (uint32 ind=indstart;ind<Relative.length();ind++)
		{
			if (Relative[ind]=='/')
			{
				dir.CreateDirectory(PathToCreate.c_str(),&dir);		
				PathToCreate = PathToCreate + "/";
			}
			else
			{
				PathToCreate = PathToCreate + Relative[ind];
			}
		}
		if (PathToCreate.length()>0)
		{
			dir.CreateDirectory(PathToCreate.c_str(),&dir);		
		}
	} //If Length == 0
//	int errcode = dir.CreateDirectory(DirComplete.c_str(),&dir);
/*
	if (errcode!=B_OK)
	{
		string truc2(strerror(errcode));	
		printf("Code : %d Err : %s \n",errcode,truc2.c_str());
//		GeneralException excep(truc2.c_str(),"BJerFile::CreateCompletePath");
//		throw(excep);
	}		
*/	
}

void TJerFile::CopyStrucFile(const char *SrcDir, const char *DestDir, BList *Diff)
{
	entry_ref *truc;
	BEntry *entry;
	BPath chemin;
	BPath Destination;
	char *Relative;
	char *TheRelativePathAndName;
/*
printf("------------------------------------\n");	
printf("ZIPPathName : %s \n",ZIPPathName);
printf("SrcDir : %s \n",SrcDir);
printf("DestDir : %s \n",DestDir);
printf("------------------------------------\n");	
*/
	BMessage *AMessage;
	AMessage = new BMessage(B_RESET_STATUS_BAR);
	AMessage->AddFloat("maximum",Diff->CountItems());
	MyInvoker.Invoke(AMessage);		
	delete AMessage;				
	try
	{
	for (int ind=0;ind < Diff->CountItems();ind++ )
	{
		truc = (entry_ref *)(Diff->ItemAt(ind));
		if (truc!=NULL)
		{
			entry = new BEntry(truc);
			entry->GetPath(&chemin);		
			if (CreateZIP == true)
			{
//				printf("Zipping............\n");
				char *titi;
				titi = (char *)malloc(sizeof(char)*(strlen(DestDir) + strlen(FBackupName) +2 )); //count the \0 and the / for the directory!
				strcpy(titi,DestDir);
				strcat(titi,"/");
				strcat(titi,FBackupName);
//				string titi(DestDir);
/*
printf("------------------------------------\n");	
printf("ZIPPathName : %s \n",ZIPPathName);
printf("chemin : %s \n",chemin.Path());
printf("titi : %s \n",titi.c_str());
printf("SrcDir : %s \n",SrcDir);
printf("DestDir : %s \n",DestDir);
printf("------------------------------------\n");	
*/
//				titi = titi + "/BeBackup.zip";

//				AddFileToZIP(chemin.Path(),titi.c_str());
				AddFileToZIP(chemin.Path(),titi);
				
			}
			else
			{
				GetRelativePath(SrcDir,chemin.Path(),&Relative);
				CreateCompletePath(DestDir,Relative);	
				GetRelativePathAndName(SrcDir,chemin.Path(),&TheRelativePathAndName);
				Destination.SetTo(DestDir);			
				string toto(Destination.Path());
				toto = toto + TheRelativePathAndName;
				CopyFile(chemin.Path(),toto.c_str());
			}
			delete entry;
		}							
		else
			printf("Items is null...\n");
	}	
	} //Try
	catch(GeneralException &e)
	{
		printf("Exception while copying... %s %s",e.Message.c_str(),e.Location.c_str());
	}
}

int32 TJerFile::CRCFile(const char * AFileNameAndPath)
{
	BFile *fichier;
	int32 CRCNbr = -1;
	fichier = new BFile(AFileNameAndPath,B_READ_ONLY);
	CRCNbr = CRCFile(fichier);
	delete fichier;	
	return CRCNbr;
}
/*
int32 BJerFile::CRCFile(BFile *fichier)
{
	char buffer[1024];
	ssize_t amt_read;	
	int32 CRCNbr = -1;	
	for (;;)
	{
		amt_read = fichier->Read(buffer, 1024); 
		if ( amt_read < 0 )
		{
			string truc("Error in reading File.");
			GeneralException excep(truc.c_str(),"BJerFile::CRCFile");
			throw(excep);
		}
		else 
		{
			if (amt_read==0) break; //Normal exit...
			for (int ind=0;ind<amt_read;ind++)
			{
//				CRCNbr = CRCTbl[int8(CRCNbr xor int32(buffer[ind]))] xor ((CRCNbr >> 8) and 0x00FFFFFF);							
				CRCNbr = CRCTbl[int8(CRCNbr xor int32(buffer[ind]))];							
			}
		}		
	}
	return CRCNbr;
}
*/

void TJerFile::AddFileToZIP(const char *FileAndPathToAdd,const char *ZipFileAndPath)
{
	BEntry Entry(ZIPPathName);
	entry_ref Myentry;
	Entry.GetRef(&Myentry);
//	string toto;
//	char** argv;
//	char** buf;
//	argv = (char**)malloc(sizeof(char *)*2);
//	buf = argv;
//	char *Param="/Data/tmp/BizCardz.zip";
//	char *Param="-h";
//	toto = ZipFileAndPath + ' ';
//	toto = toto + FileAndPathToAdd;
//	char *titi;
//	titi = (char *)malloc(sizeof(char)*(strlen(toto.c_str())+1));
//	strcpy(titi,toto.c_str());
	
//	titi = (char *)malloc(sizeof(char)*(strlen(ZipFileAndPath)+2 +strlen(FileAndPathToAdd)));
//	strcpy(titi,ZipFileAndPath);
//	strcat(titi," ");
//	strcat(titi,FileAndPathToAdd);
	team_id team;
//	bool resultat;	
	status_t resultat;	
	
	char *argv[2];
	argv[0] = (char *)malloc(strlen(ZipFileAndPath)+1);
	strcpy(argv[0],ZipFileAndPath);
	argv[1] = (char *)malloc(strlen(FileAndPathToAdd)+1);
	strcpy(argv[1],FileAndPathToAdd);

/*	string truc,truc2;
	truc = ZipFileAndPath;
	*argv[0] = truc.c_str();
	truc2 = FileAndPathToAdd;
	*argv[1] = truc2.c_str();
*/	
//	strcpy(*argv[1],truc2.c_str());
//    *argv[0] = ZipFileAndPath;
//	*argv[1] = FileAndPathToAdd;
/*
    argv[0] = ZipFileAndPath;
	argv[1] = FileAndPathToAdd;
*/
//	char *argv[2]={"/Data/tmp/BizCardz.zip","/Data/tmp/BizCardz"};
	resultat = be_roster->Launch(&Myentry,2,&argv[0],&team);
	
//	resultat = be_roster->Launch(&Myentry,1,&titi,&team);
//	*argv++ = FileAndPathToAdd;
//	*argv = ZipFileAndPath;
//	argv = buf;
//	resultat = be_roster->Launch(&Myentry,2,argv,&team);
/*
printf("------------------------------------\n");	
printf("ZIPPathName : %s \n",ZIPPathName);
  printf("zipfileandpath : %s \n",ZipFileAndPath);
  printf("FileAndPathToAdd : %s \n",FileAndPathToAdd);
printf("------------------------------------\n");	
*/
	if (resultat==B_OK)
	{
//	    printf("zipfileandpath : %s \n",ZipFileAndPath);
//		printf("FileAndPathToAdd : %s \n",FileAndPathToAdd);
//		printf("Launched OK\n");
	}
	else
	if (resultat == B_BAD_VALUE)
	{
//		printf("BAD_VALUE \n");		
		GeneralException excep("Launch returned B_BAD_VALUE","BJerFile::AddFileToZIP");
		throw(excep);        	
	}
	else
	if (resultat == B_ALREADY_RUNNING)
	{
//		printf("ALREADY_RUNNING \n");		
		GeneralException excep("Launch returned ALREADY_RUNNING","BJerFile::AddFileToZIP");
		throw(excep);        	
	}
	else
	if (resultat == B_LAUNCH_FAILED)
	{
//		printf("LAUNCH_FAILED \n");		
		GeneralException excep("Launch returned LAUNCH_FAILED","BJerFile::AddFileToZIP");
		throw(excep);        	
	}
	else
	{
//		printf("Others Errors...\n");		
		GeneralException excep("Launch returned Others Errors","BJerFile::AddFileToZIP");
		throw(excep);        	
	}
}

//---------------------------------------------------------------
// Copy File, not only data but also attributes ;-)
//---------------------------------------------------------------
void TJerFile::CopyFile( const char *sourcepath, const char *destinationpath )
{
    BFile *source = 0L, *destination = 0L;
   	entry_ref ref;
    uint8 data[2048];
    int32 len = 2048;
   	char buf[B_ATTR_NAME_LENGTH]; 
   	void *buffer = NULL;
   	int32 lengthR,lengthW;
   	attr_info attribute;
    
    BEntry entry( sourcepath );
    if( B_OK == entry.InitCheck() )
    {
        if( B_OK == entry.GetRef( &ref ) )
        {
            source = new BFile( &ref ,B_READ_ONLY);
        }
        else
        {
			string truc("Error opening file in read only mode: ");
			truc = truc + sourcepath;
			GeneralException excep(truc.c_str(),"BJerFile::CopyFile");
			throw(excep);        	
        }
    }
    else
    {
		string truc("Error constructing file object: ");
		truc = truc + sourcepath;
		GeneralException excep(truc.c_str(),"BJerFile::CopyFile");
		throw(excep);        	    	
    }

    entry.SetTo( destinationpath );
    if( B_OK == entry.InitCheck() )
    {
        if( B_OK == entry.GetRef( &ref ) )
        {
            destination = new BFile( &ref ,B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE);
        }
        else
        {
			string truc("Error opening file in read write mode: ");
			truc = truc + destinationpath;
			GeneralException excep(truc.c_str(),"BJerFile::CopyFile");
			throw(excep);        	
        }        
    }
    else
    {
		string truc("Error destination constructing file object: ");
		truc = truc + destinationpath;
		GeneralException excep(truc.c_str(),"BJerFile::CopyFile");
		throw(excep);        	    	
    }
    
    
    if( source && destination )
    {    
		BMessage *AMessage;
		AMessage = new BMessage(B_UPDATE_STATUS_BAR);
		AMessage->AddFloat("delta",1.0);
		AMessage->AddString("text","Copy...");				
		AMessage->AddString("trailingtext",destinationpath);				
		MyInvoker.Invoke(AMessage);		
		delete AMessage;				
    
   		while (source->GetNextAttrName(buf) == B_NO_ERROR) 
   		{ 
			source->GetAttrInfo(buf,&attribute);     		 
			if (buffer!=NULL)
			{
				free(buffer);
			}
			buffer = (void *)malloc(sizeof(char)*(attribute.size +1));
			lengthR = source->ReadAttr(buf,attribute.type,0,buffer,attribute.size);					
			lengthW = destination->WriteAttr(buf,attribute.type,0,buffer,lengthR);						

			if (lengthR!=lengthW)
			{
				string truc("Error copying attribute for file : ");
				truc = truc + destinationpath;
				GeneralException excep(truc.c_str(),"BJerFile::CopyFile");
				throw(excep);        	    	
			}
			switch(lengthR)
			{
				case B_ENTRY_NOT_FOUND:
					{
					GeneralException excep("The attribute doesn't exist.","BJerFile::CopyFile");
					throw(excep);        	    	
					break;
					}
				case B_FILE_ERROR :
					{
					GeneralException excep2("The object is uninitialized.","BJerFile::CopyFile");
					throw(excep2);        	    	
					break; 
					}
			}			
			switch(lengthW)
			{
	
				case B_FILE_ERROR :
					{
					GeneralException excep3("This object is a read-only BFile.","BJerFile::CopyFile");
					throw(excep3);        	    	
					break;
					}
				case B_NOT_ALLOWED :
					{
					GeneralException excep4("The node is on a read-only volume.","BJerFile::CopyFile");
					throw(excep4);        	    	
					break; 
					}
				case B_DEVICE_FULL :
					{
					GeneralException excep5("Out of disk space.","BJerFile::CopyFile");
					throw(excep5);        	    	
					break; 
					}
				case B_NO_MEMORY :
					{
					GeneralException excep6("Not enough memory.","BJerFile::CopyFile");
					throw(excep6);        	    	
					break;			
					}
			}						
   		}
   		
        for( ;; )
        {
            len = source->Read( data, len );
            if( len == 0 )
            	break;
            destination->Write( data, len );
			if( len != 2048 )
		    	break;
        }
        //---------- freeing some resources...
        delete source;
	    delete destination;
    }
}
//---------------------------------------
// Multi Threading Function
//---------------------------------------


void TJerFile::CopyStrucFile(void)
{
	CopyStrucFile(SrcDir,DestDir,ListFile);
}


void TJerFile::GetDiffFile(void)
{
	GetDiffFile(SrcDir,DestDir,ListFile);
}

int32 TJerFile::GetDiffMulti(void *arg)
{
	TJerFile *obj = (TJerFile *)arg; 
	obj->GetDiffFile(); 
	return 1;
} 

int32 TJerFile::CopyFileMulti(void *arg)
{
	TJerFile *obj = (TJerFile *)arg; 
//	obj->GetDiffFile(SrcDir.c_str(),DestDir.c_str(),&ListFile); 
	obj->CopyStrucFile(); 
	return 1;
} 		

int32 TJerFile::GoGetDiff(const char *ASrcDir,const char *ADestDir)
{
	SrcDir = (char *)malloc(sizeof(char)*(strlen(ASrcDir) + 1));
	strcpy(SrcDir,ASrcDir);

	DestDir = (char *)malloc(sizeof(char)*(strlen(ADestDir) + 1));
	strcpy(DestDir,ADestDir);

	ListFile = new BList();
	ListFile->MakeEmpty();		
    my_thread = spawn_thread(GetDiffMulti,"GetDiff",B_NORMAL_PRIORITY, this); 
    return (resume_thread(my_thread)); 
}

int32 TJerFile::GoCopyStructFile(const char *sourcepath, const char *destinationpath, BList *AList)
{
	SrcDir = (char *)malloc(sizeof(char)*(strlen(sourcepath) + 1));
	strcpy(SrcDir,sourcepath);
	ListFile = new BList();
	ListFile->MakeEmpty();		
	ListFile->AddList(AList);
	DestDir = (char *)malloc(sizeof(char)*(strlen(destinationpath) + 1));
	strcpy(DestDir,destinationpath);

    my_thread = spawn_thread(CopyFileMulti,"CopyStruct",B_NORMAL_PRIORITY, this); 
    return (resume_thread(my_thread)); 
}

