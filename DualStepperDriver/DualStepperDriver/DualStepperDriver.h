#include <arduino.h> 

class DualStepperDriver{
    private:
        int STEP1, STEP2, SLEEP1, SLEEP2, DIR1, DIR2;
        int d1, d2; //clockwise=1, counterclockwise=-1
    public:

        //default constructor
        DualStepperDriver();
        
        //initializes pin locations 
        DualStepperDriver(int STEP1, int DIR1, int SLEEP1, int STEP2, int DIR2, int SLEEP2);
        
        //advances stepper one by sC1 and stepper two by sC2
        //motor must not be in SLEEP mode
        void Advance(int sC1, int sC2);

        //if sX, sleeps stepper X
        void Sleep(int s1, int s2);

        //if wX, wakes stepper X
        void Wake(int w1, int w2);

        //sets current direction of motor
        void SetDirection(int d1, int d2);

        //if cX, flips current direction of stepper X
        void ChangeDirection(int c1, int c2);
};

