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

/**
 * @brief Creates an empty color dlist
 * 
 * @return ColorDList : new empty color dlist
 */
ColorDList *newColorDList(void);

/**
 * @brief Checks if an color dlist is empty
 * 
 * @param eli {colorDList} : list to check
 * @return true : the list is empty
 * @return false : the list is not empty
 */
bool isColorDListEmpty(ColorDList *cli);

#endif