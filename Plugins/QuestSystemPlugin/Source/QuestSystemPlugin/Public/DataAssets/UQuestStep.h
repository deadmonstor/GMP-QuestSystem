#pragma once
#include "UQuestStep.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FFuckYou, FString, Name );

class UQuestSettings;
class UQuest;
UCLASS(Blueprintable, BlueprintType)
class UQuestStep final : public UObject
{
	GENERATED_BODY()

public:		
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestStepCompleted();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Quest")
	void OnQuestStepStart(const UQuestSettings* QuestStepData, const UQuest* Quest);

	// TODO: Make sure this is actually the best way of doing it
	virtual UWorld* GetWorld() const override
	{
		return GEngine->GetCurrentPlayWorld();
	}

	// BUG: TODO: FUCKU: REMIND NATHAN TO MATCAP 
	UPROPERTY(BlueprintAssignable, Category="Quest");
	FFuckYou fuckutest;
};
