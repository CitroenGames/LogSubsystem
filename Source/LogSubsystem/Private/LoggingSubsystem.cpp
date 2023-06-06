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
    ULoggingSaveGame* SaveGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoggingSaveGame::StaticClass()));
    if (!SaveGameInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("SaveGameInstance is null!"));
        return;
    }

    SaveGameInstance->bLoggingEnabled = bEnabled;

    // Now the bool value is saved in the SaveGameInstance, you need to write it to disk
    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("LoggingSaveSlot"), 0);
}

bool ULoggingSubsystem::IsLoggingEnabled() const
{
    ULoggingSaveGame* LoadGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoggingSaveGame::StaticClass()));
    if (!LoadGameInstance)
    {
        UE_LOG(LogTemp, Error, TEXT("LoadGameInstance is null!"));
        return false;
    }

    // Load the saved game from the specified slot
    LoadGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LoggingSaveSlot"), 0));

    // If the slot doesn't exist or failed to load, default to logging being disabled
    if (!LoadGameInstance)
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to load game from slot!"));
        return false;
    }

    return LoadGameInstance->bLoggingEnabled;
}

void ULoggingSubsystem::LogToFile(const FString& LogMessage)
{
    if (!IsLoggingEnabled())
    {
        return;
    }

    // Log the message to the file
    FFileHelper::SaveStringToFile(LogMessage + LINE_TERMINATOR, *LogFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
}
