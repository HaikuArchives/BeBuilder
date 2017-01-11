//------------------------------------------
// Moebius Technologies inc.
// Copyright (C) 1998, All Rights Reserved.
//
// Created by Jerome Fillon 12-Sept-98
//------------------------------------------
#include "GeneralException.h"

/*GeneralException::GeneralException(char *AMessage,char *ALocation)
{
	Message = AMessage;
	Location = ALocation;
}
*/

GeneralException::GeneralException(const char *AMessage,const char *ALocation,bool ThrowNow)
{
	Message = AMessage;
	Location = ALocation;
	if (ThrowNow) { throw(this);}
}

GeneralException::~GeneralException(void) throw()
{
	;
}
