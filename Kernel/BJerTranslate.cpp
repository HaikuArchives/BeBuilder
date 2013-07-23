#include "BJerTranslate.h"

//#include <string>

#define IMAGE_JPEG 0
#define IMAGE_GIF 1
#define IMAGE_TGA 2
#define IMAGE_BMP 3
#define IMAGE_AUTRE 4

string TTranslator::ShowInformation(void)
{
	string truc;
	truc = "Nom: " + FNom + " ID: ";
	//truc << FID;
}


BJerTranslate::BJerTranslate()
{
	MyRoster = new BTranslatorRoster;
	MyRoster->AddTranslators(NULL); //Default Translators...
	LoadTTranslator();
//	MyRoster->	
}

void BJerTranslate::LoadTTranslator(void)
{
	TTranslator *truc;
	int32 num_translators, i; 
	translator_id *translators; 
	const char *translator_name, *translator_info; 
	int32 translator_version; 
	CITranslator ptr;
	bool MUSTADD;
	MyRoster->GetAllTranslators(&translators, &num_translators); 
	for (i=0;i<num_translators;i++) 
	{ 
		MyRoster->GetTranslatorInfo(translators[i], &translator_name, &translator_info, &translator_version); 
		MUSTADD = false;
//		ptr = ListTranslator.find(translator_name);
/*
		if (ptr!=ListTranslator.end()) // found!
		{ 
			if (ptr->second->FVersion < translator_version)
			{
				erase(ptr);
				MUSTADD = true;
 			}
		}
		else
		{
			MUSTADD = true;
		}
		*/
		MUSTADD = true;
		if (MUSTADD) 
		{
			truc = new TTranslator;
			truc->FNom = translator_name;
//			truc->FType=0;
			truc->FVersion = translator_version;
//s			truc->FInfo = translator_info;
			truc->FID = translators[i];
			ListTranslator[truc->FNom] = truc;						
		}
	}
}
	

void BJerTranslate::AddTranslators(char *TranslatorPath)
{
	MyRoster->AddTranslators(TranslatorPath);	
}

int BJerTranslate::GetImageType(BFile *fichier)
{
	int resultat;

	const char *AttributeName = "BEOS:TYPE" ;
	attr_info truc;
	fichier->GetAttrInfo(AttributeName,&truc);
	char *buffer;
	buffer = (char *)malloc((truc.size+1)*sizeof(char));
	fichier->ReadAttr("BEOS:TYPE",0,0,buffer,truc.size); 
	resultat = IMAGE_AUTRE;
	if (strstr(buffer,"jpeg")!=NULL) 
	{
		resultat = IMAGE_JPEG;
	}
	if (strstr(buffer,"BMP")!=NULL) 
	{
		resultat = IMAGE_BMP;
	}
	if (strstr(buffer,"GIF")!=NULL) 
	{
		resultat = IMAGE_GIF;
	}
	free(buffer);
	return resultat;
}

BBitmap * BJerTranslate::LoadBitmap(entry_ref *ref)
{
	BFile *fichier;
	BBitmap *result = NULL;
	
	fichier = new BFile(ref,B_READ_ONLY);	
	
	result = LoadBitmap(fichier);		
	delete fichier;
	return result;	
}

BBitmap * BJerTranslate::LoadBitmap(char *FileNameAndPath)
{
	BFile *fichier;
	BBitmap *result = NULL;	
	fichier = new BFile(FileNameAndPath,B_READ_ONLY);	
	result = LoadBitmap(fichier);	
	delete fichier;
	return result;	
}

BBitmap * BJerTranslate::LoadBitmap(BFile *fichier)
{
//	BFile *fichier;
	int ImageType;
	BBitmapStream stream;
	BBitmap *result = NULL;
	
//	fichier = new BFile(FileNameAndPath,B_READ_ONLY);	
	
//	ImageType = GetImageType(FileNameAndPath);   
	ImageType = GetImageType(fichier);   

//	if ((MyRoster->Translate(fichier,NULL,NULL,&stream,B_TRANSLATOR_BITMAP)==B_OK) && (ImageType==IMAGE_AUTRE))
	if ((MyRoster->Translate(fichier,NULL,NULL,&stream,B_TRANSLATOR_BITMAP)==B_OK))
	{
				
		stream.DetachBitmap(&result);
	//	ShowMessage("DEtach done.");
	}			
	else
	{
		ShowMessage("No translator installed for this kind of file...");
	}
//	delete fichier;
	return result;	
}

void BJerTranslate::SaveBitmap(char *FileNameandPath, BBitmap *ABitmap, char * Format)
{
	
	BFile fichier(FileNameandPath,B_WRITE_ONLY|B_CREATE_FILE);
//	fichier = new BFile;	
	
	BBitmapStream stream(ABitmap);
	if ((MyRoster->Translate(&stream,NULL,NULL,&fichier,B_TRANSLATOR_BITMAP)==B_OK))
	{
		stream.DetachBitmap(&ABitmap);
	//	ShowMessage("DEtach done.");
	}			
	else
	{
		ShowMessage("No translator installed for this kind of file...");
	}
}



void BJerTranslate::ShowLoadedTranslators2(void)
{
  int32 num_translators, i; 
  translator_id *translators; 
  const char *translator_name, *translator_info; 
  int32 translator_version; 
//char * truc2;
  string truc("");
			   
  MyRoster->GetAllTranslators(&translators, &num_translators); 
  for (i=0;i<num_translators;i++) 
  { 
      MyRoster->GetTranslatorInfo(translators[i], &translator_name, &translator_info, &translator_version); 
   	  truc = truc + translator_name + " " + translator_info + "\n";
      const translation_format *fmts; 
      int32 num_fmts; 
      MyRoster->GetOutputFormats(translators[i], &fmts, &num_fmts); 
      for (int32 j=0;j<num_fmts;j++) 
      { 
      	truc = truc + "\t Format : \n\t\t Name: "+ fmts[j].name + " Mime: " + fmts[j].MIME +"\n";
//      	if (!strcasecmp(fmts[j].MIME, mime)) 
//               printf("match: %s type %8.8x (%4.4s)\\n", 
//                  fmts[j].name, fmts[j].type, &fmts[j].type); 
      } 


/*
   
      for (int32 i=0;i<num_translators;i++) { 
         const translation_format *fmts; 
         int32 num_fmts; 
   
         roster->GetOutputFormats(translators[i], &fmts, &num_fmts); 
   
         for (int32 j=0;j<num_fmts;j++) { 
            if (!strcasecmp(fmts[j].MIME, mime)) 
               printf("match: %s type %8.8x (%4.4s)\\n", 
                  fmts[j].name, fmts[j].type, &fmts[j].type); 
         } 
*/


//      printf("%s: %s (%.2f)\n", translator_name, translator_info, 
//         translator_version/100.); 
  } 
	ShowMessage(truc.data());   

  delete [] translators; // clean up our droppings

}

void BJerTranslate::ShowLoadedTranslators(void)
{
	string chaine;
	for (CITranslator truc=ListTranslator.begin(); truc!=ListTranslator.end(); ++truc)
	{
		chaine = chaine + (truc->second)->ShowInformation();			
	}
	ShowMessage(chaine.data());		
}


//status_t BJerTranslate::DoSaveAs( BBitmap *ABitmap, char *FileNameAndPath, BMessage * save_as) 
status_t BJerTranslate::DoSaveAs( BBitmap *ABitmap, entry_ref *ref, BMessage * save_as) 
{ 
	int32 translator; 
	uint32 type; 
	status_t err; 

	printf("Inside DoSAveAS...\n");
	
	BFile outputFile(ref,B_WRITE_ONLY|B_CREATE_FILE);
	printf("fichier %s devrait etre cree...\n",ref->name);
	
	err = save_as->FindInt32("be:translator", &translator); 
	if (err < B_OK) return err; 
	err = save_as->FindInt32("be:type", (int32 *)&type); 
	if (err < B_OK) return err; 
	
	BBitmapStream input(ABitmap); 
	err = MyRoster->Translate(translator, &input, NULL, &outputFile, type); 
	if (err == B_OK) err = SetFileType(&outputFile, translator, type); 
	return err; 
} 

status_t BJerTranslate::SetFileType(BFile * file, int32 translator, uint32 type) 
{ 
	translation_format * formats; 
	int32 count; 
	status_t err = MyRoster->GetOutputFormats(translator, &formats, &count); 
	if (err < B_OK) return err; 
	const char * mime = NULL; 
	for (int ix=0; ix<count; ix++) { 
	        if (formats[ix].type == type) { 
	                mime = formats[ix].MIME; 
	                break; 
	        } 
	} 
	if (mime == NULL) {     /* this should not happen, but being defensive might be prudent */ 
	        return B_ERROR; 
	} 
	/* use BNodeInfo to set the file type */ 
	BNodeInfo ninfo(file); 
	return ninfo.SetType(mime); 
}

