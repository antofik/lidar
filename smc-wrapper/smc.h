// http://www.pololu.com/docs/0J44/6.7.3

#ifndef __smc__
#define __smc__

#include <iostream>
#include <string>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

struct SMCException : public std::exception
{
    std::string s;
    SMCException(std::string ss) : s(ss) {}
    ~SMCException() throw () {}
    const char* what() const throw() { return s.c_str(); }
};

class SMC {

private:
    const char* _device;
    int         _fd;

public:

    SMC(const char* dev) : _device(dev) {
        _fd = open(_device, O_RDWR | O_NOCTTY);
        if (_fd == -1) {
            perror(_device);
            throw SMCException("Invalid Device");
        }
    }
    ~SMC() { close(_fd); }

    int smcGetVariable(unsigned char variableId);
	int smcGetTargetSpeed();
    int smcGetErrorStatus();
    int smcExitSafeStart();
    int smcSetTargetSpeed(int speed);
};

#endif
