#pragma once
#include "DataAssets/UQuestStep.h"

#include "FQuestStruct.generated.h"

class UQuestSettings;
USTRUCT(BlueprintType)

struct FQuestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BlueprintBaseOnly=true))
	TSoftClassPtr<UQuestStep> QuestComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftClassPtr<UQuestSettings> QuestSettings;
};

