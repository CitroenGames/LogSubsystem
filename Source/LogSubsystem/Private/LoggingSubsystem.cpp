// CitroenGames 2023


#include "LoggingSubsystem.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/App.h"
#include "LoggingSettings.h"

ULoggingSubsystem::ULoggingSubsystem()
{
    // Get the current Unix timestamp at startup and store it
    FDateTime Now = FDateTime::UtcNow();
    StartupTime = FString::Printf(TEXT("%lld"), Now.ToUnixTimestamp());

    // Get the platform user directory and project name
    FString UserDir = FPlatformProcess::UserDir();
    FString ProjectName = FApp::GetProjectName();

    // Build the full path to the log file
    LogFilePath = FPaths::Combine(UserDir, ProjectName, ProjectName + StartupTime + ".txt");
    
    // Check if the file already exists
    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    if (!PlatformFile.FileExists(*LogFilePath))
    {
        // If the file doesn't exist, create it
        FFileHelper::SaveStringToFile(FString(""), *LogFilePath);
    }
}

void ULoggingSubsystem::LogToFile(const FString& LogMessage)
{
    // Get a pointer to the settings object
    const ULoggingSettings* Settings = GetDefault<ULoggingSettings>();

    // Check if we should log in a packaged build
    if (Settings->bEnableLoggingInPackagedBuilds || GIsEditor)
    {
        // Append the log message to the file
        FFileHelper::SaveStringToFile(LogMessage + LINE_TERMINATOR, *LogFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
    }
}


