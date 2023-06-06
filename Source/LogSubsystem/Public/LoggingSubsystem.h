// CitroenGames 2023

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/Subsystem.h"
#include "LoggingSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class LOGSUBSYSTEM_API ULoggingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    UFUNCTION(BlueprintCallable, Category = "Logging")
        void SetLoggingEnabled(bool bEnabled);

    UFUNCTION(BlueprintCallable, Category = "Logging")
        bool IsLoggingEnabled() const;

    UFUNCTION(BlueprintCallable, Category = "Logging")
        void LogToFile(const FString& LogMessage);

private:
    FString LogFilePath;
};
