#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

#include "color.h"

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
	color *colors = malloc(sizeof(*colors));
	float saturation;

	enum {
		SATURATE,
		HEX2RGB,
		RGB2HEX,
		DISTANCE
	} mode;
	
	regex_t testreg;
	int testCheck = regcomp(&testreg, "^#[0-9a-fA-F]*$", REG_EXTENDED);
	testCheck = regexec(&testreg, "#f8a", 0, NULL, 0);

	if (!testCheck)
	{
		printf("Test check match !");
	} else 
	{
		printf("Test check not match !");
	}

	regex_t reghex;
	int hexCheck = regcomp(&reghex, "^#([0-9a-fA-F]{6}|[0-9a-fA-F]{8})$", 0);

	regex_t rgbex;
	int rgbCheck = regcomp(&rgbex, RGBREG, 0);

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
				// hexColor = newHexColor((const unsigned char *)optarg);
				colors = realloc(colors, ++colorCount * sizeof(*colors));

				// Hex color code regex
				hexCheck = regexec(&reghex, optarg, 0, NULL, 0);

				// RGB color code regex
				rgbCheck = regexec(&rgbex, optarg, 0, NULL, 0);
				
				printf("hex check: %d\n", hexCheck);
				// Check which color format matches
				if (!hexCheck)
				{
					printf("Hex color matched !\n");

				}	else if (!rgbCheck)
				{
					printf("RGB color matched !\n");

				}	else
				{
					fprintf(stderr, "Invalid color provided: %s\n", optarg);
					exit(0);
				}
				
				// colors[colorCount - 1];
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
