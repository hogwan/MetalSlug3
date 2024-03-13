#include "MissionStartChar.h"
#include "ContentsHelper.h"

MissionStartChar::MissionStartChar()
{
}

MissionStartChar::~MissionStartChar()
{
}

void MissionStartChar::BeginPlay()
{
	Renderer = CreateImageRenderer(MT3RenderOrder::UI);
	Renderer->SetTransform({ {0,0},{500,500} });
	Renderer->CameraEffectOff();
	Renderer->CreateAnimation("A", "MissionStart.png", 0, 0, 0.08f, false);
	Renderer->CreateAnimation("B", "MissionStart.png", 1, 1, 0.08f, false);
	Renderer->CreateAnimation("C", "MissionStart.png", 2, 2, 0.08f, false);
	Renderer->CreateAnimation("D", "MissionStart.png", 3, 3, 0.08f, false);
	Renderer->CreateAnimation("E", "MissionStart.png", 4, 4, 0.08f, false);
	Renderer->CreateAnimation("F", "MissionStart.png", 5, 5, 0.08f, false);
	Renderer->CreateAnimation("G", "MissionStart.png", 6, 6, 0.08f, false);
	Renderer->CreateAnimation("H", "MissionStart.png", 7, 7, 0.08f, false);
	Renderer->CreateAnimation("I", "MissionStart.png", 8, 8, 0.08f, false);
	Renderer->CreateAnimation("J", "MissionStart.png", 9, 9, 0.08f, false);
	Renderer->CreateAnimation("K", "MissionStart.png", 10, 10, 0.08f, false);
	Renderer->CreateAnimation("L", "MissionStart.png", 11, 11, 0.08f, false);
	Renderer->CreateAnimation("M", "MissionStart.png", 12, 12, 0.08f, false);
	Renderer->CreateAnimation("N", "MissionStart.png", 13, 13, 0.08f, false);
	Renderer->CreateAnimation("O", "MissionStart.png", 14, 14, 0.08f, false);
	Renderer->CreateAnimation("P", "MissionStart.png", 15, 15, 0.08f, false);
	Renderer->CreateAnimation("Q", "MissionStart.png", 16, 16, 0.08f, false);
	Renderer->CreateAnimation("R", "MissionStart.png", 17, 17, 0.08f, false);
	Renderer->CreateAnimation("S", "MissionStart.png", 18, 18, 0.08f, false);
	Renderer->CreateAnimation("T", "MissionStart.png", 19, 19, 0.08f, false);
	Renderer->CreateAnimation("U", "MissionStart.png", 20, 20, 0.08f, false);
	Renderer->CreateAnimation("V", "MissionStart.png", 21, 21, 0.08f, false);
	Renderer->CreateAnimation("W", "MissionStart.png", 22, 22, 0.08f, false);
	Renderer->CreateAnimation("X", "MissionStart.png", 23, 23, 0.08f, false);
	Renderer->CreateAnimation("Y", "MissionStart.png", 24, 24, 0.08f, false);
	Renderer->CreateAnimation("Z", "MissionStart.png", 25, 25, 0.08f, false);
	Renderer->CreateAnimation("1", "MissionStart.png", 26, 26, 0.08f, false);
	Renderer->CreateAnimation("2", "MissionStart.png", 27, 27, 0.08f, false);
	Renderer->CreateAnimation("3", "MissionStart.png", 28, 28, 0.08f, false);
	Renderer->CreateAnimation("4", "MissionStart.png", 29, 29, 0.08f, false);
	Renderer->CreateAnimation("5", "MissionStart.png", 30, 30, 0.08f, false);
	Renderer->CreateAnimation("6", "MissionStart.png", 31, 31, 0.08f, false);
	Renderer->CreateAnimation("7", "MissionStart.png", 32, 32, 0.08f, false);
	Renderer->CreateAnimation("8", "MissionStart.png", 33, 33, 0.08f, false);
	Renderer->CreateAnimation("9", "MissionStart.png", 34, 34, 0.08f, false);
	Renderer->CreateAnimation("!", "MissionStart.png", 35, 35, 0.08f, false);
	Renderer->CreateAnimation("?", "MissionStart.png", 36, 36, 0.08f, false);
}

void MissionStartChar::Tick(float _DeltaTime)
{
	Renderer->ChangeAnimation(S,false,0,0.08f);

	if (MoveOn)
	{
		AddActorLocation(MoveDir * 5.0f * _DeltaTime);
	}
}
