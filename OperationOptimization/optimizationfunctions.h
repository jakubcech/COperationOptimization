#include "stdafx.h"
#include <iostream>

using namespace std;

// Calculate a number of digits in an integer
uint32_t calculateNumberOfDigitsSlow(uint64_t v);
uint32_t calculateNumberOfDigitsFast(uint64_t v);
// Two digit cuts
uint32_t calculateNumberOfDigitsBinary(uint64_t v);

// Integer to String
uint32_t convertu64ToAsciiSlow(uint64_t v, char *dst);
uint32_t convertu64ToAsciiFast(uint64_t v, char *const buffer);
// Two digit cuts
uint32_t convertu64ToAsciiFastest(uint64_t v, char *dst);
