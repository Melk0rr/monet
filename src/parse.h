#ifndef __PARSE__H__
#define __PARSE__H__

#include <getopt.h>

#include "color_dlist.h"

/**
 * @brief Command modes enumeration
 * 
 */
enum commandmode
{
  CMD_HELP,
  CMD_INFO,
  CMD_DISTANCE,
  CMD_SATURATE
};

/**
 * @brief Command data to pass
 * 
 */
struct commanddata
{
  enum commandmode mode;
  union
  {
    float sat;
  } value;
};

/**
 * @brief Command info with function pointer
 * 
 */
struct commandinfo
{
  void (*func)(ColorDList *cli, struct commanddata *cmdata);
};

/**
 * @brief Handle --distance command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdDistance(ColorDList *cli, struct commanddata *cmdata);

/**
 * @brief Handle --saturate command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdSaturate(ColorDList *cli, struct commanddata *cmdata);

/**
 * @brief Handle --help command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdHelp(ColorDList *cli, struct commanddata *cmdata);

/**
 * @brief Handle --info command argument
 * 
 * @param cli {ColorDList} : color dlist to potentially use
 * @param cmdata {union commanddata} : potential data to pass
 */
void cmdInfo(ColorDList *cli, struct commanddata *cmdata);

/**
 * @brief Handles command data and run mathing function
 * 
 * @param cli {ColorDList} : color dlist to pass to mode functions
 * @param cmdata {struct commandata} : command data to pass to mode functions
 */
void parseMode(ColorDList *cli, struct commanddata *cmdata);

/**
 * @brief Mode lookup table : associates commandmode to a function
 * 
 */
static const struct commandinfo modeLookup[] = {
  [CMD_HELP]     = {cmdHelp},
  [CMD_INFO]     = {cmdInfo},
  [CMD_DISTANCE] = {cmdDistance},
  [CMD_SATURATE] = {cmdSaturate}
};

/**
 * @brief Long option table to use with getopt longoptions
 * 
 */
static const struct option longOptions[] = {
  {"color", required_argument, 0, 'c'},
  {"distance", no_argument, 0, 'd'},
  {"help", no_argument, 0, 'H'},
  {"info", optional_argument, 0, 'i'},
  {"saturate", required_argument, 0, 's'},
};

#endif