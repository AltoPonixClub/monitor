static const uint8_t NAME2PIN[] = {A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15};
static const long baudRate = 9600;

String exampleGet = String("/get?pin=<name>");
String examplePost = String("/post?pin=(<name>,<value>), pin=(<name>,<value>)");

int request(String input) {
    String request = input.substring(0, input.indexOf('?'));
    if (request.equals("/get")) {
        return getRequest(input);
    }
    if (request.equals("/post")) {
        postRequest(input);
        return 200;
    }
}

int getRequest(String input) {
    String pinString = input.substring(input.indexOf('=') + 1);
    uint8_t pin;
    if (pinString.indexOf('A') >= 0) {
        pinString = pinString.substring(1);
        pin = NAME2PIN[pinString.toInt()];
        return analogRead(pin);
    }
    pin = pinString.toInt();
    return digitalRead(pin);
}

void postRequest(String input) {
    String pinString, valueString;
    uint8_t pin, value;
    bool analog;
    while (true) {
        pinString = input.substring(input.indexOf('(') + 1, input.indexOf(','));
        valueString = input.substring(input.indexOf(',') + 1, input.indexOf(')'));
        if (pinString.indexOf('A') >= 0) {
            pinString = pinString.substring(1);
            pin = NAME2PIN[pinString.toInt()];
            analog = true;
        } else {
            pin = pinString.toInt();
            analog = false;
        }
        if (valueString.indexOf("INPUT") >= 0) {
            pinMode(pin, INPUT);
        } else if (valueString.indexOf("OUTPUT") >= 0) {
            pinMode(pin, OUTPUT);
        } else {
            value = valueString.toInt();
            if (analog) {
                analogWrite(pin, value);
            } else {
                digitalWrite(pin, value);
            }
        }
        if (input.indexOf(')') + 2 <= input.length() - 1) {
            input = input.substring(input.indexOf(')') + 2);
        } else {
            break;
        }
    }
}

void setup() {
    // put your setup code here, to run once:
    Serial.begin(baudRate);
}

void loop() {
    // put your main code here, to run repeatedly:
    if (Serial.available() > 0) {
        String input = Serial.readString();
        Serial.println(request(input));
    }
    delay(30);
}
