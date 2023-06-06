// CitroenGames 2023

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoggingSaveGame.generated.h"

UCLASS()
class ULoggingSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, Category = Basic)
        bool bLoggingEnabled;
};

