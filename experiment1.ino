const byte LED1 = 6;
const byte LED2 = 7;
const byte LED3 = 8;
const byte LED4 = 9;
const byte LED5 = 10;
const byte LED6 = 11;
const byte LED7 = 12;
const byte LED8 = 13;

const byte SWITCH1 = 5;
const byte SWITCH2 = 3;
const byte SWITCH3 = 4;
const byte STOP_SWITCH = 2;

boolean SWITCH1_State = false;
boolean SWITCH2_State = false;
boolean SWITCH3_State = false;
boolean STOP_SWITCH_State = false;
boolean oldSWITCH1_State = false;
boolean oldSWITCH2_State = false;
boolean oldSWITCH3_State = false;
boolean oldSTOP_SWITCH_State = false;

enum Pattern { NONE, PATTERN1, PATTERN2, PATTERN3 };
Pattern currentPattern = NONE;

void setup() {
    pinMode(SWITCH1, INPUT);
    pinMode(SWITCH2, INPUT);
    pinMode(SWITCH3, INPUT);
    pinMode(STOP_SWITCH, INPUT);

    for (int i = LED1; i <= LED8; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }

    Serial.begin(9600);
    Serial.println(" ");
    randomSeed(analogRead(0));
}

void loop() {
    checkSwitch();
    if (currentPattern != NONE) {
        executePattern();
    }
}

void checkSwitch() {
    const unsigned long debounceDelay = 50;
    static unsigned long lastDebounceTime = 0;

    boolean currentSWITCH1_State = digitalRead(SWITCH1);
    boolean currentSWITCH2_State = digitalRead(SWITCH2);
    boolean currentSWITCH3_State = digitalRead(SWITCH3);
    boolean currentSTOP_SWITCH_State = digitalRead(STOP_SWITCH);

    unsigned long currentTime = millis();
    if ((currentTime - lastDebounceTime) > debounceDelay) {
        if (currentSWITCH1_State != oldSWITCH1_State) {
            if (currentSWITCH1_State == HIGH) {
                currentPattern = PATTERN1;
                Serial.println("Pattern 1");
            }
            oldSWITCH1_State = currentSWITCH1_State;
        }

        if (currentSWITCH2_State != oldSWITCH2_State) {
            if (currentSWITCH2_State == HIGH) {
                currentPattern = PATTERN2;
                Serial.println("Pattern 2");
            }
            oldSWITCH2_State = currentSWITCH2_State;
        }

        if (currentSWITCH3_State != oldSWITCH3_State) {
            if (currentSWITCH3_State == HIGH) {
                currentPattern = PATTERN3;
                Serial.println("Pattern 3");
            }
            oldSWITCH3_State = currentSWITCH3_State;
        }

        if (currentSTOP_SWITCH_State != oldSTOP_SWITCH_State) {
            if (currentSTOP_SWITCH_State == HIGH) {
                currentPattern = NONE;
                for (int i = LED1; i <= LED8; i++) {
                    digitalWrite(i, LOW);
                }
                Serial.println("All Lights Off");
            }
            oldSTOP_SWITCH_State = currentSTOP_SWITCH_State;
        }

        lastDebounceTime = currentTime;
    }
}

void executePattern() {
    switch (currentPattern) {
        case PATTERN1:
            pattern1();
            break;
        case PATTERN2:
            pattern2();
            break;
        case PATTERN3:
            pattern3();
            break;
        default:
            break;
    }
}

void pattern1() {
    const int beatDelay4_4 = 550;

    for (int repeat = 0; repeat < 4; repeat++) {
        if (checkStop()) return;

        for (int i = 0; i < 8; i++) {
            int randomLED = random(LED1, LED8 + 1);
            digitalWrite(randomLED, HIGH);
            delay(beatDelay4_4 / 4);
            digitalWrite(randomLED, LOW);
        }

        delay(beatDelay4_4 / 4);
    }

    const int bassDelay = beatDelay4_4 / 2;
    const int snareDelay = beatDelay4_4 / 4;

    for (int repeat = 0; repeat < 4; repeat++) {
        if (checkStop()) return;

        for (int i = LED1; i <= LED4; i++) {
            digitalWrite(i, HIGH);
        }
        delay(bassDelay);
        for (int i = LED1; i <= LED4; i++) {
            digitalWrite(i, LOW);
        }

        if (checkStop()) return;

        for (int i = LED5; i <= LED8; i++) {
            digitalWrite(i, HIGH);
        }
        delay(snareDelay);
        for (int i = LED5; i <= LED8; i++) {
            digitalWrite(i, LOW);
        }

        delay(beatDelay4_4 / 4);
    }

    for (int i = 0; i < 2; i++) {
        if (checkStop()) return;

        for (int intensity = 0; intensity <= 255; intensity += 100) {
            for (int j = LED1; j <= LED8; j++) {
                analogWrite(j, intensity);
            }
            delay(beatDelay4_4 / 4);
        }

        for (int intensity = 255; intensity >= 0; intensity -= 100) {
            for (int j = LED1; j <= LED8; j++) {
                analogWrite(j, intensity);
            }
            delay(beatDelay4_4 / 4);
        }
    }
}

void pattern2() {
    for (int repeat = 0; repeat < 2; repeat++) {
        if (checkStop()) return;

        for (int i = 0; i < 4; i++) {
            if (checkStop()) return;

            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            delay(300);
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);

            if (checkStop()) return;

            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            delay(300);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);

            if (checkStop()) return;

            digitalWrite(LED5, HIGH);
            digitalWrite(LED6, HIGH);
            delay(300);
            digitalWrite(LED5, LOW);
            digitalWrite(LED6, LOW);

            for (int j = 0; j < 10; j++) {
                if (checkStop()) return;

                int led = random(LED1, LED8 + 1);
                digitalWrite(led, HIGH);
                delay(45);
                digitalWrite(led, LOW);
            }

            if (checkStop()) return;

            delay(20);
        }
    }

    for (int i = 0; i < 4; i++) {
        if (checkStop()) return;

        digitalWrite(LED1, HIGH);
        digitalWrite(LED8, HIGH);
        delay(310);
        digitalWrite(LED1, LOW);
        digitalWrite(LED8, LOW);

        if (checkStop()) return;

        digitalWrite(LED2, HIGH);
        digitalWrite(LED7, HIGH);
        delay(310);
        digitalWrite(LED2, LOW);
        digitalWrite(LED7, LOW);

        if (checkStop()) return;

        digitalWrite(LED3, HIGH);
        digitalWrite(LED6, HIGH);
        delay(300);
        digitalWrite(LED3, LOW);
        digitalWrite(LED6, LOW);

        if (checkStop()) return;

        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, HIGH);
        delay(330);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);

        if (checkStop()) return;

        delay(20);
    }

    for (int i = 0; i < 4; i++) {
        if (checkStop()) return;

        digitalWrite(LED1, HIGH);
        digitalWrite(LED8, HIGH);
        delay(350);
        digitalWrite(LED1, LOW);
        digitalWrite(LED8, LOW);

        if (checkStop()) return;

        digitalWrite(LED2, HIGH);
        digitalWrite(LED7, HIGH);
        delay(350);
        digitalWrite(LED2, LOW);
        digitalWrite(LED7, LOW);

        if (checkStop()) return;

        digitalWrite(LED3, HIGH);
        digitalWrite(LED6, HIGH);
        delay(340);
        digitalWrite(LED3, LOW);
        digitalWrite(LED6, LOW);

        if (checkStop()) return;

        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, HIGH);
        delay(370);
        digitalWrite(LED4, LOW);
        digitalWrite(LED5, LOW);

        if (checkStop()) return;

        delay(20);
    }
}

void repeatFirstPartThreeTimes() {
    for (int k = 0; k < 3; k++) {
        if (checkStop()) return;

        for (int i = 0; i < 2; i++) {
            if (checkStop()) return;

            digitalWrite(LED1, HIGH);
            digitalWrite(LED2, HIGH);
            delay(300);
            digitalWrite(LED1, LOW);
            digitalWrite(LED2, LOW);

            if (checkStop()) return;

            digitalWrite(LED3, HIGH);
            digitalWrite(LED4, HIGH);
            delay(300);
            digitalWrite(LED3, LOW);
            digitalWrite(LED4, LOW);

            if (checkStop()) return;

            digitalWrite(LED5, HIGH);
            digitalWrite(LED6, HIGH);
            delay(300);
            digitalWrite(LED5, LOW);
            digitalWrite(LED6, LOW);

            for (int j = 0; j < 10; j++) {
                if (checkStop()) return;

                int led = random(LED1, LED8 + 1);
                digitalWrite(led, HIGH);
                delay(45);
                digitalWrite(led, LOW);
            }

            if (checkStop()) return;

            delay(20);
        }
    }

    for (int cycle = 0; cycle < 4; cycle++) {
        if (checkStop()) return;

        digitalWrite(LED1, HIGH);
        digitalWrite(LED2, HIGH);
        digitalWrite(LED3, HIGH);
        digitalWrite(LED4, HIGH);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
        digitalWrite(LED7, LOW);
        digitalWrite(LED8, LOW);
        delay(300);
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, LOW);
        digitalWrite(LED4, LOW);

        if (checkStop()) return;

        digitalWrite(LED5, HIGH);
        digitalWrite(LED6, HIGH);
        digitalWrite(LED7, HIGH);
        digitalWrite(LED8, HIGH);
        delay(300);
        digitalWrite(LED5, LOW);
        digitalWrite(LED6, LOW);
        digitalWrite(LED7, LOW);
        digitalWrite(LED8, LOW);

        if (checkStop()) return;
    }
}

void pattern3() {
    const int tempoDelay = 170;
    const int tempoDelay1 = 135;
    const int tempoDelay2 = 200;
    const int reverseDelay = 2100;
    const int reverseDelay2 = 400;
    const int longDelay = 2900;
    const int mediumDelay = 2100;
    const int fadeDelay = 18;
    const int fadeSteps = 150;
    const int fadeCycles = 4;

    for (int cycle = 0; cycle < 2; cycle++) {
        for (int round = 0; round < 3; round++) {
            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED1, HIGH);
                delay(tempoDelay1);
                digitalWrite(LED1, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED3, HIGH);
                delay(tempoDelay);
                digitalWrite(LED3, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED4, HIGH);
                delay(tempoDelay);
                digitalWrite(LED4, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED6, HIGH);
                digitalWrite(LED7, HIGH);
                delay(tempoDelay);
                digitalWrite(LED6, LOW);
                digitalWrite(LED7, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED5, HIGH);
                digitalWrite(LED7, HIGH);
                digitalWrite(LED8, HIGH);
                delay(tempoDelay1);
                digitalWrite(LED5, LOW);
                digitalWrite(LED7, LOW);
                digitalWrite(LED8, LOW);
            }
        }

        delay(reverseDelay);

        for (int round = 0; round < 3; round++) {
            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED5, HIGH);
                digitalWrite(LED6, HIGH);
                digitalWrite(LED7, HIGH);
                digitalWrite(LED8, HIGH);
                delay(tempoDelay1);
                digitalWrite(LED5, LOW);
                digitalWrite(LED6, LOW);
                digitalWrite(LED7, LOW);
                digitalWrite(LED8, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED4, HIGH);
                digitalWrite(LED6, HIGH);
                digitalWrite(LED7, HIGH);
                delay(tempoDelay1);
                digitalWrite(LED4, LOW);
                digitalWrite(LED6, LOW);
                digitalWrite(LED7, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED3, HIGH);
                digitalWrite(LED5, HIGH);
                delay(tempoDelay);
                digitalWrite(LED3, LOW);
                digitalWrite(LED5, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED2, HIGH);
                delay(tempoDelay1);
                digitalWrite(LED2, LOW);
            }

            if (checkStop()) return;

            for (int i = 0; i < 2; i++) {
                digitalWrite(LED1, HIGH);
                digitalWrite(LED3, HIGH);
                delay(tempoDelay1);
                digitalWrite(LED1, LOW);
                digitalWrite(LED3, LOW);
            }

            delay(tempoDelay);
        }

        if (cycle == 0) {
            delay(mediumDelay);
        }
    }

    delay(reverseDelay2 + longDelay);

    for (int fadeCycle = 0; fadeCycle < fadeCycles; fadeCycle++) {
        for (int brightness = 0; brightness <= fadeSteps; brightness++) {
            analogWrite(LED4, brightness);
            analogWrite(LED5, brightness);
            analogWrite(LED6, brightness);
            delay(fadeDelay);
        }

        for (int brightness = fadeSteps; brightness >= 0; brightness--) {
            analogWrite(LED4, brightness);
            analogWrite(LED5, brightness);
            analogWrite(LED6, brightness);
            delay(fadeDelay);
        }
        delay(tempoDelay2);
    }
}

boolean checkStop() {
    boolean stopPressed = digitalRead(STOP_SWITCH);
    if (stopPressed) {
        for (int i = LED1; i <= LED8; i++) {
            digitalWrite(i, LOW);
        }
        return true;
    }
    return false;
}
