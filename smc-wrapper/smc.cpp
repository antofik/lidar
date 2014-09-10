// http://www.pololu.com/docs/0J44/6.7.3
 
#include "smc.h"
 
#define SERIAL_ERROR -9999
 
// Reads a variable from the SMC and returns it as number between 0 and 65535.
// Returns SERIAL_ERROR if there was an error.
// The 'variableId' argument must be one of IDs listed in the
// "Controller Variables" section of the user's guide.
// For variables that are actually signed, additional processing is required
// (see smcGetTargetSpeed for an example).
int SMC::smcGetVariable(unsigned char variableId)
{
  unsigned char command[] = {0xA1, variableId};
  if(write(_fd, &command, sizeof(command)) == -1)
  {
    perror("error writing");
    return SERIAL_ERROR;
  }
 
  unsigned char response[2];
  if(read(_fd,response,2) != 2)
  {
    perror("error reading");
    return SERIAL_ERROR;
  }
 
  return response[0] + 256*response[1];
}
 
// Returns the target speed (-3200 to 3200).
// Returns SERIAL_ERROR if there is an error.
int SMC::smcGetTargetSpeed()
{
  int val = smcGetVariable(20);
  return val == SERIAL_ERROR ? SERIAL_ERROR : (signed short)val;
}
 
// Returns a number where each bit represents a different error, and the
// bit is 1 if the error is currently active.
// See the user's guide for definitions of the different error bits.
// Returns SERIAL_ERROR if there is an error.
int SMC::smcGetErrorStatus()
{
  return smcGetVariable(0);
}
 
// Sends the Exit Safe Start command, which is required to drive the motor.
// Returns 0 if successful, SERIAL_ERROR if there was an error sending.
int SMC::smcExitSafeStart()
{
  const unsigned char command = 0x83;
  if (write(_fd, &command, 1) == -1)
  {
    perror("error writing");
    return SERIAL_ERROR;
  }
  return 0;
}
 
// Sets the SMC's target speed (-3200 to 3200).
// Returns 0 if successful, SERIAL_ERROR if there was an error sending.
int SMC::smcSetTargetSpeed(int speed)
{
  unsigned char command[3];
 
  if (speed < 0)
  {
    command[0] = 0x86; // Motor Reverse
    speed = -speed;
  }
  else
  {
    command[0] = 0x85; // Motor Forward
  }
  command[1] = speed & 0x1F;
  command[2] = speed >> 5 & 0x7F;
 
  if (write(_fd, command, sizeof(command)) == -1)
  {
    perror("error writing");
    return SERIAL_ERROR;
  }
  return 0;
}
 
