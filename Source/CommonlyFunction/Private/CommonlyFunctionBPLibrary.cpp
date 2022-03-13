// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonlyFunctionBPLibrary.h"
#include "CommonlyFunction.h"
#include "Blueprint/UserWidget.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "HAL/FileManager.h"
#include "Internationalization/Text.h"
#include "HAL/FileManager.h"
#include "HAL/FileManagerGeneric.h"
#include "Engine/World.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#include "Misc/DateTime.h"

UCommonlyFunctionBPLibrary::UCommonlyFunctionBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float UCommonlyFunctionBPLibrary::CommonlyFunctionSampleFunction(float Param)
{
	return -1;
}

void UCommonlyFunctionBPLibrary::OutLog(FString OutString)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *OutString);
}

//设置单选框
void UCommonlyFunctionBPLibrary::SetCheckBoxWithRadio(TArray<UCheckBox*> CheckBoxArr, UCheckBox* CheckedBox, bool IsChecked)
{
	for (int32 i = 0; i < CheckBoxArr.Num(); ++i)
	{
		CheckBoxArr[i]->SetCheckedState(ECheckBoxState::Unchecked);
	}

	if (IsChecked && CheckedBox != NULL)
	{
		CheckedBox->SetCheckedState(ECheckBoxState::Checked);
	}
}

//切换UI
void UCommonlyFunctionBPLibrary::ChangeWidget(TArray<UUserWidget*> WidgetArr, TSubclassOf<UUserWidget> CreateTargetWidget, APlayerController* PlayerController)
{
	for (int32 i = 0; i < WidgetArr.Num(); ++i)
	{
		WidgetArr[i]->RemoveFromParent();
	}

	if (CreateTargetWidget)
	{
		UUserWidget* ChoiceWidget = CreateWidget<UUserWidget>(PlayerController, CreateTargetWidget);
		if (ChoiceWidget)
		{
			ChoiceWidget->AddToViewport();
		}
	}
}

//获取日期和时间
FDate UCommonlyFunctionBPLibrary::GetDate()
{
	FDateTime Now = FDateTime::Now();

	int32 Years = Now.GetYear();
	int32 Months = Now.GetMonth();
	int32 Days = Now.GetDay();
	int32 Hours = Now.GetHour();
	int32 Minutes = Now.GetMinute();
	int32 Seconds = Now.GetSecond();

	FDate NowTime;

	//NowTime.Years = FText::FromString(FString::FromInt(Years));
	NowTime.Years = FString::FromInt(Years);
	NowTime.Months = FormatToTime(Months);
	NowTime.Days = FormatToTime(Days);
	NowTime.Hours = FormatToTime(Hours);
	NowTime.Minutes = FormatToTime(Minutes);
	NowTime.Seconds = FormatToTime(Seconds);
	//NowTime.Week = FDateTime::GetDayOfWeek();

	return NowTime;
}


FString UCommonlyFunctionBPLibrary::GetDayOfWeek()
{
	FDateTime DateTime = FDateTime::Now();
	EDayOfWeek DayOfWeek = DateTime.GetDayOfWeek();

	switch (DayOfWeek)
	{
		case EDayOfWeek::Monday		:	 return FString(TEXT("星期一"));
		case EDayOfWeek::Tuesday	:	 return FString(TEXT("星期二"));
		case EDayOfWeek::Wednesday	:	 return FString(TEXT("星期三"));
		case EDayOfWeek::Thursday	:	 return FString(TEXT("星期四"));
		case EDayOfWeek::Friday		:	 return FString(TEXT("星期五"));
		case EDayOfWeek::Saturday	:	 return FString(TEXT("星期六"));
		case EDayOfWeek::Sunday		:	 return FString(TEXT("星期七"));

		default						:	 return FString(TEXT("读取错误"));
	}
}

//整数格式转换为 00 格式
FString UCommonlyFunctionBPLibrary::FormatToTime(int32 Time)
{
	if (Time >= 10)
	{
		//return FText::FromString(FString::FromInt(Time));
		return FString::FromInt(Time);
	}

	FString TempString = FString(TEXT("0")).Append(FString::FromInt(Time));
	//return FText::FromString(TempString);
	return TempString;
}

//创建文件夹
void UCommonlyFunctionBPLibrary::NewDirectory(FString DirectoryName, bool InProjectContent, FString AbsolutePath, bool& Successful, FString& DirectoryPath)
{
	FString CompleteContentPath;

	if (InProjectContent)
	{
		IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
		CompleteContentPath = FPaths::ProjectContentDir().Append(DirectoryName);
		bool Result = PlatformFile.CreateDirectory(*CompleteContentPath);

		if (Result)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create A NewDirectory In ProjectContentPath Successfully! Path:%s"), *CompleteContentPath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to Create A NewDirectory In ProjectContentPath! Path:%s"), *CompleteContentPath);
		}

		Successful = Result;
		DirectoryPath = CompleteContentPath;
	}
	else
	{
		IPlatformFile& PlatFormFile = FPlatformFileManager::Get().GetPlatformFile();
		CompleteContentPath = AbsolutePath.Append(DirectoryName);
		bool Result = PlatFormFile.CreateDirectory(*CompleteContentPath);

		if (Result)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create A NewDirectory In AbsolutePath Successfully! Path:%s"), *CompleteContentPath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed To Create A NewDirectory In AbsolutePath! Path:%s"), *CompleteContentPath);
		}

		Successful = Result;
		DirectoryPath = CompleteContentPath;
	}
}

//删除文件夹
bool UCommonlyFunctionBPLibrary::DeleteDirectory(FString FilePath, bool DeleteAllFiles)
{

	if (FilePath.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To DeleteDirectory,FilePath Is Empty!"));
		return false;
	}

	IPlatformFile& PlatFormFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (DeleteAllFiles)
	{
		TArray<FString> FilePathArray;
		FilePathArray.Empty();
		FFileManagerGeneric::Get().FindFilesRecursive(FilePathArray, *FilePath, *FString("*"), true, true);
		for (int32 i = 0; i < FilePathArray.Num(); ++i)
		{
			DeleteFile(FilePathArray[i]);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *FilePathArray[i]);
		}
	}
	if (PlatFormFile.DeleteDirectory(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Delete Directory Successfully! Path:%s"), *FilePath);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Delete Directory! Path:%s"), *FilePath);
		return false;
	}
}

//打开文件夹
void UCommonlyFunctionBPLibrary::OpenFolder(FString Path)
{
	if (Path.IsEmpty())
	{
		return;
	}
	//IFileManager::Get().DirectoryExists(*Path);
	FPlatformProcess::ExploreFolder(*Path);
}

//创建文件
void UCommonlyFunctionBPLibrary::CreateNewFile(FString FileName, bool InProjectContent, bool AutoNewline,  FString AbsolutePath, FString ContentString, bool& Successful, FString& FilePath)
{
	FString CompleteFilePath;

	if (InProjectContent)
	{
		CompleteFilePath = FPaths::ProjectContentDir().Append(FileName);
		IFileManager& FileManager = IFileManager::Get();
		bool Result = FFileHelper::SaveStringToFile(AutoNewline ? ContentString.Append("\r\n") : ContentString, *CompleteFilePath, FFileHelper::EEncodingOptions::ForceUTF8, &FileManager, EFileWrite::FILEWRITE_Append);

		if (Result)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create A New File In ContentPath Successfully! Path:%s"), *CompleteFilePath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed To Create A New File In ContentPath! Path:%s"), *CompleteFilePath);
		}

		Successful = Result;
		FilePath = CompleteFilePath;
	}
	else
	{
		IFileManager& FileManager = IFileManager::Get();
		CompleteFilePath = AbsolutePath.Append("\\" + FileName);
		bool Result = FFileHelper::SaveStringToFile(AutoNewline ? ContentString.Append("\r\n") : ContentString, *CompleteFilePath, FFileHelper::EEncodingOptions::ForceUTF8WithoutBOM, &FileManager, EFileWrite::FILEWRITE_Append);

		if (Result)
		{
			UE_LOG(LogTemp, Warning, TEXT("Create A New File In AbsolutePath Successfully! Path:%s"), *CompleteFilePath);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed To Create A New File In AbsolutePath! Path:%s"), *CompleteFilePath);
		}

		Successful = Result;
		FilePath = CompleteFilePath;
	}
}

//读取文件
FString UCommonlyFunctionBPLibrary::ReadFile(FString FilePath)
{
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.FileExists(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Load File Succcessfully! Path:%s"), *FilePath);
		FString TempString;
		FFileHelper::LoadFileToString(TempString, *FilePath);
		return TempString;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("File Not Found! Path:%s"), *FilePath);
		FString TempString = FString(TEXT("File Not Found!"));
		return TempString;
	}
}

//删除文件
bool UCommonlyFunctionBPLibrary::DeleteFile(FString FilePath)
{
	if (FilePath.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Delete File,FilePath Is Empty!"));
		return false;
	}

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.DeleteFile(*FilePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Delete File Successfully! Path:%s"), *FilePath);
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed To Delete File! Path:%s"), *FilePath);
		return false;
	}
}


