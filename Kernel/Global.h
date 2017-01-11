#ifndef __BEBACK_GLOBAL_
#define __BEBACK_GLOBAL_
#include <string>
#include <Rect.h>
#include <Point.h>
#include <Message.h>
extern void ShowMessage(const char *);
extern void ShowMessage(char *);
extern void ShowMessage(const char *,BRect);
extern void ShowMessage(const char *,BPoint);
extern void ShowMessage(const char *,long);
extern void ShowMessageHexa(const char *, long);
extern void ShowMessage(const char *, const char *);
extern void ShowMessage(std::string);
extern char *IntToStr(int);
extern char *IntToStr(long);
extern char *FloatToStr(float);
extern char *FloatToStr(double);
extern int StrToInt(const char *);
extern long StrToLong(const char *);
extern double StrToDouble(const char *);
extern int StrToInt(char *AStr);
extern long StrToLong(char *AStr);
extern double StrToDouble(char *AStr);
extern std::string StrCopy(std::string, int, int );
extern void PrintMessage(BMessage *AMessage,int tab);
extern bool IsFoundInside(std::string , const char *);
#endif
