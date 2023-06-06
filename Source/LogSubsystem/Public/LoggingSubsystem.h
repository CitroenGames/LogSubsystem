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
    ULoggingSubsystem();

    UFUNCTION(BlueprintCallable, Category = "Logging", meta = (Keywords = "write log"))
        void LogToFile(const FString& LogMessage);

private:
    FString StartupTime;
    FString LogFilePath;
};
