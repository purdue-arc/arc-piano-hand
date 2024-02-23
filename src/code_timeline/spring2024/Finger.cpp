
class Finger {
private: 
    int angle_rest {};
    int angle_down {};
    int dt {200};
    const Servo servo;

    void moveDown(int hold) {
        servo.write(this->angle_down);
        delay(hold);
    }

    void moveUp() {
        servo.write(this->angle_rest);
    }

public:
    Finger(int pin, int angle_down, int angle_rest = 60) {
        this->angle_down = angle_down;
        this->angle_rest = angle_rest;
        this->servo.attach(pin);
    }

    void move(int hold=100) {
        moveDown(hold);
        moveUp();
    }
}