#include "Marco_Idle.h"

Marco_Idle::Marco_Idle()
{
}

Marco_Idle::~Marco_Idle()
{
}

void Marco_Idle::BeginPlay()
{
	Renderer = CreateImageRenderer(4);
	Renderer->SetImage("Marco_Idle.png");
	Renderer->CreateAnimation("Idle", "Marco_Idle.png", 0, 5, 0.08f, true);
	Renderer->SetTransform({ {0,0},{500,500} });
}

void Marco_Idle::Tick(float _DeltaTime)
{
	if (AnimStart)
	{
		Renderer->ChangeAnimation("Idle", false, 0, 0.08f);
	}
}
