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
	// "Title Level" + "�� ����ٰ� ������ �����ϴ�";
	MainWindow.SetWindowScale({ 800,600 });
	CreateLevel<CharacterSelect>("CharacterSelect");
	CreateLevel<PlayLevel>("Play");
	CreateLevel<TestLevel>("Test");

	ChangeLevel("Test");
	
}

void MetalSlug3Core::Tick(float _DeltaTime)
{
	// �÷��̾� �������� �Ѵ�.
}

void MetalSlug3Core::End()
{
}