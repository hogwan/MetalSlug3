#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum MT3RenderOrder
{
	Map,
	Monster,
	Player,
	Projectile,
};

enum class EActorDir
{
	Left,
	Right,
};

enum class EGunType
{
	Pistol,
	Rifle,
};

enum class EPlayState
{
	None,
	CameraFreeMove,
	FreeMove,
	Idle,
	Move,
	Jump,
};

class UContentsHelper
{
public:
	static UWindowImage* ColMapImage;

private:
	UContentsHelper();
	~UContentsHelper();
};

