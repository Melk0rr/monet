#include <stdio.h>

int main(int argc, char const *argv[])
{

	enum {
			
	}

	while ((c = getopt_long(argc, argv, "hc:", &long_options[0], NULL)) != -1) {
		switch (c) {
			case 'h':
				printf("Usage: %s [-h] [color]\n", argv[0]);
				return 1;
			case 'S':
				// Handle saturate option
				break;
			default:
				fprintf(stderr, "Unknown option: -%c\n", c);
				return 2;
		}
	}
	return 0;
}
