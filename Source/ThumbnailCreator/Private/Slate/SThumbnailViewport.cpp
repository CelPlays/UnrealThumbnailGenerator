// Copyright (c) Panda Studios Comm. V.  - All Rights Reserves. Under no circumstance should this could be distributed, used, copied or be published without written approved of Panda Studios Comm. V. 

#include "SThumbnailViewport.h"
#include "SViewport.h"
#include "Editor/LevelEditor/Private/SLevelViewportToolBar.h"
#include "AssetEditorModeManager.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewScene.h"
#include "Editor/AdvancedPreviewScene/Public/AdvancedPreviewSceneModule.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMesh.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PostProcessComponent.h"
#include "ThumbnailViewportClient.h"


void SThumbnailViewport::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(MeshComp);
	Collector.AddReferencedObject(MaterialComp);
	Collector.AddReferencedObject(SkelMeshComp);
	Collector.AddReferencedObject(PostComp);
}

TSharedRef<class SEditorViewport> SThumbnailViewport::GetViewportWidget()
{
	return SharedThis(this);
}

TSharedPtr<FExtender> SThumbnailViewport::GetExtenders() const
{
	TSharedPtr<FExtender> Result(MakeShareable(new FExtender));
	return Result;
}

void SThumbnailViewport::OnFloatingButtonClicked()
{
	// Nothing
}

//Just create the advnaced preview scene and initiate components
SThumbnailViewport::SThumbnailViewport() : PreviewScene(MakeShareable(new FAdvancedPreviewScene(FPreviewScene::ConstructionValues())))
{

	MeshComp = NewObject<UStaticMeshComponent>();

	MaterialComp = NewObject<UStaticMeshComponent>();

	SkelMeshComp = NewObject<USkeletalMeshComponent>();

	PostComp = NewObject <UPostProcessComponent>();
}

SThumbnailViewport::~SThumbnailViewport() 
{
	if (TypedViewportClient.IsValid())
	{
		TypedViewportClient->Viewport = NULL;
	}
}

void SThumbnailViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}


TSharedRef<FEditorViewportClient> SThumbnailViewport::MakeEditorViewportClient()
{
	TypedViewportClient = MakeShareable(new FThumbnailViewportClient(SharedThis(this), PreviewScene.ToSharedRef()));
	return TypedViewportClient.ToSharedRef(); 
}

void SThumbnailViewport::BindCommands()
{
	SEditorViewport::BindCommands();
}

EVisibility SThumbnailViewport::GetTransformToolbarVisibility() const
{
	return EVisibility::Visible;
}

void SThumbnailViewport::OnFocusViewportToSelection()
{

}


void SThumbnailViewport::SetMesh(class UStaticMesh* inMesh, bool bTakeShot)
{
	//Set the mesh inside the client's meshcomp
	TypedViewportClient->SetMesh(inMesh, bTakeShot);
}

FText SThumbnailViewport::GetTitleText() const
{
	//return the title text of the viewport
	return FText::FromString("Thumbnail Generator");
}
