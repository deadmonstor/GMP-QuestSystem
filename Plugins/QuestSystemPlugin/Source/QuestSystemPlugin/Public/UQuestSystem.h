#pragma once
#include "CoreMinimal.h"
#include "DataAssets/Quest.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UQuestSystem.generated.h"

UCLASS(meta=(ScriptName="QuestSystem"))
class UQuestSystem final : public UBlueprintFunctionLibrary
{
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
	
	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			HidePin = "SelfObject",
			DefaultToSelf = "SelfObject",
			WorldContext = "WorldContextObject"
		)
	)
	static bool StopQuest(UObject* SelfObject, UObject* WorldContextObject, const TSoftObjectPtr<UQuest> InQuest);

	UFUNCTION(BlueprintCallable,
		Category="QuestSystem",
		meta =
		(
			WorldContext = "WorldContextObject"
		)
	)
	static bool FinishQuest(UObject* WorldContextObject, const TSoftObjectPtr<UQuest> InQuest);
	
private:
	#pragma region Templated SoftPointer Helpers
	template<typename T>
	static T* GetOrLoad(const TSoftObjectPtr<T>* InObject);

	template<typename T>
	static UClass* GetOrLoad(const TSoftClassPtr<T> InClass);
#pragma endregion
};
