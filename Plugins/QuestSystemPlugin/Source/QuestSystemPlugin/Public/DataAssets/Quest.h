#pragma once

#include "CoreMinimal.h"
#include "QuestStep.h"
#include "QuestStruct.h"
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

	UPROPERTY(Transient)
	UQuestStep* CurrentStep;

	UPROPERTY(Transient)
	int CurrentStepID;
};
