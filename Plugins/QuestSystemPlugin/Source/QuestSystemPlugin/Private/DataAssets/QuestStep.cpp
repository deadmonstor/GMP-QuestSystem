#include "DataAssets/QuestStep.h"
#include "QuestComponent.h"

UWorld* UQuestStep::GetWorld() const
{
	return GEngine->GetCurrentPlayWorld();
}

void UQuestStep::Init(UQuestComponent* QuestComponent)
{
	OwnerQuestComponent = QuestComponent;
	OwnerQuest = QuestComponent->GetCurrentQuest();
	IsReady = true;
}

void UQuestStep::CallEvent(const FString Name) const
{
	if (!IsReady)
	{
		return;
	}

	if (!EventQuest.Contains(Name))
	{
		return;
	}

	for (int i = 0; i < EventQuest[Name].test.Num(); i++)
	{
		// TODO: If this works remove the name here, unless they bind it to two? might be needed idk

		if (!EventQuest[Name].test[i].ExecuteIfBound(Name))
		{
			//EventQuest[Name].test.Remove(EventQuest[Name].test[i]);
		}
	}
}

void UQuestStep::BindEventToName(const FString Name, const FQuestEvent EventRef)
{
	// TODO: Check if this is a mem leak lol

	if (!EventQuest.Contains(Name))
	{
		EventQuest.Add(Name, FTestasdasdasda());
	}
	
	EventQuest[Name].test.Add(EventRef);
}
