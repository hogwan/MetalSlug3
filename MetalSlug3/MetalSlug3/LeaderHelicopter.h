#pragma once
class LeaderHelicopter
{
public:
	// constructor destructor
	LeaderHelicopter();
	~LeaderHelicopter();

	// delete Function
	LeaderHelicopter(const LeaderHelicopter& _Other) = delete;
	LeaderHelicopter(LeaderHelicopter&& _Other) noexcept = delete;
	LeaderHelicopter& operator=(const LeaderHelicopter& _Other) = delete;
	LeaderHelicopter& operator=(LeaderHelicopter&& _Other) = delete;
};

