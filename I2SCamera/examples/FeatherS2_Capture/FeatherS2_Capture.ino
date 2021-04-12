#include "OV7670.h"

#include "BMP.h"

//These pins should only work with the UM FeatherS2 board
// NOTE: - on linux refer to ~/Arduino/hardware/espressif/esp32/variants/um_feather_s2/pins_arduino.h
//       - when in doubt use the IO# on the official reference card pinout diagram 
// connect: camera "3.3V"  to Feather  "3V3" (LDO 1)  FIXME maybe LDO 2 is better for low power apps, turns of while deep sleeping
//          camera "RESET" to Feather "EN"
//          camera "PDWN"  is unused
// the remainder of pins as follows...
// lib. pin name, Arduino Pin, "Camera board label" 
const int SIOD = SDA; //IO9 "SDA"
const int SIOC = SCL; //IO8 "SCL"

//the integers all name IO# pins
const int VSYNC = 33; //"VS"
const int HREF  = 38; //"HS"


const int XCLK = 1;   //"MCLK"
const int PCLK = 3;   //"PCLK"

const int D0 = 7;
const int D1 = 10;
const int D2 = 11;
const int D3 = 5;
const int D4 = 6;
const int D5 = 12;
const int D6 = 14;
const int D7 = 18;

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
