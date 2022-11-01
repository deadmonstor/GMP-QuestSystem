#include "DataAssets/UQuestStep.h"

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
	// TODO: We should probably just fail on IsReady == false
	if (!IsReady) return;
	// TODO: Look if we can make this work in begin play, seems stupid but we probably should be allowed
	// Actually does this even make sense when we have our own "init"/OnQuestStepStart function now
	
	EventTest.Broadcast(Name);
}