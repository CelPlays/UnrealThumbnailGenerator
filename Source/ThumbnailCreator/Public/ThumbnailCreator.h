// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Core/Public/Containers/Ticker.h"
#include "SImage.h"
#include "SEditorViewport.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewScene.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewSceneModule.h"
#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class FThumbnailCreatorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void PreUnloadCallback() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();

	/*
	*	Assign asset to the viewport client scene
	*
	*	@param	_Dats		FAssetData of the asset to use
	*	@param	bTakeShot	Should we take a shot with this change?
	*/
	void AssignAsset(FAssetData _Data, bool bTakeShot);

	//Generate all screenshots from selection of the conten browser
	FReply GenerateFromSelection();
	//Set preview mesh to the one selected in the content browser
	FReply PreviewSelected();
	//generate image without changing any mesh with the current view
	FReply GenerateView();

	//Next in queue for the image tick
	bool NextInQueue(float Delta);

	//Remove from StartupImages 
	void RemoveFromPreKnown(const FString ToRemove);

	/** Pointer to the Viewport */
	TSharedPtr<class SThumbnailViewport> ViewportPtr;
	//Details view of the screenshot settings
	TSharedPtr<class IDetailsView> DetailsView;

	//Queue of active to take screenshots
	TArray<FAssetData> Queue;
	//All created images still to process
	TArray<FString> CreatedImages;
	//Images to ignore for process
	TArray<FString> StartupImages;

	//Tick delegate for the 0.03s image tick
	FTickerDelegate ImageTickDelegate;

	//Thumbnail options for the screenshots
	class UThumbnailOptions* ThumbnailOptions;
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);
	
	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;
};