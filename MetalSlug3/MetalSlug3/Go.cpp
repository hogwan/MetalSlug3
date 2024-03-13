#include "Go.h"
#include "ContentsHelper.h"
#include <EnginePlatform/EngineSound.h>
AGo::AGo()
{
}

AGo::~AGo()
{
}

void AGo::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer->SetImage("Go.png");
	Renderer->SetTransform({ { 0,0 }, { 500,500 } });
	Renderer->CreateAnimation("Go", "Go.png", 0, 15, 0.08f, true);
	Renderer->CameraEffectOff();
}

void AGo::Tick(float _DeltaTime)
{
	UCollision* ScreenCollider = UContentsHelper::ScreenCol->GetCollider();
	std::vector<UCollision*> Result;
	if (ScreenCollider->CollisionCheck(MT3CollisionOrder::Enemy, Result)
		|| ScreenCollider->CollisionCheck(MT3CollisionOrder::Boss, Result))
	{
		Renderer->ActiveOff();
		Renderer->AnimationReset();
		AccTime = 0.0f;
	}
	else
	{
		AccTime += _DeltaTime;
	}

	if (AccTime > TurnOnTime)
	{
		Renderer->ActiveOn();
		Renderer->ChangeAnimation("Go", false, 0, 0.08f);

		if (!Trigger && Renderer->GetCurAnimationFrame() == 0)
		{
			UEngineSoundPlayer Sound = UEngineSound::SoundPlay("Go.mp3");
			Trigger = true;
		}

		if (Renderer->IsCurAnimationEnd())
		{
			Trigger = false;
		}
	}
}
