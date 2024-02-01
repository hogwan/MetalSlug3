#include "MetalSlug3Core.h"
#include "StartLevel.h"
#include "PlayLevel.h"
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
	CreateLevel<StartLevel>("StartLevel");
	CreateLevel<PlayLevel>("PlayLevel");

	ChangeLevel("PlayLevel");

	
}

void MetalSlug3Core::Tick(float _DeltaTime)
{
	// �÷��̾� �������� �Ѵ�.
}

void MetalSlug3Core::End()
{
}