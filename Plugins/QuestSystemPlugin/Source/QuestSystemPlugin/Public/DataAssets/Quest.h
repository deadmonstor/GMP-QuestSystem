#pragma once

#include "CoreMinimal.h"
#include "FTestStruct.h"
#include "UQuestStep.h"
#include "Quest.generated.h"

UCLASS(BlueprintType)
class UQuest final : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FTestStruct> Steps;
};
