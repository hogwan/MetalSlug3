#include "MetalSlug3Core.h"
#include "CharacterSelect.h"
#include "PlayLevel.h"
#include "TestLevel.h"
#include <EngineCore\EngineResourcesManager.h>

MetalSlug3Core::MetalSlug3Core()
{
}

MetalSlug3Core::~MetalSlug3Core()
{
}

void MetalSlug3Core::BeginPlay()
{
	int Value = 0;
	__int64 Address = reinterpret_cast<__int64>(&Value);
	srand(Address);

	// "Title Level" + "을 만들다가 에러가 났습니다";
	MainWindow.SetWindowScale({ 800,600 });
	CreateLevel<CharacterSelect>("CharacterSelect");
	CreateLevel<PlayLevel>("Play");
	//CreateLevel<TestLevel>("Test");

	ChangeLevel("Play");
	
}

void MetalSlug3Core::Tick(float _DeltaTime)
{
	// 플레이어 움직여야 한다.
}

void MetalSlug3Core::End()
{
}