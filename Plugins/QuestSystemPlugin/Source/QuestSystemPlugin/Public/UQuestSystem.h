#pragma once
#include "CoreMinimal.h"
#include "DataAssets/Quest.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UQuestSystem.generated.h"

UCLASS(meta=(ScriptName="QuestSystem"))
class UQuestSystem final : public UBlueprintFunctionLibrary
{
	// TODO: We need to move this its randomly crashing for no reason
	// At the moment it is a pointer to mem that randomly gets reassigned during every PIE play
	// this means that when we get to a valid object in the array it crashes because it technically is a valid object
	// but it is not the object we are looking for and thus it crashes. Even doing checks on class crashes because of this
	// so we need to find a way to make this a valid object that is not a pointer to mem

	// This needs to be on a valid object in the world so we can have a valid pointer.
	inline static UQuest* CurrentQuest;

	GENERATED_BODY()
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
	static bool StartQuest(UObject* SelfObject, UObject* WorldContextObject, const TSoftObjectPtr<UQuest> InQuest);
	static bool FinishQuestInternal(const UObject* SelfObject, const TSoftObjectPtr<UQuest>* InQuest, bool bCancelled);

	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			HidePin = "SelfObject",
			DefaultToSelf = "SelfObject"
		)
	)
	static bool StopQuest(UObject* SelfObject, const TSoftObjectPtr<UQuest> InQuest);

	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			HidePin = "SelfObject",
			DefaultToSelf = "SelfObject"
		)
	)
	
	static bool FinishQuest(UObject* SelfObject, const TSoftObjectPtr<UQuest> InQuest);

	UFUNCTION(BlueprintCallable,
		Category="QuestSystem"
	)
	static void CallEvent(FString Name);

private:
	#pragma region Templated SoftPointer Helpers
	template<typename T>
	static T* GetOrLoad(const TSoftObjectPtr<T>* InObject);

	template<typename T>
	static UClass* GetOrLoad(const TSoftClassPtr<T>* InClass);
#pragma endregion
};
