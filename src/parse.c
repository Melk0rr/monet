
#include "parse.h"
#include <bits/getopt_ext.h>

// Handle --distance command argument : see parse.h
void cmdDistance(ColorDList *cli, union commanddata cmdata)
{
  if (cli->length < 2)
  {
    fprintf(stderr, "Not enough colors provided !");
  }
  
  if (cli->begin != NULL && cli->begin->next != NULL)
  {
    color *c1 = cli->begin->nodeColor;
    color *c2 = cli->begin->next->nodeColor;

    float dist = getBasicColorDistance(c1, c2);
    printf("%f", dist);
  }
}

// Handle --saturate command argument : see parse.h
void cmdSaturate(ColorDList *cli, union commanddata cmdata)
{
  changeDListColorSaturation(cli, cmdata.sat);
}

// Handle --help command argument : see parse.h
void cmdHelp(ColorDList *cli, union commanddata cmdata)
{
  printf("Monet, color manipulation\nUsage: monet (--color [--saturate])...\n\n");
  printf("Options:\n");

  for (int i = 0; i < (sizeof(longOptions) / sizeof(struct option)); i++)
  {
    printf("-%c --%s", longOptions[i].val, longOptions[i].name);
  }
}

// Parse command mode : see parse.h
void parseMode(ColorDList *cli, commandmode mode, union commanddata cmd)
{
  if (isColorDListEmpty(cli))
  {
    fprintf(stderr, "No color provided");
    exit(1);
  }


}
