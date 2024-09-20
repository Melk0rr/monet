#include "color_dlist.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>

// Function to create an empty color dlist : see color_dlist.h
ColorDList *newColorDList()
{
  ColorDList *cli = malloc(sizeof(*cli));

  if (cli != NULL)
  {
    cli->length = 0;
    cli->begin = NULL;
    cli->end = NULL;
  }

  return cli;
}

// Function to check if the given color dlist is empty : see color_dlist.h
bool isColorDListEmpty(ColorDList *cli)
{
  if (cli == NULL || cli->end == NULL)
  {
    return true;
  }

  return false;
}

// Function to push a new color at the end of an color dlist : see color_dlist.h
ColorDList *pushBackColorDList(ColorDList *cli, color *col)
{
  ColorDListNode *colNode = malloc(sizeof(*colNode));
  
  if (colNode == NULL)
  {
    fprintf(stderr, "pushBackColorDList::Memory allocation failed for new ColorDListNode !");
    exit(1);
  }

  colNode->nodeColor = col;
  colNode->prev = NULL;
  colNode->next = NULL;
  
  if (isColorDListEmpty(cli))
  {
    cli = malloc(sizeof(*cli));

    if (cli == NULL)
    {
      fprintf(stderr, "pushBackColorDList::Memory allocation failed for empty ColorDList !");
      exit(1);
    }
    
    // If dlist is empty : new node is the first and last element
    cli->begin = colNode;
    cli->end = colNode;

  } else {
    // If dlist is not empty : Last dlist element next pointer now points to new node
    cli->end->next = colNode;

    // New node prev pointer now points to the previous last dlist element
    colNode->prev = cli->end;
    
    // And dlist end now points to the new node
    cli->end = colNode;
  }
  
  cli->length++;

  return cli;
}

// Function to pop an expense node from given list end : see expense_dlist.h
ColorDList *popBackColorDList(ColorDList *cli)
{
  if (isColorDListEmpty(cli))
  {
    printf("popBackColorDList::List is empty. Nothing to pop.\n");
    return newColorDList();
  }
  
  // Check if the list contains only one element
  if (cli->begin == cli->end)
  {
    free(cli);
    cli = NULL;

    return newColorDList();
  }
  // Saves the last element
  ColorDListNode *tmp = cli->end;

  // Last node is now the second to last
  cli->end = cli->end->prev;

  // The new last node next pointer is now NULL as it is the last element
  cli->end->next = NULL;

  // Deleting removed node links to prev and next
  tmp->next = NULL;
  tmp->prev = NULL;

  free(tmp);
  tmp = NULL;

  cli->length--;

  return cli;
}