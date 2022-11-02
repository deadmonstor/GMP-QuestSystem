#pragma once
#include "QuestStep.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEventTest, FString, Name);

class UQuestSettings;
class UQuest;
class UQuestComponent;

UCLASS(Blueprintable, BlueprintType)
class UQuestStep final : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	bool IsReady = false;

	UPROPERTY()
	UQuestComponent* OwnerQuestComponent;

	UPROPERTY()
	UQuest* OwnerQuest;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "QuestStep")
	void OnQuestStepCompleted(bool bCancelled);

	UFUNCTION(BlueprintImplementableEvent, Category = "QuestStep")
	void OnQuestStepStart(const UQuestSettings* QuestStepData, const UQuest* Quest,
	                      const UQuestComponent* QuestComponent);

	UFUNCTION(BlueprintCallable, Category="QuestStep")
	void CallEvent(FString Name);

	UPROPERTY(BlueprintAssignable, Category="QuestStep")
	FEventTest EventTest;

	UFUNCTION(BlueprintImplementableEvent, Category="QuestStep")
	FString GetDescription();

	virtual UWorld* GetWorld() const override;
	void Init(UQuestComponent* QuestComponent, UQuest* Quest);
};
