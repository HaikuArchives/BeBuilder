#ifndef __BOPTION_H__
#define __BOPTION_H__

#include <Path.h>
#include <File.h>
#include <Resources.h>
#include <FindDirectory.h>
#include "GeneralException.h"
class BOption : public BMessage
{
	public:
		BOption(const char *filename);
		~BOption(void);
		void ApplyUpdates(void); 	
		void SetBool(const char *name, bool ABool);
		void GetBool(const char *name, bool *ABool);
		
		void SetString(const char *name, char *AStr);
		void GetString(const char *name, char **AStr);

		void SetFloat(const char *name, float AFloat);
		void GetFloat(const char *name, float *AFloat);
		
		
//		status_t SetBool(const char *name, bool b);
//		status_t SetBool(const char *name, bool b);
	 
		
	private:
		BFile file;
		BPath path;
		int status;
};
#endif