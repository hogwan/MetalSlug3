#include "CharacterSelect.h"
#include <EngineCore\EngineResourcesManager.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>
#include <EnginePlatform/EngineSound.h>
#include "MarcoPhoto.h"
#include "P1.h"
#include "Panel.h"
#include "ContentsHelper.h"

CharacterSelect::CharacterSelect()
{
}

CharacterSelect::~CharacterSelect()
{
}

void CharacterSelect::BeginPlay()
{
	UEngineDirectory NewPath;
	NewPath.MoveParent();
	NewPath.Move("MT3Resource");
	NewPath.Move("CharacterSelectScreen");

	std::list<UEngineFile> AllFileList = NewPath.AllFile({ ".png", ".bmp" }, true);

	for (UEngineFile& File : AllFileList)
	{
		std::string FullPath = File.GetFullPath();
		// �̱��� ���� ����� �Ϻη� GetInst�� ����ϰڽ��ϴ�.
		UEngineResourcesManager::GetInst().LoadImg(FullPath);
	}

	UEngineResourcesManager::GetInst().CuttingImage("MarcoSelectedAnim.png", 2, 1);
	UEngineResourcesManager::GetInst().CuttingImage("DoorEffect.png", 10, 1);
	UEngineResourcesManager::GetInst().CuttingImage("Marco_Idle.png", 10, 1);

	SpawnActor<Panel>();
	SpawnActor<P1>();
	SpawnActor<MarcoPhoto>();
	
	NewPath.Move("Sound");
	UEngineSound::Load(NewPath.AppendPath("BGM.ogg"));
	UEngineSound::Load(NewPath.AppendPath("Marco.mp3"));
	UEngineSound::Load(NewPath.AppendPath("Select.ogg"));
	UEngineSound::Load(NewPath.AppendPath("MS3_Title.ogg"));
}
