// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UQuestSettings.generated.h"

struct FQuest;

UCLASS(BlueprintType)
class UQuestSettings final : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UQuestSettings()
	{
	}

	UPROPERTY(EditAnywhere, Category="Quests")
	TArray<FQuest> Quests;
};
