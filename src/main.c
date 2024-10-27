#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "color_dlist.h"

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

  static const struct option longOptions[] = {
    {"color", required_argument, 0, 'c'},
    {"distance", no_argument, 0, 'd'},
    {"help", no_argument, 0, 'H'},
    {"info", optional_argument, 0, 'i'},
    {"saturate", required_argument, 0, 's'},
  };

  ColorDList *colors = newColorDList();
  float saturation;

  // Program modes
  enum mode { INFO, DISTANCE, SATURATE } m;
  
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
        m = DISTANCE;
        break;

      case 'i':
        m = INFO;
        break;

      case 'H':
        break;

      case 's':
        m = SATURATE;
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
  
  if (isColorDListEmpty(colors))
  {
    fprintf(stderr, "No color provided");
    exit(1);
  }

  struct commandinfo
  {
    char *(*func)(ColorDList *cli, float sat);
  };

  static const struct commandinfo commandinfoLookup[] = {};

  // Mode actions
  switch (m) {
    case 1:
      

      break;
      
    case 2:
      changeDListColorSaturation(colors, saturation);
      break;
    
    default:
      printColorDList(colors);
  }

  deleteColorDList(colors);
  
  return EXIT_SUCCESS;
}
