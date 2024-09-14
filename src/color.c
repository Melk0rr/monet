#include "utils.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A function to create a new hex color : see color.h
hex *newHexColor(const unsigned char *hexStr)
{
  hex *newColor = malloc(sizeof(*newColor));
  int hexLen = strlen((char *)hexStr);

  if
  (
    (hexLen != 7 && strchr((char *)hexStr, '#')) || 
    (hexLen != 6 && !strchr((char *)hexStr, '#')) ||
    (strchr((char *)hexStr, '#') && ((hexStr[0] == '#') == 0))
  )
  {
    fprintf(stderr, "newHexColor::Invalid value provided !");
    return NULL;
  }

  // If the hex string contains '#' : skip it
  bool skipFirstChar = false;
  int i = 0;

  if (hexStr[0] == '#')
  {
    skipFirstChar = true;
    i = 1;
  }
  
  for (; i < hexLen; i++)
  {
    newColor->code[i - (skipFirstChar ? 1 : 0)] = hexStr[i];
  }
  newColor->code[hexLen - (skipFirstChar ? 1 : 0)] = '\0';

  return newColor;
}

// A function to create a new RGB color : see color.h
rgb *newRGBColor(const unsigned char r, const unsigned char g, const unsigned char b)
{
  rgb *newColor = malloc(sizeof(*newColor));

  if (!checkRGBValue(r) || !checkRGBValue(g) || !checkRGBValue(b))
  {
    fprintf(stderr, "newRGBColor::Invalid RGB value provided !");
    return NULL;
  }
  
  newColor->red = r;
  newColor->green = g;
  newColor->blue = b;

  return newColor;
}

// A function to check if the given value is a valid RGB value : see color.h
bool checkRGBValue(const unsigned char value)
{
  bool check = true;
  if (value > 255 || value < 0)
  {
    check = false;
  }
  
  return check;
}

// A function to convert a hex color into an RGB one : see color.h
rgb *hex2RGB(hex *hex)
{
  unsigned long hexValue = strtoul((char *)hex->code, NULL, 16);
  return newRGBColor((hexValue >> 16) & 0xFF, (hexValue >> 8) & 0xFF, hexValue & 0xFF);
}

hex *rgb2Hex(rgb *rgb)
{
  unsigned char *hexStr = (unsigned char *)malloc(6);
  sprintf((char *)hexStr, "%02x%02x%02x", rgb->red, rgb->green, rgb->blue);
  
  return newHexColor(hexStr);
}

// Prints Hex color value : see color.h
void printHexValue(hex *hexColor)
{
  printf("#%s\n", hexColor->code);
}

// Prints RGB values : see color.h
void printRGBValues(rgb *rgbColor)
{
  printf("(%d,%d,%d)\n", rgbColor->red, rgbColor->green, rgbColor->blue);
}