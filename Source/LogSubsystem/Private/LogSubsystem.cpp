// Copyright Epic Games, Inc. All Rights Reserved.

#include "LogSubsystem.h"


#define LOCTEXT_NAMESPACE "FLogSubsystemModule"

void FLogSubsystemModule::StartupModule()
{
}

void FLogSubsystemModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
    // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLogSubsystemModule, LogSubsystem)
