#ifndef __PARSE__H__
#define __PARSE__H__

#include <getopt.h>

#include "color_dlist.h"

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

struct optwithdesc
{
  struct option;
  char *desc;
};

struct commandinfo
{
  void (*func)(ColorDList *cli, union commanddata cmdata);
};

/**
 * @brief Handle --distance command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdDistance(ColorDList *cli, union commanddata cmdata);

/**
 * @brief Handle --saturate command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdSaturate(ColorDList *cli, union commanddata cmdata);

/**
 * @brief Handle --help command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdHelp(ColorDList *cli, union commanddata cmdata);

/**
 * @brief Handle --info command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdInfo(ColorDList *cli, union commanddata cmdata);

const struct commandinfo modeLookup[] = {
  [CMD_HELP]     = {cmdHelp},
  [CMD_INFO]     = {cmdInfo},
  [CMD_DISTANCE] = {cmdDistance},
  [CMD_SATURATE] = {cmdSaturate}
};

const struct option longOptions[] = {
  {"color", required_argument, 0, 'c'},
  {"distance", no_argument, 0, 'd'},
  {"help", no_argument, 0, 'H'},
  {"info", optional_argument, 0, 'i'},
  {"saturate", required_argument, 0, 's'},
};

#endif