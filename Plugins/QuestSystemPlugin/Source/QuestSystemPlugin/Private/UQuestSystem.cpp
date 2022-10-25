#include "UQuestSystem.h"
#include "QuestSystemPlugin.h"

bool UQuestSystem::StartQuest(const FQuest Quest)
{
	UE_LOG(LogQuestSystemModule, Log, TEXT("START QUEST %i"), Quest.Test);
	return true;
}

bool UQuestSystem::StopQuest(const FQuest Quest)
{
	UE_LOG(LogQuestSystemModule, Log, TEXT("STOP QUEST %i"), Quest.Test);
	return true;
}

bool UQuestSystem::FinishQuest(const FQuest Quest)
{
	UE_LOG(LogQuestSystemModule, Log, TEXT("FINISHED QUEST %i"), Quest.Test);
	return true;
}
