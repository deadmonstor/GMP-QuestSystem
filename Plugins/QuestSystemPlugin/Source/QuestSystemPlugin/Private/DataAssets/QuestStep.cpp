#include "DataAssets/QuestStep.h"
#include "DataAssets/Quest.h"

UWorld* UQuestStep::GetWorld() const
{
	return GEngine->GetCurrentPlayWorld();
}

void UQuestStep::Init(UQuestComponent* QuestComponent, UQuest* Quest)
{
	OwnerQuestComponent = QuestComponent;
	OwnerQuest = Quest;
	IsReady = true;
}

void UQuestStep::CallEvent(const FString Name)
{
	if (!IsReady)
	{
		return;
	}

	EventTest.Broadcast(Name);
}
