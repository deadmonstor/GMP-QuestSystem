#pragma once
#include "QuestStep.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FQuestEvent, FString, Name);

class UQuestSettings;
class UQuest;
class UQuestComponent;

USTRUCT()
struct FEventHolder
{
	GENERATED_BODY();
	
	TArray<FQuestEvent> Events;
};

UCLASS(Blueprintable, BlueprintType)
class UQuestStep final : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="QuestStep")
	UQuestComponent* OwnerQuestComponent;

	UPROPERTY(BlueprintReadOnly, Category="QuestStep")
	UQuest* OwnerQuest;

	UPROPERTY()
	TMap<FString, FEventHolder> EventQuest;

	UPROPERTY(BlueprintReadOnly, Category="QuestStep")
	bool IsReady = false;
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "QuestStep")
	void OnQuestStepCompleted(bool bCancelled);

	UFUNCTION(BlueprintImplementableEvent, Category = "QuestStep")
	void OnQuestStepStart(const UQuestSettings* QuestStepData,
						  const UQuest* Quest,
	                      const UQuestComponent* QuestComponent);

	UFUNCTION(BlueprintCallable, Category="QuestStep")
	void CallEvent(FString Name) const;

	UFUNCTION(BlueprintCallable, Category="QuestStep")
	void BindEventToName(const FString Name, FQuestEvent EventRef);
	
	UFUNCTION(BlueprintCallable, Category="QuestStep")
	void RemoveEventFromName(const FString Name, FQuestEvent EventRef);
	
	UFUNCTION(BlueprintImplementableEvent, Category="QuestStep")
	FString GetDescription();

#if WITH_ENGINE
	virtual UWorld* GetWorld() const override { return GEngine->GetCurrentPlayWorld(); };
#endif
	
	void Init(UQuestComponent* QuestComponent);
};
