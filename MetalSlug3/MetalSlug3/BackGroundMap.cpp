#include "BackGroundMap.h"
#include "ContentsHelper.h"
#include <EngineCore\EngineResourcesManager.h>

ABackGroundMap::ABackGroundMap()
{
}

ABackGroundMap::~ABackGroundMap()
{
}

void ABackGroundMap::SetMapImage(std::string_view _MapImageName)
{
	Renderer->SetImage(_MapImageName);
	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();
	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGroundMap::SetColMapImage(std::string_view _MapImageName)
{
	ColRenderer->SetImage(_MapImageName);
	UWindowImage* Image = ColRenderer->GetImage();
	UContentsHelper::ColMapImage = Image;
	FVector ImageScale = Image->GetScale();
	ColRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGroundMap::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);



	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}


void ABackGroundMap::SwitchDebug()
{
	if (true == Renderer->IsActive())
	{
		Renderer->SetActive(false);
		ColRenderer->SetActive(true);
	}
	else
	{
		Renderer->SetActive(true);
		ColRenderer->SetActive(false);
	}

}
void ABackGroundMap::BeginPlay()
{
	// 여기서 상수로 고정시키면.
	Renderer = CreateImageRenderer(MT3RenderOrder::Map);
	ColRenderer = CreateImageRenderer(MT3RenderOrder::Map);
	ColRenderer->SetActive(false);


}