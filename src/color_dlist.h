#ifndef __COLOR_DLIST__H__
#define __COLOR_DLIST__H__

#include "color.h"

// #########################################################
// Color DList and node struct definition

/**
 * @brief Colors doubled chained list node
 * 
 */
typedef struct ColorDListNode
{
  color *nodeColor;
  struct ColorDListNode *prev;
  struct ColorDListNode *next;
} ColorDListNode;

/**
 * @brief Color doubled chained list
 * 
 */
typedef struct ColorDList
{
  int length;
  struct ColorDListNode *begin;
  struct ColorDListNode *end;
} ColorDList;

// #########################################################
// Prototypes

#endif