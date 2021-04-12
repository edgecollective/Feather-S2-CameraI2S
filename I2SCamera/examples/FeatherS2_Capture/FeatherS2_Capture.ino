#include "OV7670.h"

#include "BMP.h"

const int SIOD = 21; //SDA
const int SIOC = 22; //SCL

const int VSYNC = 34;
const int HREF = 35;

const int XCLK = 32;
const int PCLK = 33;

const int D0 = 27;
const int D1 = 17;
const int D2 = 16;
const int D3 = 15;
const int D4 = 14;
const int D5 = 13;
const int D6 = 12;
const int D7 = 4;

OV7670 *camera;

unsigned char bmpHeader[BMP::headerSize];


void setup() 
{
  Serial.begin(115200);

  //camera setup
  camera = new OV7670(OV7670::Mode::QQVGA_RGB565, 
                      SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, 
                      D0, D1, D2, D3, D4, D5, D6, D7);
                      
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);

}

void loop()
{
  camera->oneFrame();
  Serial.write(bmpHeader, BMP::headerSize);
  Serial.write(camera->frame, camera->xres * camera->yres * 2);
}
