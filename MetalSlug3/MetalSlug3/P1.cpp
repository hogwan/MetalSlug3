#include "P1.h"

P1::P1()
{
}

P1::~P1()
{
}

void P1::BeginPlay()
{
	Renderer = CreateImageRenderer(5);
	Renderer->SetTransform({ {130,150},{130,80} });
	Renderer->SetImage("P1.png");
}

void P1::Tick(float _DeltaTime)
{
	Acc += _DeltaTime;
	if (Acc > CoolTime)
	{
		Acc = 0.0f;
		++ColorNum;
	}

	int Color = ColorNum % 2;
	if (Color == 0)
	{
		Renderer->SetImage("P1.png");
	}
	else
	{
		Renderer->SetImage("P1_Yellow.png");
	}
}