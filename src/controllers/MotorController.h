class MotorController {
  private:
    int pinCW;
    int pinCCW;

  public:
    MotorController(int cwPin, int ccwPin) {
      pinCW = cwPin;
      pinCCW = ccwPin;
      pinMode(pinCW, OUTPUT);
      pinMode(pinCCW, OUTPUT);
      stop();
    }

    void forward() {
      analogWrite(pinCW, 255);
      analogWrite(pinCCW, 0);
    }

    void backward() {
      analogWrite(pinCW, 0);
      analogWrite(pinCCW, 255);
    }

    void stop() {
      analogWrite(pinCW, 0);
      analogWrite(pinCCW, 0);
    }
};