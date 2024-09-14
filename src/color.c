#include "utils.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

  // newColor->code = malloc(sizeof());
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