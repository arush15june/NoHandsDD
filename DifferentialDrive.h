#ifndef DifferentialDrive_h
#define DifferentialDrive_h

#include "Arduino.h"

enum direction {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

struct DifferentialDrive {
    
private:
    int rightMotorEnable;
    int rightMotorDirF;
    int rightMotorDirB;
    
    int leftMotorEnable;
    int leftMotorDirF;
    int leftMotorDirB;

    int rightDefaultSpeed;
    int leftDefaultSpeed;
public:
    void forward(int, int);
    void backward(int, int);
    void left(int, int);
    void right(int, int);
    void stop();
}