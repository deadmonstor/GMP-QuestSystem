#pragma once
#include "QuestStep.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FQuestEvent, FString, Name);

class UQuestSettings;
class UQuest;
class UQuestComponent;

USTRUCT()
struct FTestasdasdasda
{
	GENERATED_BODY();
	
	TArray<FQuestEvent> test;
};

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

	UPROPERTY()
	TMap<FString, FTestasdasdasda> EventQuest;

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

	UFUNCTION(BlueprintImplementableEvent, Category="QuestStep")
	FString GetDescription();

#if WITH_ENGINE
	virtual UWorld* GetWorld() const override;
#endif
	
	void Init(UQuestComponent* QuestComponent);
};
