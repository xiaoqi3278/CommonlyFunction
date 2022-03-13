// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Internationalization/Text.h"
#include "Containers/UnrealString.h"
#include "UObject/Class.h"
#include "Components/CheckBox.h"
#include "Components/Widget.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "VaRest/Public//VaRestRequestJSON.h"
#include "CommonlyFunctionBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/

class UObject;
class UCheckBox;
class UUserWidget;
class APlayerController;

USTRUCT(BlueprintType)
struct FDate
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Years;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Months;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Days;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Hours;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Minutes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Seconds;

	//UENUM(BlueprintType, Category = "CommonlyFunction|Date")
	//	EDayOfWeek Week;
};

UCLASS()
class UCommonlyFunctionBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Execute Sample function", Keywords = "CommonlyFunction sample test testing"), Category = "CommonlyFunctionTesting")
		static float CommonlyFunctionSampleFunction(float Param);

	//蓝图输出到日志
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "输出到日志"), meta = (Keywords = "CommonlyFunction|Test"), Category = "CommonyFunction|Test")
		static void OutLog(FString OutString);

	//设置单选框
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "设置单选框，IsChecked为真时始终为必选单选框"), meta = (Keywords = "CommonlyFunction|Widget"), Category = "CommonlyFunction|Widget")
		static void SetCheckBoxWithRadio(TArray<UCheckBox*> CheckBoxArr, UCheckBox* CheckedBox, bool IsChecked);

	//切换UI
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "切换当前视口显示的UI"), meta = (Keywords = "CommonlyFunction|Widget"), Category = "CommonlyFunction|Widget")
		static void ChangeWidget(TArray<UUserWidget*> WidgetArr, TSubclassOf<UUserWidget> CreateTargetWidget, APlayerController* PlayerController);

	//获取日期和时间
	UFUNCTION(BlueprintPure, meta = (ToolTip = "获取系统时间"), meta = (Keywords = "CommonlyFunction|Date"), Category = "CommonlyFuntion|Date")
		static FDate GetDate();

	//获取星期
	UFUNCTION(BlueprintPure, meta = (ToolTip = "获取系统星期"), meta = (Keywords = "CommonlyFunction|Date"), Category = "CommonlyFunction|Date")
		static FString GetDayOfWeek();

	//整数格式转换为 00 格式
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "整数格式化为“00”格式"), meta = (Keywords = "CommonlyFunction|Date"), Category = "CommonlyFunction|Date")
		static FString FormatToTime(int32 Time);

	//创建文件夹
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "创建文件夹，勾选 InProjectContent 后会在项目 Content 文件夹下创建"), meta = (Keywords = "CommonlyFunction|Directory"), Category = "CommonlyFunction|Directory")
		static void NewDirectory(FString DirectoryName, bool InProjectContent, FString AbsolutPath, bool& Successful, FString& DirectoryPath);

	//删除文件夹
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "删除文件夹，返回删除是否成功, 勾选DeleteALLFiles后会删除文件夹内所有文件，否则不做删除"), meta = (Keywords = "CommonlyFunction|Directory"), Category = "commonlyFunction|Directory")
		static bool DeleteDirectory(FString FilePath, bool DeleteAllFiles);

	//打开文件夹
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "打开文件夹"), meta = (Keywords = "CommonlyFunction|Directory"), Category = "CommonlyFunction|Directory")
		static void OpenFolder(FString Path);

	//创建文件
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "创建文件，勾选 InProjectContent 后在 ContentPath 下创建 (Test.txt), 如已有文件，则在文件末尾添加，返回是否成功"), meta = (Keywords = "CommonlyFunction|Directory"), Category = "CommonlyFunction|Directory")
		static void CreateNewFile(FString FileName, bool InProjectContent, bool AutoNewline, FString AbsolutePath, FString ContentString, bool& Successful, FString& FilePath);

	//读取文件
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "读取文件"), meta = (Keywords = "CommonlyFunction|Directory"), Category = "CommonlyFuntion|Directory")
		static FString ReadFile(FString FilePath);

	//删除文件
	UFUNCTION(BlueprintCallable, meta = (ToolTip = "删除文件，返回是否成功"), meta = (Keywords = "CommonlyFunction|Directory"), Category = "CommonlyFunction|Directory")
		static bool DeleteFile(FString FilePath);

};
