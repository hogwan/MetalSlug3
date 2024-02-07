#pragma once
#include <EngineBase\EngineMath.h>
#include <EngineCore\EngineCore.h>
#include <EngineCore\ImageRenderer.h>

enum MT3RenderOrder
{
	Map,
	Monster,
	Projectile,
	ZombieArm,
	AllBody,
	LowerBody,
	UpperBody,

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
	HeavyMachineGun,
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
	Shoot,
	ForwardJumpShoot,
	Throw,
	KnifeAttack1,
	KnifeAttack2,
	AimNormalToUp,
	AimUpToNormal,
	AimUp,
	AimUpShoot,
	AimNormalToDown,
	AimDownToNormal,
	AimDownShoot,
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

