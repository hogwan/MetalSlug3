#include "SlugEnergyBar.h"
#include "ContentsHelper.h"

ASlugEnergyBar::ASlugEnergyBar()
{
}

ASlugEnergyBar::~ASlugEnergyBar()
{
}

void ASlugEnergyBar::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer->SetImage("Status.png");
	Renderer->SetTransform({ { 0,0 }, { 430,530 } });
	Renderer->CreateAnimation("SlugEnergy", "Status.png", 1, 1, 0.08f, true);
	Renderer->CameraEffectOff();
	Renderer->ChangeAnimation("SlugEnergy", false, 0, 0.08f);
}

void ASlugEnergyBar::Tick(float _DeltaTime)
{
}
