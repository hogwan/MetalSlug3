#include "MetalSlug3Core.h"
#include "StartLevel.h"
#include "PlayLevel.h"

MetalSlug3Core::MetalSlug3Core()
{
}

MetalSlug3Core::~MetalSlug3Core()
{
}

void MetalSlug3Core::BeginPlay()
{
	// "Title Level" + "을 만들다가 에러가 났습니다";

	CreateLevel<StartLevel>("StartLevel");
	CreateLevel<PlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");

}

void MetalSlug3Core::Tick(float _DeltaTime)
{
	// 플레이어 움직여야 한다.
}

void MetalSlug3Core::End()
{
}