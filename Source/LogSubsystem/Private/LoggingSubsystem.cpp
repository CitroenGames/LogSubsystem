// CitroenGames 2023

#include "LoggingSubsystem.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/App.h"

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
    if (!GConfig)
    {
        UE_LOG(LogTemp, Error, TEXT("GConfig is null!"));
        return;
    }

    GConfig->SetBool(TEXT("Logging"), TEXT("bLoggingEnabled"), bEnabled, GGameIni);
    GConfig->Flush(false, GGameIni);

    // Debug message
    UE_LOG(LogTemp, Warning, TEXT("Logging has been %s."), bEnabled ? TEXT("enabled") : TEXT("disabled"));
}

bool ULoggingSubsystem::IsLoggingEnabled() const
{
    bool bLoggingEnabled = false;
    GConfig->GetBool(TEXT("Logging"), TEXT("bLoggingEnabled"), bLoggingEnabled, GGameIni);

    // Debug message
    UE_LOG(LogTemp, Warning, TEXT("Checked if logging is enabled: %s."), bLoggingEnabled ? TEXT("Yes") : TEXT("No"));

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
