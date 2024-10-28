#ifndef __PARSE__H__
#define __PARSE__H__

#include <getopt.h>

typedef enum
{
  CMD_HELP,
  CMD_INFO,
  CMD_DISTANCE,
  CMD_SATURATE
} commandmode;

union commanddata
{
  float sat;
};

const struct option longOptions[] = {
  {"color", required_argument, 0, 'c'},
  {"distance", no_argument, 0, 'd'},
  {"help", no_argument, 0, 'H'},
  {"info", optional_argument, 0, 'i'},
  {"saturate", required_argument, 0, 's'},
};

#endif