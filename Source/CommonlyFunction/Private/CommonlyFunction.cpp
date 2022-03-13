// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommonlyFunction.h"

#define LOCTEXT_NAMESPACE "FCommonlyFunctionModule"

void FCommonlyFunctionModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
}

void FCommonlyFunctionModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCommonlyFunctionModule, CommonlyFunction)