// CitroenGames 2023


#include "LoggingSubsystem.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/App.h"
#include "LoggingSettings.h"
#include "GameFramework/GameUserSettings.h"

void ULoggingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    // Get the user directory and project name
    FString UserDir = FPlatformProcess::UserDir();
    FString ProjectName = FApp::GetProjectName();

    // Generate the full log file path
    LogFilePath = UserDir / ProjectName / (ProjectName + FString::Printf(TEXT("%lld.log"), FDateTime::UtcNow().ToUnixTimestamp()));

    // Ensure the directory exists
    IFileManager::Get().MakeDirectory(*FPaths::GetPath(LogFilePath), true);
}

void ULoggingSubsystem::Deinitialize()
{
    // Clean up any resources here
}

void ULoggingSubsystem::SetLoggingEnabled(bool bEnabled)
{
    // Update the setting in the configuration file
    GConfig->SetBool(TEXT("Logging"), TEXT("bLoggingEnabled"), bEnabled, GGameIni);
    // Make sure to save the changes
    GConfig->Flush(false, GGameIni);
}

bool ULoggingSubsystem::IsLoggingEnabled() const
{
    bool bLoggingEnabled = false;
    // Retrieve the setting from the configuration file
    GConfig->GetBool(TEXT("Logging"), TEXT("bLoggingEnabled"), bLoggingEnabled, GGameIni);
    return bLoggingEnabled;
}

void ULoggingSubsystem::LogToFile(const FString& LogMessage)
{
    if (IsLoggingEnabled())
    {
        // Append the log message to the file
        FFileHelper::SaveStringToFile(LogMessage + LINE_TERMINATOR, *LogFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
    }
}

