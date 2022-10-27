#pragma once

#include "UQuestStep.generated.h"

class UQuestSettings;
class UQuest;
UCLASS(Blueprintable, BlueprintType)
class UQuestStep final : public UObject
{
	GENERATED_BODY()

public:

	// TODO: Do we need Completed here? maybe for rewards?
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestStepCompleted();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestStepStart(const UQuestSettings* QuestStepData, const UQuest* Quest);
};
