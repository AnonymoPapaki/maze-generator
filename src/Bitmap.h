#ifndef BITMAP_H
#define BITMAP_H

#include <iostream>
#include <fstream>
#include "Color.h"

class Bitmap
{
    private:
        int height;
        int width;
        unsigned char* bitmap;
    public:
        Bitmap(int h, int w);
        ~Bitmap();
        unsigned char* get() {return bitmap;}
        bool isColor(int x, int y, Color* color);
        bool Add(int x, int y, Color* color);
        void createFile(std::string fileName);
        void print();
};
#endif // BITMAP_H