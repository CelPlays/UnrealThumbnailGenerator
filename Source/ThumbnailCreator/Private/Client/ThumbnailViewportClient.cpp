// Copyright (c) Panda Studios Comm. V.  - All Rights Reserves. Under no circumstance should this could be distributed, used, copied or be published without written approved of Panda Studios Comm. V. 
#include "ThumbnailViewportClient.h"

//Thumbnail Core
#include "ThumbnailOptions.h"
#include "ThumbnailCreator.h"

//Image
#include "Runtime/Engine/Public/HighResScreenshot.h"
#include "Editor/LevelEditor/Private/HighresScreenshotUI.h"

//Engine
#include "AssetEditorModeManager.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "LevelEditor.h"
#include "Utils.h"
#include "EngineGlobals.h"

//Slate
#include "SViewport.h"
#include "SThumbnailViewport.h"
#include "Editor/UnrealEd/Public/UnrealWidget.h"

//Components
#include "Components/SkeletalMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/StaticMeshActor.h"
#include "Runtime/Engine/Classes/Components/PostProcessComponent.h"
#include "Runtime/Engine/Classes/Materials/MaterialInterface.h"

//Scene
#include "Runtime/Engine/Public/SceneView.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewScene.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewScene.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewSceneModule.h"
#include "Runtime/Engine/Classes/Engine/PostProcessVolume.h"
#include "Runtime/Engine/Public/SceneManagement.h"
#include "Runtime/Engine/Public/CanvasTypes.h"
#include "Runtime/Engine/Classes/Materials/Material.h"
#include "Runtime/Engine/Public/PreviewScene.h"


FThumbnailViewportClient::FThumbnailViewportClient(const TSharedRef<SThumbnailViewport>& InThumbnailViewport, const TSharedRef<FAdvancedPreviewScene>& InPreviewScene) 
: FEditorViewportClient(nullptr, &InPreviewScene.Get(), StaticCastSharedRef<SEditorViewport>(InThumbnailViewport))
, ViewportPtr(InThumbnailViewport)
{

	AdvancedPreviewScene = static_cast<FAdvancedPreviewScene*>(PreviewScene);

	// Enable RealTime
	SetRealtime(true);

	// Hide grid, we don't need this.
	DrawHelper.bDrawGrid = false;
	DrawHelper.bDrawPivot = false;
	DrawHelper.AxesLineThickness = 5;
	DrawHelper.PivotSize = 5;

	//Initiate view
	SetViewLocation(FVector(75, 75, 75));
	SetViewRotation(FVector(-75, -75, -75).Rotation());

	EngineShowFlags.SetScreenPercentage(true);

	// Set the Default type to Ortho and the XZ Plane
	ELevelViewportType NewViewportType = LVT_Perspective;
	SetViewportType(NewViewportType);
	
	// View Modes in Persp and Ortho
	SetViewModes(VMI_Lit, VMI_Lit);

	//Create the static mesh component
	MeshComp = ViewportPtr.Pin()->MeshComp;
	MeshComp->bRenderCustomDepth = true;

	MaterialComp = ViewportPtr.Pin()->MaterialComp;
	MaterialComp->bRenderCustomDepth = true;
	MaterialComp->SetVisibility(false);

	//Create skeletal mesh component
	SkelMeshComp = ViewportPtr.Pin()->SkelMeshComp;
	SkelMeshComp->bRenderCustomDepth = true;
	SkelMeshComp->SetVisibility(false);
	
	//Add our own post process on the world
	UPostProcessComponent* PostComp = ViewportPtr.Pin()->PostComp;

	//Add both components to the scene
	PreviewScene->AddComponent(MeshComp, FTransform(), false);
	PreviewScene->AddComponent(SkelMeshComp, FTransform(), false);
	PreviewScene->AddComponent(PostComp, FTransform(), false);
	PreviewScene->AddComponent(MaterialComp, FTransform(), false);

	//Create a new defaults cube
	UStaticMesh* NewMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *(FString("StaticMesh'/Engine/VREditor/BasicMeshes/SM_Pyramid_01.SM_Pyramid_01'"))));
	UStaticMesh* MaterialMesh = Cast<UStaticMesh>(StaticLoadObject(UStaticMesh::StaticClass(), NULL, *(FString("StaticMesh'/Engine/EngineMeshes/MaterialSphere.MaterialSphere'"))));

	//If mesh is valid... set the mesh and render custom depth
	if (NewMesh)
	{
		MeshComp->SetStaticMesh(NewMesh);
	}

	if (MaterialMesh)
	{
		MaterialComp->SetStaticMesh(MaterialMesh);
	}

	//Allow post process materials...
	EngineShowFlags.SetPostProcessMaterial(true);
	EngineShowFlags.SetPostProcessing(true);

	//Force screen percentage higher
	PostComp->Settings.ScreenPercentage = 200;

	//Unbound
	PostComp->bUnbound = true;

	//Set that the mask is enabled for screenshots so it records transparency in the output
	GetHighResScreenshotConfig().bMaskEnabled = true;

	//Register components inside the array
	ActorComponents.Add(MeshComp);
	ActorComponents.Add(SkelMeshComp);
	ActorComponents.Add(MaterialComp);

}

void FThumbnailViewportClient::Tick(float DeltaSeconds)
{
	FEditorViewportClient::Tick(DeltaSeconds);

	// Tick the preview scene world.
	if (!GIntraFrameDebuggingGameThread)
	{
		if(AdvancedPreviewScene)
		AdvancedPreviewScene->GetWorld()->Tick(LEVELTICK_All, DeltaSeconds);
	}
}

void FThumbnailViewportClient::TakeSingleShot()
{
	//Enable green mask
	EngineShowFlags.SetHighResScreenshotMask(true);

	//set the size of the screenshot
	GScreenshotResolutionX = ThumbnailOptions->ScreenshotXSize;
	GScreenshotResolutionY = ThumbnailOptions->ScreenshotYSize;

	//Set the name of the screenshot
	FString UseName = GetAssetName();

	GetHighResScreenshotConfig().FilenameOverride = "Thumb_" + UseName;

	//Take the shots
	TakeHighResScreenShot();

	//Turn off green mask
	EngineShowFlags.SetHighResScreenshotMask(false);


	//Remove this image from known images so we can process it again
	auto ModulePtr = FModuleManager::LoadModulePtr<FThumbnailCreatorModule>(FName("ThumbnailCreator"));
	if (ModulePtr)
	{
		ModulePtr->RemoveFromPreKnown(UseName);
	}
}

void FThumbnailViewportClient::ResetScene()
{
	//PreviewScene = NULL;
}

void FThumbnailViewportClient::SetMesh(class UStaticMesh* inMesh, bool bTakeShot)
{
	//Update static mesh to new one
	MeshComp->SetStaticMesh(inMesh);
	MeshComp->SetRenderCustomDepth(true);
	MeshComp->MarkRenderStateDirty();

	SetComponentVisibility(MeshComp, EScreenshotType::Mesh);

	//If we need to take a shot, take one
	if (bTakeShot)
	{
		TakeSingleShot();
	}


}

void FThumbnailViewportClient::SetSkelMesh(class USkeletalMesh* inMesh, class UAnimationAsset* AnimAsset /*= NULL*/, bool bTakeShot /*= false*/)
{
	if (inMesh || AnimAsset)
	{
		//Only update mesh if we have one
		if(inMesh)
		SkelMeshComp->SetSkeletalMesh(inMesh);

		//If our anim asset is valid and we have a skeletal mesh then play it
		if (AnimAsset && SkelMeshComp->SkeletalMesh)
		{
			SkelMeshComp->PlayAnimation(AnimAsset, true);
		}

		//Flip visibility
		MeshComp->SetVisibility(false);
		SkelMeshComp->SetVisibility(true);
	}

	SetComponentVisibility(SkelMeshComp, EScreenshotType::Skeletal);

	//If we need to take a shot, take one
	if (bTakeShot)
	{
		TakeSingleShot();
	}
}

void FThumbnailViewportClient::SetMaterial(UMaterialInterface* inMaterial, bool bTakeShot /*= false*/)
{
	if (MaterialComp && inMaterial)
	{
		MaterialComp->SetMaterial(0, inMaterial);
	}

	SetComponentVisibility(MaterialComp, EScreenshotType::Material);

	if (bTakeShot)
	{
		TakeSingleShot();
	}
}

void FThumbnailViewportClient::SetComponentVisibility(UActorComponent* ComponentToActivate, EScreenshotType Type)
{
	//go over all components and only show the one we want to activate
	for (UPrimitiveComponent* Comp : ActorComponents)
	{
		Comp->SetVisibility(ComponentToActivate == Comp);
	}

	//Set the active type afterwards
	ActiveType = Type;
}


FString FThumbnailViewportClient::GetAssetName()
{
	if (ActiveType == EScreenshotType::Mesh)
	{
		FString Name;
		MeshComp->GetStaticMesh()->GetName(Name);
		return Name;
	}
	else if (ActiveType == EScreenshotType::Skeletal)
	{
		FString Name;
		SkelMeshComp->SkeletalMesh->GetName(Name);
		return Name;
	}
	else
	{
		FString Name;
		MaterialComp->GetMaterial(0)->GetName(Name);
		return Name;
	}
}

