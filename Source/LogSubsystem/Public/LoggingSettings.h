// CitroenGames 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "LoggingSettings.generated.h"


UCLASS(config = Game, defaultconfig)
class LOGSUBSYSTEM_API ULoggingSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    ULoggingSettings();
    UPROPERTY(EditAnywhere, config, Category = "Logging")
        bool bEnableLoggingInPackagedBuilds;
};