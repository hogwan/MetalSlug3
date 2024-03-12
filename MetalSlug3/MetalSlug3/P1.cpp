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
