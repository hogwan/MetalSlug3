#include "Panel.h"
#include <EngineCore\EngineCore.h>
#include <EngineBase/EngineTime.h>
#include <EngineCore/ImageRenderer.h>

Panel::Panel()
{
}

Panel::~Panel()
{
}

void Panel::BeginPlay()
{
	ThisRenderer = CreateImageRenderer(0);
	ThisRenderer->SetImage("Panel.png");
	ThisRenderer->SetTransform({ {0,0} , {800, 600} });
	SetActorLocation({ 400.0f, 300.0f });
}
