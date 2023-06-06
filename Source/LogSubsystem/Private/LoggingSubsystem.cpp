// CitroenGames 2023

#include "LoggingSubsystem.h"
#include "Misc/DateTime.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/FileHelper.h"
#include "Misc/App.h"

void ULoggingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    FString UserDir = FPlatformProcess::UserDir();
    FString ProjectName = FApp::GetProjectName();
    LogFilePath = UserDir / ProjectName / (ProjectName + FString::Printf(TEXT("%lld.log"), FDateTime::UtcNow().ToUnixTimestamp()));
    IFileManager::Get().MakeDirectory(*FPaths::GetPath(LogFilePath), true);
    ULoggingSaveGame* SaveGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LoggingSaveSlot"), 0));
    if (!SaveGameInstance)
    {
        SaveGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoggingSaveGame::StaticClass()));
        if (!SaveGameInstance)
        {
            UE_LOG(LogTemp, Error, TEXT("SaveGameInstance is null!"));
            return;
        }
        SaveGameInstance->bLoggingEnabled = false;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("LoggingSaveSlot"), 0);
    }

    UE_LOG(LogTemp, Warning, TEXT("IsLoggingEnabled: %s"), IsLoggingEnabled() ? TEXT("true") : TEXT("false"));
}

bool ULoggingSubsystem::IsLoggingEnabled()
{
    //get if logging is enabled from save game
    ULoggingSaveGame* SaveGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LoggingSaveSlot"), 0));
    if (!SaveGameInstance)
    {
        SaveGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoggingSaveGame::StaticClass()));
    }

    // print save game instance if bLoggingEnabled is enabled
    UE_LOG(LogTemp, Warning, TEXT("SaveGameInstance: %s"), SaveGameInstance->bLoggingEnabled ? TEXT("true") : TEXT("false"));
    return SaveGameInstance->bLoggingEnabled;
}

void ULoggingSubsystem::SetLoggingEnabled(bool bEnabled)
{
    ULoggingSaveGame* SaveGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("LoggingSaveSlot"), 0));
    if (!SaveGameInstance)
    {
        SaveGameInstance = Cast<ULoggingSaveGame>(UGameplayStatics::CreateSaveGameObject(ULoggingSaveGame::StaticClass()));
    }
    SaveGameInstance->bLoggingEnabled = bEnabled;

    UGameplayStatics::SaveGameToSlot(SaveGameInstance, TEXT("LoggingSaveSlot"), 0);
}

bool ULoggingSubsystem::LogToFile(const FString& LogMessage)
{
    if (IsLoggingEnabled() == true) // added an explicit comparison against true when calling IsLoggingEnabled to ensure strict boolean comparison
    {
        FFileHelper::SaveStringToFile(LogMessage + LINE_TERMINATOR, *LogFilePath, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), EFileWrite::FILEWRITE_Append);
        return true;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Logging is not enabled!"));
        return false;
    }
}
