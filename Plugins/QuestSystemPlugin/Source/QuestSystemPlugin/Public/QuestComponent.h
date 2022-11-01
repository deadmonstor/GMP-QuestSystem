// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/UQuestStep.h"
#include "QuestComponent.generated.h"

class UQuest;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUESTSYSTEMPLUGIN_API UQuestComponent final : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UQuest* CurrentQuest;

public:
	UQuestComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			HidePin = "SelfObject",
			DefaultToSelf = "SelfObject",
			WorldContext = "WorldContextObject"
		)
	)
	bool StartQuest(UObject* SelfObject, UObject* WorldContextObject, const TSoftObjectPtr<UQuest> InQuest);
	bool FinishQuestInternal(const UObject* SelfObject, bool bCancelled);

	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			HidePin = "SelfObject",
			DefaultToSelf = "SelfObject"
		)
	)
	bool CancelQuest(UObject* SelfObject);

	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			HidePin = "SelfObject",
			DefaultToSelf = "SelfObject"
		)
	)
	bool FinishQuest(UObject* SelfObject);

	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			HidePin = "SelfObject",
			DefaultToSelf = "SelfObject"
		)
	)
	bool FinishStep(UObject* SelfObject, UQuestStep* Step);
	
private:
#pragma region Templated SoftPointer Helpers
	template<typename T>
	T* GetOrLoad(const TSoftObjectPtr<T>* InObject);

	template<typename T>
	UClass* GetOrLoad(const TSoftClassPtr<T>* InClass);
#pragma endregion
};
