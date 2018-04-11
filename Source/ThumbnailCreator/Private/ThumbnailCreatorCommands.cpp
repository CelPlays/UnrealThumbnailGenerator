// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ThumbnailCreatorCommands.h"

#define LOCTEXT_NAMESPACE "FThumbnailCreatorModule"

void FThumbnailCreatorCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "ThumbnailCreator", "Bring up ThumbnailCreator window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
