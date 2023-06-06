// CitroenGames 2023

#pragma once

#include "Subsystems/EngineSubsystem.h"
#include "LoggingSubsystem.generated.h"

UCLASS()
class ULoggingSubsystem : public UEngineSubsystem
{
    GENERATED_BODY()

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    void SetLoggingEnabled(bool bEnabled);
    bool IsLoggingEnabled() const;
    void LogToFile(const FString& LogMessage);

private:
    FString LogFilePath;
};
