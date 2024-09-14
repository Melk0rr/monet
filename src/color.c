#include "utils.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

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
rgb *newRGBColor(const int r, const int g, const int b)
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

// A function to create a new HSL tuple : see color.h
hsl *newHSLTuple(const float h, const float s, const float l)
{
  hsl *newHSL = malloc(sizeof(*newHSL));
  
  if (!checkRGBValue(h) || !checkSLValue(s) || !checkSLValue(l))
  {
    fprintf(stderr, "newHSLTuple::Invalid HSL value provided !");
    return NULL;
  }
  
  newHSL->hue = h;
  newHSL->saturation = s;
  newHSL->lightness = l;
  
  return newHSL;
}

// A function to check if the given value is a valid RGB value : see color.h
bool checkRGBValue(const float value)
{
  bool check = false;
  if (value >= 0 && value <= 255)
  {
    check = true;
  }
  
  return check;
}

// A function to check if the given Saturation / Lightness value are valid : see color.h
bool checkSLValue(const float value)
{
  bool check = false;
  if (value >= 0 && value <= 1)
  {
    check = true;
  }
  
  return check;
}

float *rgbPercentages(rgb *rgb)
{
  float *perc = malloc(3 * sizeof(*perc));

  perc[0] = (float)rgb->red / 255;
  perc[1] = (float)rgb->green / 255;
  perc[2] = (float)rgb->blue / 255;
  
  return perc;
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

// A function to get HSL values from RGB
hsl *rgb2HSL(rgb *rgb)
{
  float *perc = rgbPercentages(rgb);

  float redPerc = perc[0];
  float greenPerc = perc[1];
  float bluePerc = perc[2];

  float minRGB = MIN(MIN(redPerc, greenPerc), bluePerc);
  float maxRGB = MAX(MAX(redPerc, greenPerc), bluePerc);
  
  // Lightness
  float l = (minRGB + maxRGB) / 2;

  // Saturation
  float s;
  if (minRGB == maxRGB)
  {
    s = 0;

  } else if (l < 0.5) {
    s = (maxRGB - minRGB) / (maxRGB + minRGB);

  } else {
    s = (maxRGB - minRGB) / (2 - maxRGB - minRGB);
  }
  
  // Hue
  float h;
  if (s == 0)
  {
    h = 0;

  } else if (redPerc >= MAX(greenPerc, bluePerc)) {
    h = (greenPerc - bluePerc) / (maxRGB - minRGB);
  
  } else if (greenPerc >= MAX(redPerc, bluePerc)) {
    h = 2 + (bluePerc - redPerc) / (maxRGB - minRGB);
  
  } else {
    h = 4 + (redPerc - greenPerc) / (maxRGB - minRGB);
  }
    
  h *= 60;
  
  if (h < 0)
  {
    h += 360;

  }

  return newHSLTuple(h, s, l);
}

// A function to get RGB values from HSL
rgb *hsl2RGB(hsl *hsl)
{
  if (hsl->saturation == 0)
  {
    return newRGBColor(hsl->hue * 255, hsl->saturation * 255, hsl->lightness * 255);
  }
  
  float tmp1;
  if (hsl->lightness < 0.5)
  {
    tmp1 = hsl->lightness * (1 + hsl->saturation);
    
  } else {
    tmp1 = hsl->lightness + hsl->saturation - hsl->lightness * hsl->saturation;
  }
  
  float tmp2 = 2 * hsl->lightness - tmp1;
  float newHue = hsl->hue / 360;
  
  float tmpRed = newHue + .333;
  float tmpGreen = newHue;
  float tmpBlue = newHue - .333;
  
  float tmpArr[3] = { tmpRed, tmpGreen, tmpBlue };
  float rgb[3];
  
  for (int i = 0; i < 3; i++)
  {
    float tmpV = tmpArr[i];
    printf("%f\n", tmpV);
    
    if (tmpV < 0)
    {
      tmpV += 1;
    }

    if (tmpV > 1)
    {
      tmpV -= 1;
    }

    if ((6 * tmpV) < 1)
    {
      rgb[i] = tmp2 + (tmp1 - tmp2) * 6 * tmpV;

    } else {
      if ((2 * tmpV) < 1)
      {
        rgb[i] = tmp1;

      } else {
        if ((3 * tmpV) < 2)
        {
          rgb[i] = tmp2 + (tmp1 - tmp2) * (.666 - tmpV) * 6;

        } else {
          rgb[i] = tmp2;
        }
      }
    }
  }

  return newRGBColor(rgb[0] * 255 + 1, rgb[1] * 255 + 1, rgb[2] * 255);
}

// A function to max the given color saturation : see color.h
hex *maxSaturation(hex *baseColor)
{
  rgb *baseRGB = hex2RGB(baseColor);
  hsl *baseHSL = rgb2HSL(baseRGB);
  
  hsl *newHSL = newHSLTuple(baseHSL->hue, 1, baseHSL->lightness);
  rgb *newRGB = hsl2RGB(newHSL);
  
  return rgb2Hex(newRGB);
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

// Prints HSL values : see color.h
void printHSLValues(hsl *hslTuple)
{
  printf("(%f,%f,%f)\n", hslTuple->hue, hslTuple->saturation, hslTuple->lightness);
}