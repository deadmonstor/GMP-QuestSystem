#include "DataAssets/QuestStep.h"
#include "QuestComponent.h"

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
			Events.RemoveAt(i);
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

void UQuestStep::RemoveEventFromName(const FString Name, const FQuestEvent EventRef)
{
	if (!EventQuest.Contains(Name))
	{
		return;
	}

	if (!EventQuest[Name].Events.Contains(EventRef))
	{
		return;
	}
	
	EventQuest[Name].Events.Remove(EventRef);
}
