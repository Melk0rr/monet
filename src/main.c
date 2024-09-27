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
      {"saturate", required_argument, 0, 's'},
      {"distance", required_argument, 0, 'd'},
      {"verbose", no_argument, &verbose_flag, 'v'},
      {"help", no_argument, 0, 'H'},
  };

  ColorDList *colors = newColorDList();
  float saturation;

  enum { SATURATE, HEX2RGB, RGB2HEX, DISTANCE } mode;

  while ((opt = getopt_long(argc, argv, "c:s:d:vH", longOptions,
                            &optionIndex)) != -1) {
    switch (opt) {
    case 0:
      if (longOptions[optionIndex].flag != 0)
        break;

      printf("Option %s", longOptions[optionIndex].name);

      if (optarg)
        printf(" with arg %s", optarg);

      printf("\n");
      break;

    case 'd':
      printf("option -d with value `%s'\n", optarg);
      break;

    case 'c':
      // New color
      color *c = newColorFromStr(optarg);
      colors = pushBackColorDList(colors, c);

      break;

    case 'H':
      break;

    case 's':
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

  deleteColorDList(colors);
  return 0;
}
