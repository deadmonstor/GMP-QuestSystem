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

	for (int i = 0; i < EventQuest[Name].Events.Num(); i++)
	{
		if (!EventQuest[Name].Events[i].ExecuteIfBound(Name))
		{
			auto Events = EventQuest[Name].Events;
			Events.Remove(Events[i]);

			// TODO: Look into this
			//EventQuest[Name].Events.RemoveAt(i);
		}
	}
}

void UQuestStep::BindEventToName(const FString Name, const FQuestEvent EventRef)
{
	if (!EventQuest.Contains(Name))
	{
		EventQuest.Add(Name, FEventHolder());
	}
	
	EventQuest[Name].Events.Add(EventRef);
}
