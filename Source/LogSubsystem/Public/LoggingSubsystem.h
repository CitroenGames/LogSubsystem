// CitroenGames 2023

#pragma once

#include "CoreMinimal.h"
#include "LoggingSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "LoggingSubsystem.generated.h"

UCLASS()
class ULoggingSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable, Category = "Logging Subsystem")
    void SetLoggingEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Logging Subsystem")
    bool IsLoggingEnabled();
    
    UFUNCTION(BlueprintCallable, Category = "Logging Subsystem")
    bool LogToFile(const FString& LogMessage);

private:
    FString LogFilePath;
};
