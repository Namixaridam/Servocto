
class servocto
{
  public:
    //initialize
    void begin();
    //no voltage output
    bool noOutput(bool state);
    //write in degrees
    void writeAngle(uint8_t servo, uint8_t angle);
    //write in microseconds
    void writeMicros(uint8_t servo, int microseconds);
  private:
    int _val_servos[8];
};
extern servocto servos;
