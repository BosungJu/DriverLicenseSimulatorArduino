#pragma once

enum class PinType {
	// 버튼 입력 핀
	LeftTurnSignal = 2,    // 좌측 방향지시등
	RightTurnSignal = 3,   // 우측 방향지시등
	EngineButton = 4,      // 시동 버튼
	EmergencyButton = 5,   // 비상등
	FrontLightButton = 6,  // 전조등
	HighBeamButton = 7,    // 상향등
	WiperButton = 8,       // 와이퍼

	// LED 출력 핀
	EmergencyLed = 9,      // 비상등 LED
	EngineLed = 10         // 시동 LED
};

// PinType 값을 Arduino 핀 번호(int)로 변환
constexpr int toPin(PinType pin) {
	return static_cast<int>(pin);
}