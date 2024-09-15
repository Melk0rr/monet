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
  int red;
  int green;
  int blue;

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
 * @param r {const int} : red value
 * @param g {const int} : green value
 * @param b {const int} : blue value
 * @return rgb* {rgb} : new rgb color
 */
rgb *newRGBColor(const int r, const int g, const int b);

/**
 * @brief Creates a new HSL tuple based on the giver hue, saturation and lightness
 * 
 * @param h {const float} : hue value
 * @param s {const float} : saturation value
 * @param l {const float} : lightness value
 * @return hsl* {hsl} : hsl tuple
 */
hsl *newHSLTuple(const float h, const float s, const float l);

/**
 * @brief Cheks if the given value is a valid RGB value
 * 
 * @param value {const float} : value to check
 * @return true {bool} : the value is valid
 * @return false {bool} : the value is not valid
 */
bool checkRGBValue(const float value);

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
 * @brief Gets HSL from RGB
 * 
 * @param rgb {rgb} : RGB to use to get HSL values
 * @return hsl* {hsl} : HSL values
 */
hsl *rgb2HSL(rgb *rgb);

/**
 * @brief Gets RGB from HSL
 * 
 * @param hsl {hsl} : hsl to use to get RGB values
 * @return rgb* {rgb} : RGB values
 */
rgb *hsl2RGB(hsl *hsl);

/**
 * @brief Maxes a color saturation
 * 
 * @param baseColor {hex} : hex color to which max the saturation
 * @param saturation {float} : saturation value to set (0 <= v <= 1)
 * @return hex* {hex} : new hex color
 */
hex *setHexColorSaturation(hex *baseColor, float saturation);

/**
 * @brief Returns an array of RGB percentages
 * 
 * @param rgb {rgb} : rgb target
 * @return float* : array of percentages
 */
float *rgbPercentages(rgb *rgb);

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

/**
 * @brief Prints HSL values
 * 
 * @param hslTuple {hsl} : hsl to print
 */
void printHSLValues(hsl *hslTuple);

#endif
