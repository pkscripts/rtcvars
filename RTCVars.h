#ifndef ___LarsHelperESP_h___
#define ___LarsHelperESP_h___

#include "Arduino.h"

#ifndef RTC_MAX_VARIABLES
  #define RTC_MAX_VARIABLES 32
#endif

#ifdef DEBUG    //Macros are usually in all capital letters.
#define DPRINT(...)    Serial.print(__VA_ARGS__)     //DPRINT is a macro, debug print
#define DPRINTLN(...)  Serial.println(__VA_ARGS__)   //DPRINTLN is a macro, debug print with new line
//#else
//#define DPRINT(...)     //now defines a blank line
//#define DPRINTLN(...)   //now defines a blank line
#endif


const static int RTC_OK                        = 0;
const static int RTC_ERROR_MAGIC_BYTES         = 1;
const static int RTC_ERROR_SIZE                = 2;
const static int RTC_ERROR_READING_FAILED      = 3;
const static int RTC_ERROR_CHECKSUM            = 4;
const static int RTC_ERROR_STATE_ID            = 5;
const static int RTC_ERROR_OTHER               = 99;
const static int RTC_STATE_ID_INVALID          = 255;


class RTCVars {
  public:
    RTCVars();
    bool registerVar(char *v);
    //bool registerVar(byte *v);
    bool registerVar(int *v);
    bool registerVar(long *v);
    bool registerVar(float *v);
    void debugOutputRTCVars();
    bool saveToRTC();
    bool loadFromRTC();
    int getFreeRTCMem();
    int getFreeRTCVars();
    int getStateID();
    int getStateIDFromRTC();
    void setStateID(int new_state_id);
    int getReadError();
  private:
    int _state_id;
    int _last_read_state_id;
    int _last_read_status;
    int _state_size;
    int _state_variables_counter;
    uintptr_t _state_variables_ptr[RTC_MAX_VARIABLES];
    int _state_variables_type[RTC_MAX_VARIABLES];
    const int _state_variable_size[6] = {0, sizeof(int), sizeof(long), sizeof(float), sizeof(int), sizeof(char)};
    bool _checkAndReserve(uintptr_t v, int type_of_var);
    bool _checkValidRTCData();
};

#endif
