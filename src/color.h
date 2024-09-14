#ifndef __COLOR__H__
#define __COLOR__H__

#include "utils.h"

// #########################################################
// Struct definitions

/**
 * @brief A structure to handle hex colors
 * 
 */
typedef struct hex
{
  unsigned char code[6];
} hex;

/**
 * @brief A structure to handle rgb colors
 * 
 */
typedef struct rgb
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;

} rgb;

/**
 * @brief A structure to handle hsl tuple
 * 
 */
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

/**
 * @brief Cheks if the given value is a valid RGB value
 * 
 * @param value {const unsigned char} : value to check
 * @return true {bool} : the value is valid
 * @return false {bool} : the value is not valid
 */
bool checkRGBValue(const unsigned char value);

/**
 * @brief Checks if the given hue value is valid
 * 
 * @param value {float} : value to check
 * @return true {bool} : value is valid
 * @return false {bool} : value is not valid
 */
bool checkHueValue(const float value);

/**
 * @brief Checks if the given Saturation / Lightness value is valid
 * 
 * @param value {float} : value to check
 * @return true {bool} : value is valid
 * @return false {bool} : value is not valid
 */
bool checkSLValue(const float value);

/**
 * @brief Creates a new HSL tuple based on the given values
 * 
 * @param h {const float} : hue value
 * @param s {const float} : saturation value
 * @param l {const float} : lightness value
 * @return hsl* {hsl} : new hsl tuple
 */
hsl *newHSLTuple(const float h, const float s, const float l);

/**
 * @brief Converts a hex color to 
 * 
 * @param hex {hex} : hex color to convert
 * @return rgb* {rgb} : converted RGB color
 */
rgb *hex2RGB(hex *hex);

/**
 * @brief Converts an RGB color to hex
 * 
 * @param rgb {rgb} : rgb color to convert
 * @return hex* {rgb} : converted Hex color
 */
hex *rgb2Hex(rgb *rgb);

/**
 * @brief Prints Hex value
 * 
 * @param hexColor {hex} : hex to print
 */
void printHexValue(hex *hexColor);

/**
 * @brief Prints RGB values
 * 
 * @param rgbColor {rgb} : rgb to print
 */
void printRGBValues(rgb *rgbColor);

#endif
