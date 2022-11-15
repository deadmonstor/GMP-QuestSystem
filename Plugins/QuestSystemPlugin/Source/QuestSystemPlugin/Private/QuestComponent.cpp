#include "QuestComponent.h"
#include "QuestSystemPlugin.h"
#include "DataAssets/Quest.h"
#include "DataAssets/QuestSettings.h"
#include "Kismet/GameplayStatics.h"

#if WITH_EDITOR
#include "Misc/UObjectToken.h"
#endif

UQuestComponent::UQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma region BlueprintFunctions

void UQuestComponent::CreateStepObject(const int ID)
{
	const auto [QuestStepClass, QuestSettingClass] = CurrentQuest->Steps[ID];

	const UClass* QuestStep = GetOrLoad(&QuestStepClass);
	const UClass* QuestSetting = GetOrLoad(&QuestSettingClass);

	UQuestStep* QuestStepObject = NewObject<UQuestStep>(GetWorld(), QuestStep);
	const UQuestSettings* QuestSettingObject = NewObject<UQuestSettings>(GetWorld(), QuestSetting);

	CurrentQuest->CurrentStep = QuestStepObject;
	CurrentQuest->CurrentStepID = ID;
	QuestStepObject->Init(this);
	QuestStepObject->OnQuestStepStart(QuestSettingObject, CurrentQuest, this);
}

bool UQuestComponent::StartQuest(UObject* SelfObject, const TSoftObjectPtr<UQuest> InQuest)
{
	UQuest* Quest = GetOrLoad(&InQuest);

	if (CurrentQuest != nullptr && IsValidChecked(CurrentQuest) && CurrentQuest->IsA(UQuest::StaticClass()))
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

	CurrentQuest = DuplicateObject(Quest, GetWorld());

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

	CreateStepObject(0);

	return true;
}

void UQuestComponent::QuestStepCompletedExec(const bool bCancelled) const
{
	CurrentQuest->CurrentStep->OnQuestStepCompleted(bCancelled);
	CurrentQuest->CurrentStep->ConditionalBeginDestroy();
	CurrentQuest->CurrentStep = nullptr;
}

bool UQuestComponent::FinishQuestInternal(const UObject* SelfObject, const bool bCancelled)
{
	if (CurrentQuest == nullptr || !IsValidChecked(CurrentQuest))
	{
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Quest %s is not the current running quest"),
		       *CurrentQuest->Name);

#if WITH_EDITOR
		FMessageLog("PIE").Error()
		                  ->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest")))
		                  ->AddToken(FTextToken::Create(FText::FromString("is not the current running quest ")))
		                  ->AddToken(FUObjectToken::Create(SelfObject->GetClass()));
#else
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Quest %s is not the current running quest"),
			*CurrentQuest->Name);
#endif

		return false;
	}

#if WITH_EDITOR
	FMessageLog("PIE").Info()
	                  ->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest Stopped")))
	                  ->AddToken(FTextToken::Create(FText::FromString(CurrentQuest->Name)));
#else
	UE_LOG(LogQuestSystemModule, Log, TEXT("QuestSystem: Quest Stopped %s"), *CurrentQuest->Name);
#endif

	if (CurrentQuest->CurrentStep != nullptr)
	{
		QuestStepCompletedExec(bCancelled);
	}
	else
	{
#if WITH_EDITOR
		FMessageLog("PIE").Error()
		                  ->AddToken(FTextToken::Create(
			                  FText::FromString("QuestSystem: Quest did not have valid current step ")))
		                  ->AddToken(FTextToken::Create(FText::FromString(CurrentQuest->Name)));
#else
		UE_LOG(LogQuestSystemModule, Log, TEXT("QuestSystem: Quest did not have valid current step %s"), *CurrentQuest->Name);
#endif
	}

	CurrentQuest->ConditionalBeginDestroy();
	CurrentQuest = nullptr;
	return true;
}

bool UQuestComponent::CancelQuest(UObject* SelfObject)
{
	return FinishQuestInternal(SelfObject, true);
}

bool UQuestComponent::FinishQuest(UObject* SelfObject)
{
	return FinishQuestInternal(SelfObject, false);
}

bool UQuestComponent::FinishStep(UObject* SelfObject)
{
	if (CurrentQuest != nullptr && CurrentQuest->CurrentStep != nullptr)
	{
		const int NextID = CurrentQuest->CurrentStepID + 1;

		if (CurrentQuest->Steps.Max() <= NextID)
		{
			FinishQuestInternal(SelfObject, false);
			return false;
		}

#if WITH_EDITOR
		FMessageLog("PIE").Info()
		                  ->AddToken(FTextToken::Create(FText::FromString("QuestSystem: Quest finished step")))
		                  ->AddToken(FTextToken::Create(FText::FromString(CurrentQuest->Name)));
#else
		UE_LOG(LogQuestSystemModule, Log, TEXT("QuestSystem: Quest finished step %s"), *CurrentQuest->Name);
#endif

		QuestStepCompletedExec(false);
		CreateStepObject(NextID);
	}

	return false;
}

FString UQuestComponent::GetCurrentQuestName() const
{
	if (CurrentQuest != nullptr)
	{
		return CurrentQuest->Name;
	}

	return FString();
}

FString UQuestComponent::GetCurrentQuestDescription() const
{
	if (CurrentQuest != nullptr && CurrentQuest->CurrentStep != nullptr)
	{
		return CurrentQuest->CurrentStep->GetDescription();
	}

	return FString();
}
#pragma endregion

#pragma region Templated SoftPointer Helpers
template <typename T>
T* UQuestComponent::GetOrLoad(const TSoftObjectPtr<T>* InObject)
{
	if (InObject->IsValid())
	{
		return InObject->Get();
	}

	return InObject->LoadSynchronous();
}

template <typename T>
UClass* UQuestComponent::GetOrLoad(const TSoftClassPtr<T>* InClass)
{
	if (InClass->IsValid())
	{
		return InClass->Get();
	}

	UClass* Class = InClass->LoadSynchronous();

	if (Class == nullptr)
	{
		UE_LOG(LogQuestSystemModule, Error, TEXT("QuestSystem: Class %s is not valid"), *InClass->ToString());
		return nullptr;
	}

	return Class;
}
#pragma endregion
