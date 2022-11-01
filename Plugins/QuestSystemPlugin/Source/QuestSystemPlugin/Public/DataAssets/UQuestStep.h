#pragma once
#include "QuestComponent.h"
#include "UQuestStep.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FEventTest, FString, Name );

class UQuestSettings;
class UQuest;
UCLASS(Blueprintable, BlueprintType)
class UQuestStep final : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly)
	bool IsReady = false;
	
	UPROPERTY(BlueprintReadOnly)
	UQuestComponent* OwnerQuestComponent;

	UPROPERTY()
	UQuest* OwnerQuest;
	
public:		
	UFUNCTION(BlueprintImplementableEvent,
		Category = "QuestStep"
	)
	void OnQuestStepCompleted();
	
	UFUNCTION(BlueprintImplementableEvent,
		Category = "QuestStep"
	)
	void OnQuestStepStart(const UQuestSettings* QuestStepData, const UQuest* Quest);
	
	UFUNCTION(BlueprintCallable,
		Category="QuestStep"
	)
	void CallEvent(FString Name);

	UPROPERTY(BlueprintAssignable,
		Category="QuestStep"
	)
	FEventTest EventTest;

	virtual UWorld* GetWorld() const override;
	void Init(UQuestComponent* QuestComponent, UQuest* Quest);
};
