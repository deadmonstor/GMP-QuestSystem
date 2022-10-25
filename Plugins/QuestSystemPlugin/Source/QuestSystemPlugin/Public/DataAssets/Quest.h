#pragma once

#include "CoreMinimal.h"
#include "Quest.generated.h"


USTRUCT(BlueprintType)
struct FQuest
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Test;
};
