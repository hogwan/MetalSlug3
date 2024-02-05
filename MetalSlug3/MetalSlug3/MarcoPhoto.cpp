#include "MarcoPhoto.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/ImageRenderer.h>

MarcoPhoto::MarcoPhoto()
{
}

MarcoPhoto::~MarcoPhoto()
{
}

void MarcoPhoto::BeginPlay()
{
	ThisRenderer = CreateImageRenderer(5);
	ThisRenderer->SetImage("MarcoSelectedAnim.png");
	ThisRenderer->SetTransform({ {0,0} , {170, 325} });
	ThisRenderer->SetImageCuttingTransform({ {0,0}, {64, 120} });
	ThisRenderer->CreateAnimation("Marco_Selected", "MarcoSelectedAnim.png", 0, 1, 0.08f, false);

	SetActorLocation({ 133.0f, 355.0f });
}

void MarcoPhoto::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (true == EngineInput::IsDown(VK_RETURN))
	{
		ThisRenderer->ChangeAnimation("Marco_Selected");
	}
}