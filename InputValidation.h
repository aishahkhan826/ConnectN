
#ifndef NCursesConnectN_INPUTVALIDATION_H
#define NCursesConnectN_INPUTVALIDATION_H
#include <stdbool.h>
bool isValidFormat(const int numArgsRead, const int numArgsNeed);
bool isInRange(int value, int lowerBound, int uppderBound);

#endif //NCursesConnectN_INPUTVALIDATION_H
