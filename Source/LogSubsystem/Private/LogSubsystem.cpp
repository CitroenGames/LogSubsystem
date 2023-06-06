// Copyright Epic Games, Inc. All Rights Reserved.

#include "LogSubsystem.h"
#include "Modules/ModuleManager.h"
#include "Engine.h"

#define LOCTEXT_NAMESPACE "FLogSubsystemModule"

void FLogSubsystemModule::StartupModule()
{
    // This function will be called after your module is loaded into memory.
    // Subscribe to the delegate that is called when the engine has been initialized.
    FCoreDelegates::OnPostEngineInit.AddLambda([this]()
    {
        // Initialize your custom subsystem here (optional)
        UEngineSubsystem* LoggingSubsystem = GEngine->GetEngineSubsystem<ULoggingSubsystem>();
        if (LoggingSubsystem)
        {
            UE_LOG(LogTemp, Log, TEXT("Logging subsystem initialized!"));
        }
    });
}

void FLogSubsystemModule::ShutdownModule()
{
    // This function may be called during shutdown to clean up your module. For modules that support dynamic reloading,
    // we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLogSubsystemModule, LogSubsystem)
