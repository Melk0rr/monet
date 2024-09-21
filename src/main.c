#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#include "color.h"
#include "color_dlist.h"

static int verbose_flag = 0;

int main(int argc, char *argv[])
{
	int opt;
	int optionIndex = 0;
	
	static struct option longOptions[] = 
	{
		{ "color", required_argument, 0, 'c' },
		{ "saturate", required_argument, 0, 's' },
		{ "distance", required_argument, 0, 'd' },
		{ "verbose", no_argument, &verbose_flag, 'v' },
		{ "help", no_argument, 0, 'H' },
	};

	int colorCount = 0;
	ColorDList *colors = newColorDList();
	float saturation;

	enum {
		SATURATE,
		HEX2RGB,
		RGB2HEX,
		DISTANCE
	} mode;
	
	regex_t reghex;
	int hexCheck = regcomp(&reghex, HEXREG, REG_EXTENDED);

	regex_t rgbex;
	int rgbCheck = regcomp(&rgbex, RGBREG, REG_EXTENDED);
	const size_t nmatch = 4;
	regmatch_t pmatch[nmatch + 1];

	while ((
		opt = getopt_long(argc, argv, "c:s:d:vH", longOptions, &optionIndex
	)) != -1) 
	{
		switch (opt)
		{
			case 0:
				if (longOptions[optionIndex].flag != 0)
					break;

				printf ("Option %s", longOptions[optionIndex].name);

				if (optarg)
					printf (" with arg %s", optarg);

				printf ("\n");
				break;

			case 'd':
				printf ("option -d with value `%s'\n", optarg);
				break;
				
			case 'c':

				// Hex color code regex
				hexCheck = regexec(&reghex, optarg, 0, NULL, 0);

				// RGB color code regex
				rgbCheck = regexec(&rgbex, optarg, nmatch, pmatch, 0);

				color *c;
				
				// Check which color format matches
				if (hexCheck == 0)
				{
					printf("Hex color matched !\n");
					c->hexColor = newHexColor((const unsigned char *)optarg);
					c->rgbColor = hex2RGB(c->hexColor);

				}	else if (rgbCheck == 0)
				{
					// TODO : use regex to capture matching groups into rgb values
					for (size_t i = 0; pmatch[i].rm_so != -1 && i < nmatch; i++)
					{
						char buf[256] = {0};
						strncpy(buf, optarg + pmatch[i].rm_so, pmatch[i].rm_eo - pmatch[i].rm_so);
						printf("start %d, end %d: %s\n", pmatch[i].rm_so, pmatch[i].rm_eo, buf);
					}

				}	else
				{
					fprintf(stderr, "Invalid color provided: %s\n", optarg);
					exit(0);
				}

				colors = pushBackColorDList(colors, c);
				
				printf("Color: %s\n", optarg);
				break;

			case 'H':
				break;

			case 's':
				saturation = atof(optarg);
				printf("saturation: %f", saturation);
				break;

			default:
				abort();
		}
	}

	if (verbose_flag)
    puts("verbose flag is set");

  if (optind < argc)
	{
		printf("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);

		putchar('\n');
	}

	// printf("%s", colors);

	// const unsigned char hexCode[] = "#0afea4";
	// hex *myColor = newHexColor(hexCode);
	
	// const unsigned char hexCode1[] = "#A36E65";
	// hex *myColor1 = newHexColor(hexCode1);

	// float colDistance = getHexBasicColorDistance(myColor, setHexColorSaturation(myColor1, 1));
	// printf("Distance: %f", colDistance);

	return 0;
}
