//------------------------------------------
// Moebius Technologies inc.
// Copyright (C) 1998, All Rights Reserved.
//
// Created by Jerome Fillon 12-Sept-98
//------------------------------------------
#ifndef __GENERAL_WINDOW_OPTION_H__
#define __GENERAL_WINDOW_OPTION_H__

#include "BOption.h"
#include "Global.h"
#include <stdio.h>
#include <string>

class BGeneralWindowOption : public BOption
{
	public:
		BGeneralWindowOption(const char *filename,const char *WindowName);
		~BGeneralWindowOption(void);
		void ApplyUpdates(void); 	
		float Top;
		float Bottom;
		float Left;
		float Right;
		string TheWindowName;
};
#endif