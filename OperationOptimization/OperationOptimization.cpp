// OperationOptimization.cpp : Defines the entry point for the console application.
//
#include "stdafx.h";
#include <iostream>
#include "optimizationfunctions.h"
#include <assert.h>

using namespace std;

// Calculate a number of digits in an integer
uint32_t calculateNumberOfDigitsSlow(uint64_t v) {
	uint32_t result = 0;
	do {
		++result;
		v /= 10;
	} while (v);
	return result;

}

// Calculate a number of digits in an integer; faster variant.
uint32_t calculateNumberOfDigitsFast(uint64_t v){
	uint32_t result = 1;
	for (;;) {
		if (v < 10) return result;
		if (v < 100) return result + 1;
		if (v < 1000) return result + 2;
		if (v < 10000) return result + 3;
		// Skip ahead by 4 orders of magnitude
		v /= 10000U;
		result += 4;
	}
}
// Calculate a number of digits in an integer; fastest variant.
uint32_t calculateNumberOfDigitsBinary(uint64_t v) {
	if (v < 10) return 1;
	if (v < 100) return 2;
	if (v < 1000) return 3;
	if (v < 1000000000000) {
		if (v < 100000000) {
			if (v < 1000000) {
				if (v < 10000) return 4;
				return 5 + (v >= 100000);
			}
			return 7 + (v >= 10000000);
		}
		if (v < 10000000000) {
			return 9 + (v >= 1000000000);
		}
		return 11 + (v >= 100000000000);
	}
	return 12 + calculateNumberOfDigitsBinary(v / 1000000000000);

}

// Convert an integer to a string; slow version. Too many array writes.
uint32_t convertu64ToAsciiSlow(uint64_t v, char *dst) {
	// Write backwards.
	auto start = dst;
	do {
		*dst++ = '0' + (v % 10);
		v /= 10;
	} while (v != 0);
	const uint32_t result = dst - start;
	// Reverse in place.
	for (dst--; dst > start; start++, dst--) {
		std::iter_swap(dst, start);
	}
	return result;

}


// Convert an integer to a string; faster version. More computation, less array writes.
uint32_t convertu64ToAsciiFast(uint64_t v, char *const buffer){
	auto const result = calculateNumberOfDigitsFast(v);
	uint32_t pos = result - 1;
	while (v >= 10) {
		auto const q = v / 10;
		auto const r = static_cast<uint32_t>(v % 10);
			buffer[pos--] = '0' + r;
		v = q;
	}    assert(pos == 0); // Last digit is trivial to handle
	*buffer = static_cast<uint32_t>(v) + '0';
		return result;
}

// Convert an integer to a string; fastest version.
uint32_t convertu64ToAsciiFastest(uint64_t v, char *dst) {
	static const char digits[201] =
		"0001020304050607080910111213141516171819"
		"2021222324252627282930313233343536373839"
		"4041424344454647484950515253545556575859"
		"6061626364656667686970717273747576777879"
		"8081828384858687888990919293949596979899";
	uint32_t const length = calculateNumberOfDigitsBinary(v);
	uint32_t next = length - 1;
	while (v >= 100) {
		auto const i = (v % 100) * 2;
		v /= 100;
		dst[next] = digits[i + 1];
		dst[next - 1] = digits[i];
		next -= 2;
	}
	// Handle last 1-2 digits
	if (v < 10) {
		dst[next] = '0' + uint32_t(v);
	}
	else {
		auto i = uint32_t(v) * 2;
		dst[next] = digits[i + 1];
		dst[next - 1] = digits[i];
	}
	return length;

}


int _tmain(int argc, _TCHAR* argv[])
{
	uint32_t v = 54212545621;
	uint32_t s = calculateNumberOfDigitsSlow(v);
	uint32_t f = calculateNumberOfDigitsFast(v);
	uint32_t b = calculateNumberOfDigitsBinary(v);


	return 0;
}

