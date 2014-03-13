#ifndef COLOR_H
#define COLOR_H

#include <cstdint> // std::uint8_t

using std::uint8_t;

class Color
{
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;

public:
	static const Color Yellow;

	Color() ;// no need to do anything, members are zero-initialized

	Color(uint8_t red, uint8_t green, uint8_t blue) ;
};

#endif // COLOR_H
