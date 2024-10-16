#include "utils.h"

// Define ANSI escape codes for colors
#define RESET       "\x1b[0m"
#define BLACK       "\x1b[30m"
#define RED         "\x1b[31m"
#define GREEN       "\x1b[32m"
#define YELLOW      "\x1b[33m"
#define BLUE        "\x1b[34m"
#define MAGENTA     "\x1b[35m"
#define CYAN        "\x1b[36m"
#define WHITE       "\x1b[37m"
#define BOLD        "\x1b[1m"

// Prints text in a certain color : see utils.h
void printInColor(const char *text, const char *color)
{
  printf("%s%s%s\n", color, text, RESET);
}

// Prints text in white : see utils.h
void printWhite(const char *text)
{
  printInColor(text, WHITE);
}

// Prints text in red : see utils.h
void printRed(const char *text)
{
  printInColor(text, RED);
}

// Prints text in green : see utils.h
void printGreen(const char *text)
{
  printInColor(text, GREEN);
}

// Prints text in yellow : see utils.h
void printYellow(const char *text)
{
  printInColor(text, YELLOW);
}

// Prints text in blue : see utils.h
void printBlue(const char *text)
{
  printInColor(text, BLUE);
}

// Function to check malloc : see utils.h
void *xmalloc(size_t size)
{
  void *p = malloc(size);

  if (p == NULL)
    abort();

  return p;
}

// Function to check if a given string matches provided regex pattern
int regCheck(const char *myStr, const char *pattern, size_t nmatch, regmatch_t pmatch[])
{
  regex_t regex;
  assert(regcomp(&regex, pattern, REG_EXTENDED) == 0);

  return regexec(&regex, myStr, nmatch, pmatch, 0);
}