#pragma once
#include "DataAssets/Quest.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UQuestSystem.generated.h"

UCLASS(meta=(ScriptName="QuestSystem"))
class UQuestSystem final : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category="QuestSystem")
	static bool StartQuest(FQuest Quest);
	
	UFUNCTION(BlueprintCallable, Category="QuestSystem")
	static bool StopQuest(FQuest Quest);

	UFUNCTION(BlueprintCallable, Category="QuestSystem")
	static bool FinishQuest(FQuest Quest);
};
