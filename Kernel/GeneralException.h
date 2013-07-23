//------------------------------------------
// Moebius Technologies inc.
// Copyright (C) 1998, All Rights Reserved.
//
// Created by Jerome Fillon 12-Sept-98
//------------------------------------------
#ifndef __GENERAL_EXCEPTION_H__
#define __GENERAL_EXCEPTION_H__
#include <string>
class GeneralException : public exception
{
	public:
//		GeneralException(char *AMessage, char *ALocation);
		GeneralException(const char *AMessage,const char *ALocation,bool ThrowNow = false);
		~GeneralException(void);
		string	Message;
		string	Location;
};
#endif
