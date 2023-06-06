// CitroenGames 2023

#pragma once

#include "CoreMinimal.h"
#include "LoggingSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "LoggingSubsystem.generated.h"

UCLASS()
class ULoggingSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable)
    void SetLoggingEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable)
    bool IsLoggingEnabled() const;
    
    UFUNCTION(BlueprintCallable)
    void LogToFile(const FString& LogMessage);

private:
    FString LogFilePath;
};
