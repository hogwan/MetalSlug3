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

	// "Title Level" + "�� ����ٰ� ������ �����ϴ�";
	MainWindow.SetWindowScale({ 800,600 });
	CreateLevel<CharacterSelect>("CharacterSelect");
	CreateLevel<PlayLevel>("Play");
	//CreateLevel<TestLevel>("Test");

	ChangeLevel("Play");
	
}

void MetalSlug3Core::Tick(float _DeltaTime)
{
	// �÷��̾� �������� �Ѵ�.
}

void MetalSlug3Core::End()
{
}