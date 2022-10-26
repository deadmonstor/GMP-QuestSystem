#pragma once
#include "CoreMinimal.h"
#include "DataAssets/Quest.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UQuestSystem.generated.h"

UCLASS(meta=(ScriptName="QuestSystem"))
class UQuestSystem final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	inline static UQuest* CurrentQuest = nullptr;
	
public:
	UFUNCTION(BlueprintCallable, Category="QuestSystem")
	static bool StartQuest(const TSoftObjectPtr<UQuest> InQuest);
	
	UFUNCTION(BlueprintCallable, Category="QuestSystem")
	static bool StopQuest(const TSoftObjectPtr<UQuest> InQuest);

	UFUNCTION(BlueprintCallable, Category="QuestSystem")
	static bool FinishQuest(const TSoftObjectPtr<UQuest> InQuest);
	
private:
	#pragma region Templated SoftPointer Helpers
	template<typename T>
	static T* GetOrLoad(const TSoftObjectPtr<T>* InObject);

	template<typename T>
	static UClass* GetOrLoad(const TSoftClassPtr<T> InClass);
#pragma endregion
};
