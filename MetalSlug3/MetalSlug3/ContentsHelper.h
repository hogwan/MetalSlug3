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

enum class UpperBodyState
{
	None,
	CameraFreeMove,
	FreeMove,
	Idle,
	Move,
	Jump,
	ForwardJump,
	AimUp,
	AimDown,
	AimNormalToUp,
	AimUpToNormal,
	Shoot,
	Throw,
};

enum class LowerBodyState
{
	None,
	Idle,
	Move,
	Jump,
	ForwardJump,
};

enum class AllBodyState
{
	None,
	Crouch_Idle,
	Crouch_Move,
	Crouch_Shoot,
	Crouch_Throw,

};

class UContentsHelper
{
public:
	static UWindowImage* ColMapImage;

private:
	UContentsHelper();
	~UContentsHelper();
};

