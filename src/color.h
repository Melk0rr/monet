#ifndef __COLOR__H__
#define __COLOR__H__


// #########################################################
// color struct definitions

typedef struct hex
{
  unsigned char code[6];
} hex;

typedef struct rgb
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;

} rgb;

typedef struct hsl
{
  float hue;
  float saturation;
  float lightness;
} hsl;

// #########################################################
// Prototypes

/**
 * @brief Creates a new hex color based on the given string
 * 
 * @param hexStr {const unsigned char} : hex falue with or without "#"
 * @return hex* {hex} : new hex color
 */
hex *newHexColor(const unsigned char *hexStr);

/**
 * @brief Creates a new RGB color based on the given red, green and blue values
 * 
 * @param r {const unsigned char} : red value
 * @param g {const unsigned char} : green value
 * @param b {const unsigned char} : blue value
 * @return rgb* {rgb} : new rgb color
 */
rgb *newRGBColor(const unsigned char r, const unsigned char g, const unsigned char b);

#endif
