#pragma once

#include "CoreMinimal.h"
#include "FQuestStruct.h"
#include "UQuestStep.h"
#include "Quest.generated.h"

UCLASS(BlueprintType)
class UQuest final : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FQuestStruct> Steps;

	UPROPERTY()
	UQuestStep* CurrentStep;

	UPROPERTY()
	int CurrentStepID;
};
