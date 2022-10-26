#include "UQuestSystem.h"
#include "QuestSystemPlugin.h"
#include "DataAssets/UQuestSettings.h"
#include "Kismet/GameplayStatics.h"

#pragma region BlueprintFunctions

bool UQuestSystem::StartQuest(const TSoftObjectPtr<UQuest> InQuest)
{
	UQuest* Quest = GetOrLoad(&InQuest);

	// TODO: Check if we are already doing a quest before this
	CurrentQuest = Quest;

	if (CurrentQuest->Steps.Max() == 0)
	{
		// TODO: Anyway that we can make this error in the blueprint?
		UE_LOG(LogQuestSystemModule, Error, TEXT("Quest %s (%s) has no steps"), *CurrentQuest->Name, *CurrentQuest->GetPathName());
		return false;
	}

	UE_LOG(LogQuestSystemModule, Log, TEXT("Starting Quest %s (%s)"), *CurrentQuest->Name, *CurrentQuest->GetPathName());
	
	const auto [QuestStepClass, QuestSettingClass] = CurrentQuest->Steps[0];
	
	const UClass* QuestStep = GetOrLoad(QuestStepClass);
	const UClass* QuestSetting = GetOrLoad(QuestSettingClass);

	// TODO: Check if TransientPackage is okay to put here? Or should we use a different package?
	UQuestStep* QuestStepObject = NewObject<UQuestStep>(GetTransientPackage(), QuestStep);
	const UQuestSettings* QuestSettingObject = NewObject<UQuestSettings>(GetTransientPackage(), QuestSetting);

	UE_LOG(LogQuestSystemModule, Log, TEXT("Calling OnQuestStepStart on %s (%s)"), *QuestStepObject->GetName(), *QuestStepObject->GetPathName());
	QuestStepObject->OnQuestStepStart(QuestSettingObject);
	
	return true;
}

bool UQuestSystem::StopQuest(const TSoftObjectPtr<UQuest> InQuest)
{
	const UQuest* Quest = GetOrLoad(&InQuest);
	
	UE_LOG(LogQuestSystemModule, Log, TEXT("STOP QUEST %s"), *Quest->Name);
	return true;
}

bool UQuestSystem::FinishQuest(const TSoftObjectPtr<UQuest> InQuest)
{
	const UQuest* Quest = GetOrLoad(&InQuest);
	
	UE_LOG(LogQuestSystemModule, Log, TEXT("FINISHED QUEST %s"), *Quest->Name);
	return true;
}
#pragma endregion
#pragma region Templated SoftPointer Helpers
template<typename T>
T* UQuestSystem::GetOrLoad(const TSoftObjectPtr<T>* InObject)
{
	if (InObject->IsValid())
	{
		return InObject->Get();
	}
	
	return InObject->LoadSynchronous();
}

template<typename T>
UClass* UQuestSystem::GetOrLoad(const TSoftClassPtr<T> InClass)
{
	if (InClass.IsValid())
	{
		return InClass.Get();
	}

	UClass* Class = InClass.LoadSynchronous();

	if (Class == nullptr)
	{
		UE_LOG(LogQuestSystemModule, Error, TEXT("Class %s is not valid"), *InClass.ToString());
	}
	
	return Class;
}
#pragma endregion