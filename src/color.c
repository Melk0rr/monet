#include "color.h"
#include "utils.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

// A function to create a new hex color : see color.h
hex *newHexColor(const unsigned char *hexStr) {
  const size_t nmatch = 2;
  regmatch_t pmatch[nmatch + 1];

  int hexCheck = regCheck((char *)hexStr, HEXREG, nmatch, pmatch);

  if (hexCheck == 0) {
    hex *newColor = malloc(sizeof(*newColor));

    char buf[256] = {0};
    strncpy(buf, (char *)hexStr + pmatch[1].rm_so,
            pmatch[1].rm_eo - pmatch[1].rm_so);

    newColor->code = strtol(buf, NULL, 16);

    return newColor;

  } else
    return NULL;
}

// A function to create a new RGB color : see color.h
rgb *newRGBColor(const unsigned int r, const unsigned int g,
                 const unsigned int b) {
  rgb *newColor = malloc(sizeof(*newColor));

  if (!checkRGBValue(r) || !checkRGBValue(g) || !checkRGBValue(b)) {
    fprintf(stderr, "newRGBColor::Invalid RGB value provided !");
    return NULL;
  }

  newColor->red = r;
  newColor->green = g;
  newColor->blue = b;

  return newColor;
}

// Function to extract RGB values from string : see color.h
rgb *newRGBColorFromStr(const char *rgbStr) {
  const size_t nmatch = 4;
  regmatch_t pmatch[nmatch + 1];

  int rgbCheck = regCheck(rgbStr, RGBREG, nmatch, pmatch);

  if (rgbCheck == 0) {
    int rgbValues[3];

    for (size_t i = 1; pmatch[i].rm_so != -1 && i < nmatch; i++) {
      char buf[256] = {0};
      strncpy(buf, rgbStr + pmatch[i].rm_so, pmatch[i].rm_eo - pmatch[i].rm_so);
      rgbValues[i - 1] = atoi(buf);
    }

    rgb *rgbCol = newRGBColor(rgbValues[0], rgbValues[1], rgbValues[2]);
    return rgbCol;

  } else {
    return NULL;
  }
}

// Function to create a new color : see color.h
color *newColor() {
  color *c = malloc(sizeof(*c));

  if (c != NULL) {
    c->hexValue = NULL;
    c->rgbValues = NULL;
  }

  return c;
}

// Function to create a new color from color string : see color.h
color *newColorFromStr(const char *colStr) {
  color *myCol = newColor();

  if (myCol == NULL) {
    fprintf(stderr, "newColorFromStr::Memory allocation failed for new color");
    exit(0);
  }

  hex *hexFromArg = newHexColor((const unsigned char *)colStr);
  rgb *rgbFromArg = newRGBColorFromStr(colStr);

  // Check which color format matches
  if (hexFromArg != NULL) {
    free(rgbFromArg);
    rgbFromArg = hex2RGB(hexFromArg);
  }

  else if (rgbFromArg != NULL) {
    free(hexFromArg);
    hexFromArg = rgb2Hex(rgbFromArg);
  }

  else {
    fprintf(stderr, "Invalid color provided: %s\n", colStr);
    exit(0);
  }

  myCol->hexValue = hexFromArg;
  myCol->rgbValues = rgbFromArg;
  myCol->hslValues = rgb2HSL(rgbFromArg);

  return myCol;
}

// A function to create a new HSL tuple : see color.h
hsl *newHSLTuple(const float h, const float s, const float l) {
  hsl *newHSL = malloc(sizeof(*newHSL));

  if (!checkRGBValue(h) || !checkSLValue(s) || !checkSLValue(l)) {
    fprintf(stderr, "newHSLTuple::Invalid HSL value provided !");
    return NULL;
  }

  newHSL->hue = h;
  newHSL->saturation = s;
  newHSL->lightness = l;

  return newHSL;
}

// A function to check if the given value is a valid RGB value : see color.h
bool checkRGBValue(const float value) {
  bool check = false;
  if (value >= 0 && value <= 255)
    check = true;

  return check;
}

// A function to check if the given Saturation / Lightness value are valid : see
// color.h
bool checkSLValue(const float value) {
  bool check = false;
  if (value >= 0 && value <= 1)
    check = true;

  return check;
}

// Function to get percentages repartition of RGB values
float *rgbPercentages(rgb *rgb) {
  float *perc = malloc(3 * sizeof(*perc));

  perc[0] = (float)rgb->red / 255;
  perc[1] = (float)rgb->green / 255;
  perc[2] = (float)rgb->blue / 255;

  return perc;
}

// A function to convert a hex color into an RGB one : see color.h
rgb *hex2RGB(hex *hexCol) {
  return newRGBColor(
    (hexCol->code >> 16) & 0xFF,
    (hexCol->code >> 8) & 0xFF,
    hexCol->code & 0xFF
  );
}

hex *rgb2Hex(rgb *rgb) {
  unsigned char hexStr[7];
  sprintf((char *)hexStr, "%02x%02x%02x", rgb->red, rgb->green, rgb->blue);

  return newHexColor(hexStr);
}

// A function to get HSL values from RGB
hsl *rgb2HSL(rgb *rgb) {
  float *perc = rgbPercentages(rgb);

  float redPerc = perc[0], greenPerc = perc[1], bluePerc = perc[2];

  float minRGB = MIN(MIN(redPerc, greenPerc), bluePerc);
  float maxRGB = MAX(MAX(redPerc, greenPerc), bluePerc);

  // Lightness
  float l = (minRGB + maxRGB) / 2;

  // Saturation
  float s;
  if (minRGB == maxRGB)
    s = 0;

  else if (l < 0.5)
    s = (maxRGB - minRGB) / (maxRGB + minRGB);

  else
    s = (maxRGB - minRGB) / (2 - maxRGB - minRGB);

  // Hue
  float h;
  if (s == 0)
    h = 0;

  else if (redPerc >= MAX(greenPerc, bluePerc))
    h = (greenPerc - bluePerc) / (maxRGB - minRGB);

  else if (greenPerc >= MAX(redPerc, bluePerc))
    h = 2 + (bluePerc - redPerc) / (maxRGB - minRGB);

  else
    h = 4 + (redPerc - greenPerc) / (maxRGB - minRGB);

  h *= 60;

  if (h < 0)
    h += 360;

  return newHSLTuple(h, s, l);
}

// A function to get RGB values from HSL
rgb *hsl2RGB(hsl *hsl) {
  if (hsl->saturation == 0)
    return newRGBColor(hsl->hue * 255, hsl->saturation * 255,
                       hsl->lightness * 255);

  float tmp1;
  if (hsl->lightness < 0.5)
    tmp1 = hsl->lightness * (1 + hsl->saturation);

  else
    tmp1 = hsl->lightness + hsl->saturation - hsl->lightness * hsl->saturation;

  float tmp2 = 2 * hsl->lightness - tmp1;
  float newHue = hsl->hue / 360;

  float tmpRed = newHue + .333, tmpGreen = newHue, tmpBlue = newHue - .333;

  float tmpArr[3] = {tmpRed, tmpGreen, tmpBlue};
  float rgb[3];

  for (int i = 0; i < 3; i++) {
    float tmpV = tmpArr[i];

    if (tmpV < 0)
      tmpV += 1;

    if (tmpV > 1)
      tmpV -= 1;

    if ((6 * tmpV) < 1)
      rgb[i] = tmp2 + (tmp1 - tmp2) * 6 * tmpV;

    else {
      if ((2 * tmpV) < 1)
        rgb[i] = tmp1;

      else
        rgb[i] = ((3 * tmpV) < 2) ? tmp2 + (tmp1 - tmp2) * (.666 - tmpV) * 6 : tmp2;
    }
  }

  return newRGBColor(rgb[0] * 255 + 1, rgb[1] * 255 + 1, rgb[2] * 255);
}

// Function to change saturation of given color : see color.h
color *changeColorSaturation(color *c, float saturation)
{
  // Step 0 : limit saturation value
  float newSaturation = MAX(MIN(1, saturation), 0);
  
  // Step 1 : create new HSL with old hue and lightness + change saturation
  hsl *newHSL = newHSLTuple(c->hslValues->hue, newSaturation, c->hslValues->lightness);
  
  // Step 2 : create new rgb and hex values based on new hsl
  rgb *newRGB = hsl2RGB(newHSL);
  hex *newHex = rgb2Hex(newRGB);
  
  // Step 3 : free old values
  free(c->hexValue);
  free(c->rgbValues);
  free(c->hslValues);

  // Step 4 : set new values
  c->hexValue = newHex;
  c->rgbValues = newRGB;
  c->hslValues = newHSL;
  
  return c;
}

// A function to calculates a basic distance between two colors : see color.h
float getHexBasicColorDistance(hex *hexColor1, hex *hexColor2) {
  rgb *rgbColor1 = hex2RGB(hexColor1);
  rgb *rgbColor2 = hex2RGB(hexColor2);

  float rc = pow(rgbColor1->red - rgbColor2->red, 2);
  float gc = pow(rgbColor1->green - rgbColor2->green, 2);
  float bc = pow(rgbColor1->blue - rgbColor2->blue, 2);

  return sqrt(rc + gc + bc) / sqrt(pow(255, 2) + pow(255, 2) + pow(255, 2));
}

// Prints Hex color value : see color.h
void printHexValue(hex *hexColor) { printf("#%x\n", hexColor->code); }

// Prints RGB values : see color.h
void printRGBValues(rgb *rgbColor) {
  printf("(%d,%d,%d)\n", rgbColor->red, rgbColor->green, rgbColor->blue);
}

// Prints HSL values : see color.h
void printHSLValues(hsl *hslTuple) {
  printf("(%f,%f,%f)\n", hslTuple->hue, hslTuple->saturation,
         hslTuple->lightness);
}

void printColor(color *col) {
  printf("\nColor Hex: #%x\n", col->hexValue->code);
  printf("Color RGB: (%d,%d,%d)\n", col->rgbValues->red, col->rgbValues->green, col->rgbValues->blue);
  printf("Color HSL: (%f,%f,%f)\n", col->hslValues->hue, col->hslValues->saturation, col->hslValues->lightness);
}