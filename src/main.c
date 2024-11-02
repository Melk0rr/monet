#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"
#include "color_dlist.h"
#include "parse.h"
#include "utils.h"

int main(int argc, char *argv[]) {

  ColorDList *colors = newColorDList();
  struct commanddata *cmdata = xmalloc(sizeof *cmdata);

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
        cmdata->mode = CMD_DISTANCE;
        break;

      case 'i':
        cmdata->mode = CMD_INFO;
        break;

      case 'H':
        cmdata->mode = CMD_HELP;
        break;

      case 's':
        cmdata->mode = CMD_SATURATE;
        cmdata->value.sat = atof(optarg);
        
        break;

      default:
        abort();
    }
  }

  if (optind < argc) {
    printf("Non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);

    putchar('\n');
  }

  parseMode(colors, cmdata);

  free(cmdata);
  deleteColorDList(colors);
  
  return EXIT_SUCCESS;
}
