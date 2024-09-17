
class Semaforo {
  public:
    enum stateLED {
      INITIAL,
      RED,
      GREEN,
      YELLOW,
    };
    
    int green, red, yellow;
    unsigned long timeLate;
    stateLED stateActual;

    Semaforo(int g, int r, int y) {
      green = g;
      red = r;
      yellow = y;
      stateActual = INITIAL;
      pinMode(green, OUTPUT);
      pinMode(red, OUTPUT);
      pinMode(yellow, OUTPUT);
    }

    void turnOn() {
      if (stateActual == INITIAL) {
        stateActual = GREEN;
        timeLate = millis();
      } else if (stateActual == GREEN) {
        if (millis() - timeLate >= 2000) {
          stateActual = YELLOW;
          timeLate = millis();
        }
      } else if (stateActual == YELLOW) {
        if (millis() - timeLate >= 1000) {
          stateActual = RED; 
          timeLate = millis();
        }
      } else if (stateActual == RED) {
        if (millis() - timeLate >= 2000) {
          stateActual = INITIAL;
          timeLate = millis();
        }
      }

      switch (stateActual) {
        case GREEN:
          changeLed(1, 0, 0);
          break;
        case YELLOW:
          changeLed(0, 0, 1);
          break;
        case RED:
          changeLed(0, 1, 0);
          break;
      }
    }

    void turnOff() {
      changeLed(0, 0, 0);
      stateActual == INITIAL;
    }

  private:
    void changeLed(int g, int r, int y) {
      digitalWrite(green, g);
      digitalWrite(red, r);
      digitalWrite(yellow, y);
    }
};

class StateButton {
  public:
    int pinButton;
    bool clickButton;
    bool stateButton;
    bool stt;

    StateButton(int pin) : pinButton(pin) {
      pinMode(pinButton, INPUT_PULLUP);
      clickButton = false;
      stateButton = false;
      stt = false;
    }

    bool state() {
      bool button = digitalRead(pinButton);

      if (button == LOW) {
        delay(50);
        clickButton = true;
        stateButton = digitalRead(pinButton);
      } else if (stateButton == HIGH && clickButton == true) {
        stt = !stt;
        clickButton = false;
      }

      return stt;
    }
};

StateButton btn(13);
Semaforo smf(12, 10, 11);

void setup() {
}

void loop() {
  if (btn.state()) {
    smf.turnOn();
  } else {
    smf.turnOff();
  }
}
