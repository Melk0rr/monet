#include "color_dlist.h"
#include "color.h"

#include <stdio.h>
#include <stdlib.h>

// Function to create an empty expense dlist : see expense_dlist.h
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

