#include "Bomb.h"
#include "EngineCore/EngineCore.h"

ABomb::ABomb()
{
}

ABomb::~ABomb()
{
}

void ABomb::BeginPlay()
{
	{
		UImageRenderer* Renderer = CreateImageRenderer(-10);
		Renderer->SetImage("Tool_Bomb_Right_0.bmp");
		Renderer->SetTransform({ {0,0},{50,50} });
		Renderer->SetImageCuttingTransform({ {0,0}, {50, 50} });
	}
}
void ABomb::Tick(float _DeltaTime)
{
	AddActorLocation(Dir * Speed * _DeltaTime);

}

