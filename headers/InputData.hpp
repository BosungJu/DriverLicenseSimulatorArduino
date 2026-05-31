#pragma once
enum class GearType {
	Reverse = -1,
	Neutral = 0,
	First = 1,
	Second = 2,
	Third = 3,
	Fourth = 4,
	Fifth = 5,
	Sixth = 6
};

enum class InputType {
	Clutch,
	Excel,
	Brake,
	
	Handle,
	
	SideBrake,

	Gear_R,
	Gear_N,
	Gear_1,
	Gear_2,
	Gear_3,
	Gear_4,
	Gear_5,
	Gear_6,

	EmergencyButton,
	FrontLightButton,
	RearLightButton,
	HighBeamButton,
	LowBeamButton,

	WiperButton,


};

// 매 프레임마다 입력되는 데이터로 인스턴스 만들어서 리턴하기. 렉걸리면 인스턴스 하나로 계속 업데이트해서 리턴하기. (메모리 낭비 방지)
class InputData {
public:
	float clutch;
	float excel;
	float brake;
	float handle;
	bool sideBrake;
	GearType gear;

	InputData() : clutch(0), excel(0), brake(0), handle(0), sideBrake(false), gear(GearType::Neutral) {}
	InputData(float clutch, float excel, float brake, float handle, bool sideBrake, GearType gear)
		: clutch(clutch), excel(excel), brake(brake), handle(handle), sideBrake(sideBrake), gear(gear) {}
};
