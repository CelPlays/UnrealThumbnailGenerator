// Copyright (c) Panda Studios Comm. V.  - All Rights Reserves. Under no circumstance should this could be distributed, used, copied or be published without written approved of Panda Studios Comm. V. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HighResScreenshot.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewScene.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewSceneModule.h"
#include "Editor/AdvancedPreviewScene/Public/SAdvancedPreviewDetailsTab.h"
#include "Editor/UnrealEd/Public/LevelEditorViewport.h"
#include "Editor/UnrealEd/Public/EditorViewportClient.h"

enum class EScreenshotType : uint8 
{
	Mesh,
	Skeletal,
	Material
};


class THUMBNAILCREATOR_API FThumbnailViewportClient : public FEditorViewportClient
{

public:

	/** The preview scene we use instead of the real gameplay scene */

	/** Pointer back to the Editor Viewport */
	TWeakPtr<class SThumbnailViewport> ViewportPtr;

	//Constructor and destructor
	FThumbnailViewportClient(const TSharedRef<SThumbnailViewport>& InThumbnailViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene);

	//Components in the scne
	UPROPERTY()
	UStaticMeshComponent* MeshComp;
	UPROPERTY()
	USkeletalMeshComponent* SkelMeshComp;
	UPROPERTY()
	UStaticMeshComponent* MaterialComp;

	/** Stored pointer to the preview scene in which the static mesh is shown */
	FAdvancedPreviewScene* AdvancedPreviewScene;

	//All registerd actor components
	UPROPERTY()
	TArray<UPrimitiveComponent*> ActorComponents;

	//Active type of the screenshot
	EScreenshotType ActiveType;

	//Options file
	class UThumbnailOptions* ThumbnailOptions;

	virtual void Tick(float DeltaSeconds) override;

	//Take one single shot
	void TakeSingleShot();

	void ResetScene();
	/*
	*	Set the static mesh
	*	@param inMesh		Mesh to use
	*	@param bTakeShot	Should we take a shot with this change?
	*/
	void SetMesh(class UStaticMesh* inMesh, bool bTakeShot = false);
	/*
	*	Set the Skeletal mesh
	*	@param inMesh		Mesh to use
	*	@param AnimAsset	Animation asset to set it with
	*	@param bTakeShot	Should we take a shot with this change?
	*/
	void SetSkelMesh(class USkeletalMesh* inMesh, class UAnimationAsset* AnimAsset = NULL, bool bTakeShot = false);
	/*
	*	Set the material preview
	*	@param inMaterial	Material to use
	*	@param bTakeShot	Should we take a shot with this change?
	*/
	void SetMaterial(class UMaterialInterface* inMaterial, bool bTakeShot = false);
	/*
	*	Update visibilty of the proper mesh
	*	@param ComponentToActivate		Component to activate
	*	@param Type						Type of the screenshot to activate
	*/
	void SetComponentVisibility(UActorComponent* ComponentToActivate, EScreenshotType Type);

	/*
	*	Get the name of the active asset
	*/
	FString GetAssetName();
};
