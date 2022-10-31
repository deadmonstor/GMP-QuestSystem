#include "UQuestSystem.h"
#include "QuestSystemPlugin.h"
#include "DataAssets/UQuestSettings.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR 
	#include "Misc/UObjectToken.h"
#endif

#pragma region BlueprintFunctions
bool UQuestSystem::StartQuest(UObject* SelfObject, UObject* WorldContextObject, const TSoftObjectPtr<UQuest> InQuest)
{
	UQuest* Quest = GetOrLoad(&InQuest);
	
	// TODO: Do we actually want to allow this?
	if (IsValidChecked(CurrentQuest) && CurrentQuest->IsA(UQuest::StaticClass()))
	{
#if WITH_EDITOR
		FMessageLog("PIE").Error()
			->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest")))
			->AddToken(FUObjectToken::Create(CurrentQuest))
			->AddToken(FTextToken::Create(FText::FromString("is already active")))
			->AddToken(FUObjectToken::Create(SelfObject->GetClass()));
#else
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Quest %s is already active"),
			*CurrentQuest->Name);
#endif
		
		return false;
	}
	
	CurrentQuest = DuplicateObject(Quest, WorldContextObject);
	
	if (CurrentQuest->Steps.Max() == 0)
	{

#if WITH_EDITOR
		FMessageLog("PIE").Error()
			->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest")))
			->AddToken(FUObjectToken::Create(Quest))
			->AddToken(FTextToken::Create(FText::FromString("has no steps")));
#else
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Quest %s (%s) has no steps"), *Quest->Name, *Quest->GetPathName());
#endif
		
		return false;
	}

#if WITH_EDITOR
	FMessageLog("PIE").Info()
		->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Starting Quest")))
		->AddToken(FUObjectToken::Create(Quest))
		->AddToken(FTextToken::Create(FText::FromString("object that started the quest")))
		->AddToken(FUObjectToken::Create(SelfObject->GetClass()));
#else
	UE_LOG(LogQuestSystemModule, Log, TEXT("QuestSystem: Starting Quest %s (%s)"), *CurrentQuest->Name, *CurrentQuest->GetPathName());
#endif
	
	const auto [QuestStepClass, QuestSettingClass] = CurrentQuest->Steps[0];
	
	const UClass* QuestStep = GetOrLoad(&QuestStepClass);
	const UClass* QuestSetting = GetOrLoad(&QuestSettingClass);

	UQuestStep* QuestStepObject = NewObject<UQuestStep>(WorldContextObject, QuestStep);
	const UQuestSettings* QuestSettingObject = NewObject<UQuestSettings>(WorldContextObject, QuestSetting);
	
	QuestStepObject->OnQuestStepStart(QuestSettingObject, Quest);
	CurrentQuest->CurrentStep = QuestStepObject;
	
	return true;
}

bool UQuestSystem::FinishQuestInternal(const UObject* SelfObject, const TSoftObjectPtr<UQuest>* InQuest, bool bCancelled)
{
	const UQuest* Quest = GetOrLoad(InQuest);
	
	// TODO: Do we actually want to allow this?
	if (!IsValid(CurrentQuest))
	{
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Quest %s (%s) is not the current running quest"),
		       *Quest->Name, *Quest->GetPathName());

#if WITH_EDITOR
		FMessageLog("PIE").Error()
		                  ->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest")))
		                  ->AddToken(FUObjectToken::Create(Quest))
		                  ->AddToken(FTextToken::Create(FText::FromString("is not the current running quest ")))
		                  ->AddToken(FUObjectToken::Create(SelfObject->GetClass()));
#else
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Quest %s (%s) is not the current running quest"),
			*Quest->Name, *Quest->GetPathName());
#endif
		
		return false;
	}

	// TODO: We need a better way of identifying this as it can be broken
	if (CurrentQuest->Name != Quest->Name)
	{
#if WITH_EDITOR
		FMessageLog("PIE").Error()
		                  ->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest")))
		                  ->AddToken(FUObjectToken::Create(Quest))
		                  ->AddToken(FTextToken::Create(FText::FromString("is not the current running quest ")))
		                  ->AddToken(FUObjectToken::Create(SelfObject->GetClass()));
#else
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Quest %s (%s) is not the current running quest %s (%s)"),
			*Quest->Name, *Quest->GetPathName(),
			*CurrentQuest->Name, *CurrentQuest->GetPathName());
#endif
		
		return false;
	}

#if WITH_EDITOR
	FMessageLog("PIE").Info()
	                  ->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest Stopped")))
	                  ->AddToken(FUObjectToken::Create(Quest));
#else
	UE_LOG(LogQuestSystemModule, Log, TEXT("QuestSystem: Quest Stopped %s"), *CurrentQuest->Name);
#endif
	
	if (CurrentQuest->CurrentStep != nullptr)
	{
		CurrentQuest->CurrentStep->OnQuestStepCompleted();
		CurrentQuest->CurrentStep->ConditionalBeginDestroy();
		CurrentQuest->CurrentStep = nullptr;
	}
	else
	{
#if WITH_EDITOR
		FMessageLog("PIE").Error()
						  ->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest did not have valid current step ")))
						  ->AddToken(FUObjectToken::Create(Quest));
#else
		UE_LOG(LogQuestSystemModule, Log, TEXT("QuestSystem: Quest did not have valid current step %s"), *CurrentQuest->Name);
#endif
	}

	CurrentQuest->ConditionalBeginDestroy();
	CurrentQuest = nullptr;
	return true;
}

bool UQuestSystem::StopQuest(UObject* SelfObject, const TSoftObjectPtr<UQuest> InQuest)
{
	return FinishQuestInternal(SelfObject, &InQuest, true);
}

bool UQuestSystem::FinishQuest(UObject* SelfObject, const TSoftObjectPtr<UQuest> InQuest)
{
	return FinishQuestInternal(SelfObject, &InQuest, false);
}

void UQuestSystem::CallEvent(const FString Name)
{
	// TODO: Look if we can make this work in begin play, seems stupid but we probably should be allowed
	check(CurrentQuest)
	check(CurrentQuest->CurrentStep)
	
	if (CurrentQuest != nullptr && CurrentQuest->CurrentStep != nullptr)
	{
		CurrentQuest->CurrentStep->fuckutest.Broadcast(Name);
	}
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
UClass* UQuestSystem::GetOrLoad(const TSoftClassPtr<T>* InClass)
{
	if (InClass->IsValid())
	{
		return InClass->Get();
	}

	UClass* Class = InClass->LoadSynchronous();

	if (Class == nullptr)
	{
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Class %s is not valid"), *InClass->ToString());
	}
	
	return Class;
}
#pragma endregion