
#include "parse.h"
#include <bits/getopt_ext.h>

// Handle --distance command argument : see parse.h
void cmdDistance(ColorDList *cli, struct commanddata *cmdata)
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
void cmdSaturate(ColorDList *cli, struct commanddata *cmdata)
{
  changeDListColorSaturation(cli, cmdata->value.sat);
}

// Handle --help command argument : see parse.h
void cmdHelp(ColorDList *cli, struct commanddata *cmdata)
{
  printf("Monet, color manipulation\nUsage: monet (--color [--saturate])...\n\n");
  printf("Options:\n");

  for (int i = 0; i < (sizeof(longOptions) / sizeof(struct option)); i++)
  {
    printf("-%c --%s\n", longOptions[i].val, longOptions[i].name);
  }
}

// Handle --info command argument : see parse.h
void cmdInfo(ColorDList *cli, struct commanddata *cmdata)
{
  printColorDList(cli);
}

// Parse command mode : see parse.h
void parseMode(ColorDList *cli, struct commanddata *cmdata)
{
  if (cmdata->mode != CMD_HELP && isColorDListEmpty(cli))
  {
    fprintf(stderr, "No color provided");
    exit(1);
  }

  const struct commandinfo *modeCommandInfo = &modeLookup[cmdata->mode];
  modeCommandInfo->func(cli, cmdata);
}
