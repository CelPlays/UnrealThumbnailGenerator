// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "ThumbnailCreatorStyle.h"

class FThumbnailCreatorCommands : public TCommands<FThumbnailCreatorCommands>
{
public:

	FThumbnailCreatorCommands()
		: TCommands<FThumbnailCreatorCommands>(TEXT("ThumbnailCreator"), NSLOCTEXT("Contexts", "ThumbnailCreator", "ThumbnailCreator Plugin"), NAME_None, FThumbnailCreatorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};