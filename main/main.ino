#include <Bounce2.h>

// 버튼 입력 핀
const int PIN_LEFT_TURN_SIGNAL   = 2;  // 좌측 방향지시등
const int PIN_RIGHT_TURN_SIGNAL  = 3;  // 우측 방향지시등
const int PIN_ENGINE_BUTTON      = 4;  // 시동 버튼
const int PIN_EMERGENCY_BUTTON   = 5;  // 비상등
const int PIN_FRONT_LIGHT_BUTTON = 6;  // 전조등
const int PIN_HIGH_BEAM_BUTTON   = 7;  // 상향등
const int PIN_WIPER_BUTTON       = 8;  // 와이퍼

// LED 출력 핀
const int PIN_ENGINE_LED    = 10;   // 시동 버튼 LED
const int PIN_EMERGENCY_LED = 9;  // 비상등 버튼 LED

const int DEBOUNCE_INTERVAL = 50;

// 유니티로 전송할 명령어 이름
const char* CMD_LEFT_TURN_SIGNAL_BUTTON  = "LeftTurnSignalButton";
const char* CMD_RIGHT_TURN_SIGNAL_BUTTON = "RightTurnSignalButton";
const char* CMD_ENGINE_BUTTON            = "EngineButton";
const char* CMD_EMERGENCY_BUTTON         = "EmergencyButton";
const char* CMD_FRONT_LIGHT_BUTTON       = "FrontLightButton";
const char* CMD_HIGH_BEAM_BUTTON         = "HighBeamButton";
const char* CMD_WIPER_BUTTON             = "WiperButton";

Bounce bounceLeftTurnSignal  = Bounce();
Bounce bounceRightTurnSignal = Bounce();
Bounce bounceEngineButton    = Bounce();
Bounce bounceEmergencyButton = Bounce();
Bounce bounceFrontLight      = Bounce();
Bounce bounceHighBeam        = Bounce();
Bounce bounceWiper           = Bounce();

void setup() {
  Serial.begin(115200);

  initButton(bounceLeftTurnSignal, PIN_LEFT_TURN_SIGNAL);
  initButton(bounceRightTurnSignal, PIN_RIGHT_TURN_SIGNAL);
  initButton(bounceEngineButton, PIN_ENGINE_BUTTON);
  initButton(bounceEmergencyButton, PIN_EMERGENCY_BUTTON);
  initButton(bounceFrontLight, PIN_FRONT_LIGHT_BUTTON);
  initButton(bounceHighBeam, PIN_HIGH_BEAM_BUTTON);
  initButton(bounceWiper, PIN_WIPER_BUTTON);

  pinMode(PIN_ENGINE_LED, OUTPUT);
  pinMode(PIN_EMERGENCY_LED, OUTPUT);

  // 전원 켰을 때 버튼이 이미 눌린 상태일 수도 있으므로 LED 상태를 실제 버튼 상태와 맞춤
  digitalWrite(PIN_ENGINE_LED, digitalRead(PIN_ENGINE_BUTTON) == LOW ? HIGH : LOW);
  digitalWrite(PIN_EMERGENCY_LED, digitalRead(PIN_EMERGENCY_BUTTON) == LOW ? HIGH : LOW);
}

void loop() {
  checkButtonState(bounceLeftTurnSignal, CMD_LEFT_TURN_SIGNAL_BUTTON);
  checkButtonState(bounceRightTurnSignal, CMD_RIGHT_TURN_SIGNAL_BUTTON);

  // 시동 버튼: 락킹 토글 버튼
  checkLockingButtonWithLed(bounceEngineButton, CMD_ENGINE_BUTTON, PIN_ENGINE_LED);

  // 비상등 버튼: 락킹 토글 버튼
  checkLockingButtonWithLed(bounceEmergencyButton, CMD_EMERGENCY_BUTTON, PIN_EMERGENCY_LED);

  checkButtonState(bounceFrontLight, CMD_FRONT_LIGHT_BUTTON);
  checkButtonState(bounceHighBeam, CMD_HIGH_BEAM_BUTTON);
  checkButtonState(bounceWiper, CMD_WIPER_BUTTON);
}

void initButton(Bounce &b, int pin) {
  b.attach(pin, INPUT_PULLUP);
  b.interval(DEBOUNCE_INTERVAL);
}

// 일반 버튼/스위치: 상태 변화가 생기면 실제 상태를 유니티로 전송
void checkButtonState(Bounce &b, const char* command) {
  b.update();

  if (b.changed()) {
    int realState = (b.read() == LOW) ? 1 : 0;

    Serial.print(command);
    Serial.print(":");
    Serial.println(realState);
  }
}

// 락킹 토글 버튼용: 실제 버튼 상태를 그대로 읽고 LED도 같은 상태로 제어
void checkLockingButtonWithLed(Bounce &b, const char* command, int ledPin) {
  b.update();

  if (b.changed()) {
    int realState = (b.read() == LOW) ? 1 : 0;

    digitalWrite(ledPin, realState ? HIGH : LOW);

    Serial.print(command);
    Serial.print(":");
    Serial.println(realState);
  }
}