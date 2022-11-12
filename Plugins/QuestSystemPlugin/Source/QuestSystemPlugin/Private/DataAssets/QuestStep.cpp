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
	// TODO: Should we just be halting here or should we try and be nice and error
	if (!IsReady)
	{
		return;
	}

	EventTest.Broadcast(Name);
}
