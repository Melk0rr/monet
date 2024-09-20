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

/**
 * @brief Adds a new color to the given color dlist
 * 
 * @param cli {ColorDList} : list to push the new color into
 * @param col {color} : new color
 * @return ColorDList* {ColorDList} : updated color dlist
 */
ColorDList *pushBackColorDList(ColorDList *cli, color *col);

/**
 * @brief Removes the last color from given color dlist
 * 
 * @param cli {ColorDList} : color dlist to retreive last color from
 * @return ColorDList* {ColorDList} : updated color dlist
 */
ColorDList *popBackColorDList(ColorDList *cli);

/**
 * @brief Deletes a color dlist
 * 
 * @param cli {ColorDList} : color dlist to delete
 */
void deleteColorDList(ColorDList *cli);

#endif