#include <Bounce2.h>
#include "PinType.hpp"  // 버튼 및 LED 핀 번호 정의

// 디바운싱 시간
const int DEBOUNCE_INTERVAL = 50;

// 유니티로 전송할 명령어 이름
const char* CMD_LEFT_TURN_SIGNAL_BUTTON  = "LeftTurnSignalButton";
const char* CMD_RIGHT_TURN_SIGNAL_BUTTON = "RightTurnSignalButton";
const char* CMD_ENGINE_BUTTON            = "EngineButton";
const char* CMD_EMERGENCY_BUTTON         = "EmergencyButton";
const char* CMD_FRONT_LIGHT_BUTTON       = "FrontLightButton";
const char* CMD_HIGH_BEAM_BUTTON         = "HighBeamButton";
const char* CMD_WIPER_BUTTON             = "WiperButton";

// 버튼 디바운싱 객체
Bounce bounceLeftTurnSignal  = Bounce();
Bounce bounceRightTurnSignal = Bounce();
Bounce bounceEngineButton    = Bounce();
Bounce bounceEmergencyButton = Bounce();
Bounce bounceFrontLight      = Bounce();
Bounce bounceHighBeam        = Bounce();
Bounce bounceWiper           = Bounce();

void setup() {
	Serial.begin(115200);

	// 버튼 입력 초기화
	initButton(
		bounceLeftTurnSignal,
		toPin(PinType::LeftTurnSignal)
	);

	initButton(
		bounceRightTurnSignal,
		toPin(PinType::RightTurnSignal)
	);

	initButton(
		bounceEngineButton,
		toPin(PinType::EngineButton)
	);

	initButton(
		bounceEmergencyButton,
		toPin(PinType::EmergencyButton)
	);

	initButton(
		bounceFrontLight,
		toPin(PinType::FrontLightButton)
	);

	initButton(
		bounceHighBeam,
		toPin(PinType::HighBeamButton)
	);

	initButton(
		bounceWiper,
		toPin(PinType::WiperButton)
	);

	// LED 출력 핀 초기화
	pinMode(toPin(PinType::EngineLed), OUTPUT);
	pinMode(toPin(PinType::EmergencyLed), OUTPUT);
}

void loop() {
	// 일반 버튼 상태 확인
	checkButtonState(
		bounceLeftTurnSignal,
		CMD_LEFT_TURN_SIGNAL_BUTTON
	);

	checkButtonState(
		bounceRightTurnSignal,
		CMD_RIGHT_TURN_SIGNAL_BUTTON
	);

	// 시동 버튼
	checkLockingButtonWithLed(
		bounceEngineButton,
		CMD_ENGINE_BUTTON,
		toPin(PinType::EngineLed)
	);

	// 비상등 버튼
	checkLockingButtonWithLed(
		bounceEmergencyButton,
		CMD_EMERGENCY_BUTTON,
		toPin(PinType::EmergencyLed)
	);

	checkButtonState(
		bounceFrontLight,
		CMD_FRONT_LIGHT_BUTTON
	);

	checkButtonState(
		bounceHighBeam,
		CMD_HIGH_BEAM_BUTTON
	);

	checkButtonState(
		bounceWiper,
		CMD_WIPER_BUTTON
	);
}

// 버튼 초기화
void initButton(Bounce &button, int pin) {
	button.attach(pin, INPUT_PULLUP);
	button.interval(DEBOUNCE_INTERVAL);
}

// 일반 버튼 및 스위치 상태 확인
// 상태가 변경되면 실제 상태를 유니티로 전송
void checkButtonState(Bounce &button, const char* command) {
	button.update();

	if (button.changed()) {
		int realState = (button.read() == LOW) ? 1 : 0;

		Serial.print(command);
		Serial.print(":");
		Serial.println(realState);
	}
}

// 락킹 토글 버튼 상태 확인
// 실제 버튼 상태를 읽어 LED 상태를 변경하고 유니티로 전송
void checkLockingButtonWithLed(
	Bounce &button,
	const char* command,
	int ledPin
) {
	button.update();

	if (button.changed()) {
		int realState = (button.read() == LOW) ? 1 : 0;

		digitalWrite(
			ledPin,
			realState ? HIGH : LOW
		);

		Serial.print(command);
		Serial.print(":");
		Serial.println(realState);
	}
}