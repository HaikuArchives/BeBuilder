#ifndef __BEBUILDER_OPTION_H__
#define __BEBUILDER_OPTION_H__

#include "BOption.h"
#include "Global.h"
#include <stdio.h>
#include <string>

class TBeBuilderOption : public BOption
{
	public:
		TBeBuilderOption(const char *filename);
		TBeBuilderOption(void);
		void ApplyUpdates(void); 	
		std::string FEditorMimeType;
		
};
#endif
