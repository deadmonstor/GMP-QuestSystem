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

	EventTest.Broadcast(Name);
}
