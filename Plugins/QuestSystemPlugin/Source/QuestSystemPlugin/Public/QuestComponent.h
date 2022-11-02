// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DataAssets/QuestStep.h"
#include "QuestComponent.generated.h"

class UQuest;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUESTSYSTEMPLUGIN_API UQuestComponent final : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY()
	UQuest* CurrentQuest;

#pragma region Templated SoftPointer Helpers
	template <typename T>
	static T* GetOrLoad(const TSoftObjectPtr<T>* InObject);

	template <typename T>
	static UClass* GetOrLoad(const TSoftClassPtr<T>* InClass);
#pragma endregion

protected:
	void CreateStepObject(UObject* WorldContextObject, const int ID);
	void QuestStepCompletedExec(bool bCancelled);
	bool FinishQuestInternal(const UObject* SelfObject, bool bCancelled);

public:
	UQuestComponent();

	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = (HidePin = "SelfObject", DefaultToSelf = "SelfObject", WorldContext = "WorldContextObject"))
	bool StartQuest(UObject* SelfObject, UObject* WorldContextObject, const TSoftObjectPtr<UQuest> InQuest);

	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = (HidePin = "SelfObject", DefaultToSelf = "SelfObject"))
	bool CancelQuest(UObject* SelfObject);

	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = (HidePin = "SelfObject", DefaultToSelf = "SelfObject"))
	bool FinishQuest(UObject* SelfObject);

	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = ( HidePin = "SelfObject", DefaultToSelf = "SelfObject", WorldContext = "WorldContextObject"))
	bool FinishStep(UObject* SelfObject, UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable)
	FString GetName() const;
	
	UFUNCTION(BlueprintCallable)
	FString GetDescription() const;
};
