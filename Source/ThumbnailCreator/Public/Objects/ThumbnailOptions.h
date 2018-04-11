// Copyright (c) Panda Studios Comm. V.  - All Rights Reserves. Under no circumstance should this could be distributed, used, copied or be published without written approved of Panda Studios Comm. V. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ThumbnailOptions.generated.h"


UCLASS(Transient)
class THUMBNAILCREATOR_API UThumbnailOptions : public UObject
{
	GENERATED_BODY()


public:
	//Screenshot X Size
	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 ScreenshotXSize = 512;
	//Screenshot Y Size
	UPROPERTY(EditAnywhere, Category = "Setup")
		int32 ScreenshotYSize = 512;
};
