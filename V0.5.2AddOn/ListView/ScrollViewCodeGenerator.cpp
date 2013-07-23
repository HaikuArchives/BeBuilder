#include "ScrollViewCodeGenerator.h"
#include "ScrollViewComponent.h"

TScrollViewCodeGenerator::TScrollViewCodeGenerator(TScrollViewComponent * AScrollViewComponent, bool CanCreateSourceFile):TCodeGenerator(CanCreateSourceFile)
{
	FScrollViewComponent = AScrollViewComponent;
}
/*
void TScrollViewCodeGenerator::GenerateAll(const char *APath,const char *ClassName,TFileRW *AParentFileRWHeader, TFileRW *AParentFileRWCPP)
{
	printf("TScrollViewCodeGenerator::GenerateAll Before Call to Genewration\n");
	FScrollViewComponent->FInternalComponent->FCodeGenerator->GenerateAll(APath,ClassName,AParentFileRWHeader,AParentFileRWCPP);
}
*/
void TScrollViewCodeGenerator::GenerateAll(const char *APath,const char *ClassName)
{
	printf("TScrollViewCodeGenerator::GenerateAll Before Call to Genewration\n");
	FScrollViewComponent->FInternalComponent->FCodeGenerator->GenerateAll(APath,ClassName);
}
bool TScrollViewCodeGenerator::CreateBody(bool ReallyWriteInFile = true)
{
	return FScrollViewComponent->FInternalComponent->FCodeGenerator->CreateBody(ReallyWriteInFile);
}
bool TScrollViewCodeGenerator::CreateHeader(bool ReallyWriteInFile = true)
{
	return FScrollViewComponent->FInternalComponent->FCodeGenerator->CreateHeader(ReallyWriteInFile);
}
bool TScrollViewCodeGenerator::CreateMakeFile(bool ReallyWriteInFile = true)
{
	return FScrollViewComponent->FInternalComponent->FCodeGenerator->CreateMakeFile(ReallyWriteInFile);
}
bool TScrollViewCodeGenerator::CreateConstructor(bool ReallyWriteInFile = true)
{
	return ((TListViewCodeGenerator *)(FScrollViewComponent->FInternalComponent->FCodeGenerator))->CreateConstructor(ReallyWriteInFile);
}
bool TScrollViewCodeGenerator::CreateMessageReceived(bool ReallyWriteInFile = true)
{
	//return FScrollViewComponent->FInternalComponent->FCodeGenerator->CreateMessageReceived(ReallyWriteInFile);
	return true;
}
bool TScrollViewCodeGenerator::PrepareCode(const char *APath, const char *AClassName, bool ReallyWriteInFile = true)
{
	return FScrollViewComponent->FInternalComponent->FCodeGenerator->PrepareCode(APath,AClassName,ReallyWriteInFile);
}
