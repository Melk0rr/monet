#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"
#include "color_dlist.h"
#include "utils.h"

static int verbose_flag = 0;

int main(int argc, char *argv[]) {
  int opt;
  int optionIndex = 0;

  static struct option longOptions[] = {
      {"color", required_argument, 0, 'c'},
      {"distance", no_argument, 0, 'd'},
      {"help", no_argument, 0, 'H'},
      {"info", optional_argument, 0, 'i'},
      {"saturate", required_argument, 0, 's'},
      {"verbose", no_argument, &verbose_flag, 'v'},
  };

  ColorDList *colors = newColorDList();
  float saturation;

  // Program modes
  enum mode { DISTANCE, INFO, SATURATE } m;

  // Handling options
  while ((opt = getopt_long(argc, argv, "c:s:dvH", longOptions,
                            &optionIndex)) != -1) 
  {
    color *c;

    switch (opt) {
      case 0:
        if (longOptions[optionIndex].flag != 0)
          break;

        printf("Option %s", longOptions[optionIndex].name);

        if (optarg)
          printf(" with arg %s", optarg);

        printf("\n");
        break;

      case 'c':
        // New color
        c = newColorFromStr(optarg);
        colors = pushBackColorDList(colors, c);

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

  if (verbose_flag)
    puts("verbose flag is set");

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);

    putchar('\n');
  }
  
  // Mode actions
  switch (m) {
    case 0:
      if (colors->length < 2)
      {
        fprintf(stderr, "Not enough colors provided !");
      }
      
      if (colors->begin != NULL && colors->begin->next != NULL)
      {
        color *c1 = colors->begin->nodeColor;
        color *c2 = colors->begin->next->nodeColor;

        float dist = getBasicColorDistance(c1, c2);
        printf("%f", dist);
      }

      break;

    case 1:
      printColor(colors->begin->nodeColor);
      break;
      
    case 2:
      if (isColorDListEmpty(colors))
      {
        fprintf(stderr, "No color provided");
        exit(1);
      }

      color *saturated = changeColorSaturation(colors->begin->nodeColor, saturation);
      printf("#%x", saturated->hexValue->code);
      break;
    
    default:
      abort();  
  }

  deleteColorDList(colors);
  return 0;
}
