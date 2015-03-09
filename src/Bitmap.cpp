#include "Bitmap.h"

Bitmap::Bitmap(int h, int w)
{
    height = h;
    width = w;

    int totalSize = height*width*3;

    bitmap = new unsigned char[totalSize];

    for(int x = 0; x < totalSize; x++)
    {
        bitmap[x] = 0x00;
    }
}

Bitmap::~Bitmap()
{
    delete[] bitmap;
}

bool Bitmap::isColor(int x, int y, Color* color)
{
	if(x < 0 || y < 0 || x >= width || y >= height)
		return false;

    int pos = 3*(width*y + x);

    return   bitmap[pos] == color->b &&
             bitmap[pos+1] == color->g &&
             bitmap[pos+2] == color->r;
}

bool Bitmap::Add(int x, int y, Color* color)
{
	if(x < 0 || y < 0 || x >= width || y >= height)
		return false;

   int pos = 3*(width*y + x);

   bitmap[pos] = color->b;
   bitmap[pos+1] = color->g;
   bitmap[pos+2] = color->r;

   return true;
}

void Bitmap::print()
{
    for(int x = 0; x < width*height*3; x++)
    {
        if(bitmap[x] == 0x00) std::cout << '0';
        else std::cout << 'F';
        //std::cout << bitmap[x];
        if((x+1) % 3 == 0) std::cout << '|';
        if(x % width == (width - 1))
            std::cout << std::endl;
    }
}

void Bitmap::createFile(std::string fileName)
{
    using namespace std;

    struct bmp_header
    {
           uint32_t size_of_file;
		   uint32_t reserve;
		   uint32_t offset_of_pixle_data;
		   uint32_t size_of_header;
		   uint32_t width;
		   uint32_t height;
		   uint32_t num_of_colour_plane : 16;
		   uint32_t num_of_bit_per_pix : 16;
		   uint32_t compression;
		   uint32_t size_of_pix_data;
		   uint32_t h_resolution;
		   uint32_t v_resolution;
		   uint32_t num_of_colour_in_palette;
		   uint32_t important_colours;

    }
    HEADER;

    char padding = 0x00;
    short BM = 0x4d42;

    HEADER.size_of_file =  sizeof(HEADER) + sizeof(bitmap) + sizeof(padding) * height + 2;
    HEADER.reserve = 0000;
    HEADER.offset_of_pixle_data = 54;
    HEADER.size_of_header = 40;
    HEADER.width = width;
    HEADER.height = height;
    HEADER.num_of_colour_plane = 1;
    HEADER.num_of_bit_per_pix = 24;
    HEADER.compression = 0;
    HEADER.size_of_pix_data = sizeof(bitmap) + sizeof(padding) * height;
    HEADER.h_resolution = 2835;
    HEADER.v_resolution = 2835;
    HEADER.num_of_colour_in_palette = 0;
    HEADER.important_colours = 0;

    // write BMP Header ////////////////////////////////////////////////////////////////
    ofstream file;
    file.open (fileName, ios::out | ios::trunc | ios::binary);
    file.write ((char*)(&BM), 2);
    file.write ((char*)(&HEADER), sizeof(HEADER));
    ////////////////////////////////////////////////////////////////////////////////////

    // write BMP data //////////////////////////////////////////////////////////////////
    //file.write ((char*)(&bitmap[0]),1);
    int position = width * height * 3;
    while (position != 0)
    {
          for (int n = 0; n != width * 3; n++)
          {
              file.write ((char*)(&bitmap[position - width * 3 + n]), 1);
          }

          int paddcount = width - ((int)(width / 4))*4;

          for(int x = 0; x < paddcount; x++)
            file.write ((char*)(&padding), 1);


          position = position - width * 3;
    }

    file.close();
}