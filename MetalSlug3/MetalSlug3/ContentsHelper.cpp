#include "ContentsHelper.h"
#include <EnginePlatform/EngineSound.h>

UWindowImage* UContentsHelper::ColMapImage = nullptr;
UWindowImage* UContentsHelper::CrouchColMapImage = nullptr;
AScreenCollision* UContentsHelper::ScreenCol = nullptr;
class Marco* UContentsHelper::Player = nullptr;
class CameraManager* UContentsHelper::CameraManager = nullptr;
class UEngineSoundPlayer UContentsHelper::BGMPlayer;
bool  UContentsHelper::GameEnd = false;
int UContentsHelper::Life = 2;
int UContentsHelper::Score = 0;

UContentsHelper::UContentsHelper()
{
}

UContentsHelper::~UContentsHelper()
{
}
