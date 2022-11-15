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
	
	void CreateStepObject(const int ID);
	void QuestStepCompletedExec(bool bCancelled) const;
	bool FinishQuestInternal(const UObject* SelfObject, bool bCancelled);

public:
	UQuestComponent();
	
	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = (HidePin = "SelfObject", DefaultToSelf = "SelfObject"))
	bool StartQuest(UObject* SelfObject, const TSoftObjectPtr<UQuest> InQuest);

	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = (HidePin = "SelfObject", DefaultToSelf = "SelfObject"))
	bool CancelQuest(UObject* SelfObject);

	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = (HidePin = "SelfObject", DefaultToSelf = "SelfObject"))
	bool FinishQuest(UObject* SelfObject);

	UFUNCTION(BlueprintCallable, Category="QuestSystem", meta = ( HidePin = "SelfObject", DefaultToSelf = "SelfObject"))
	bool FinishStep(UObject* SelfObject);
	
	UFUNCTION(BlueprintCallable)
	FString GetCurrentQuestName() const;

	UFUNCTION(BlueprintCallable)
	FString GetCurrentQuestDescription() const;

	UFUNCTION(BlueprintCallable)
	UQuest* GetCurrentQuest() const { return CurrentQuest; }
};
