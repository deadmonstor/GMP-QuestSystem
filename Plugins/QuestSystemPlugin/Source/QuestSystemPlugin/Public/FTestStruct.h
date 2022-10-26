#pragma once
#include "DataAssets/UQuestStep.h"

#include "FTestStruct.generated.h"

class UQuestSettings;
USTRUCT(BlueprintType)

// TODO: Rename this to something more appropriate
struct FTestStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test", meta=(BlueprintBaseOnly=true))
	TSoftClassPtr<UQuestStep> QuestComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Test")
	TSoftClassPtr<UQuestSettings> Test;
};

