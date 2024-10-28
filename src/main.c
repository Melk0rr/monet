#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "color_dlist.h"
#include "parse.h"

void mappedDistance(ColorDList *cli)
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

int main(int argc, char *argv[]) {

  ColorDList *colors = newColorDList();
  float saturation;

  // Program modes
  commandmode m;
  
  int opt;
  int optionIndex = 0;

  // Handling options
  while ((opt = getopt_long(argc, argv, "c:s:dvHi", longOptions,
    &optionIndex)) != -1) 
  {
    switch (opt) {
      case 'c':
        // New color
        colors = pushBackColorDList(colors, newColorFromStr(optarg));
        break;

      case 'd':
        m = CMD_DISTANCE;
        break;

      case 'i':
        m = CMD_INFO;
        break;

      case 'H':
        m = CMD_HELP;
        break;

      case 's':
        m = CMD_SATURATE;
        saturation = atof(optarg);
        
        break;

      default:
        abort();
    }
  }

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);

    putchar('\n');
  }
  
  // // Mode actions
  // switch (m) {
  //   case 1:
  //     mappedDistance(colors);
  //     break;
      
  //   case 2:
  //     changeDListColorSaturation(colors, saturation);
  //     break;
    
  //   default:
  //     printColorDList(colors);
  // }

  deleteColorDList(colors);
  
  return EXIT_SUCCESS;
}
