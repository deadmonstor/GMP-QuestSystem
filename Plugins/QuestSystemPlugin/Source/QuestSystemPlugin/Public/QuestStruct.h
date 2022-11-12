#pragma once
#include "QuestStruct.generated.h"

class UQuestSettings;
class UQuestStep;
USTRUCT(BlueprintType)

struct FQuestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BlueprintBaseOnly=true))
	TSoftClassPtr<UQuestStep> QuestComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UQuestSettings> QuestSettings;
};
