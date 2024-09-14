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




#endif
