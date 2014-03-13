#include "Color.h"

const Color Color::Yellow = Color(0xff, 0xee, 0x00);
Color::Color()
{
}
Color::Color(uint8_t red, uint8_t green, uint8_t blue) :
		r(red), g(green), b(blue) 
{
}