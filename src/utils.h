#ifndef __UTILS__H__
#define __UTILS__H__

#include <regex.h>

// #########################################################
// Struct definitions

/**
 * @brief Bool type struct
 * 
 */
typedef enum
{
  false,
  true
} bool;

#endif

// #########################################################
// Prototypes

/**
 * @brief Ask user for input
 * 
 * @param prompt {char *} : prompt string
 * @param buffer {char *} : buffer into which store user input
 * @param bufferSize {int} : size of the buffer
 * @return signed char 
 */
void getSecureInput(char *prompt, char *buffer, int bufferSize);

/**
 * @brief Ask user specifically for an int
 * 
 * @param prompt {char *} : prompt string
 * @param bufferSize {int} : buffer size
 * @return int : input integer
 */
int getSecureInputInt(char *prompt, int bufferSize);

/**
 * @brief Ask user specifically for a signed char (string)
 * 
 * @param prompt {char *} : prompt string
 * @param bufferSize {int} : size of the buffer
 * @return signed char : input string
 */
signed char *getSecureInputSignedChar(char *prompt, int bufferSize);

/**
 * @brief Prints text in specified color
 * 
 * @param text {const char *} : text to print
 * @param color {const char *} : color value
 */
void printInColor(const char *text, const char *color);

/**
 * @brief Prints text in white
 * 
 * @param text {const char *} : text to print
 */
void printWhite(const char *text);

/**
 * @brief Prints text in red
 * 
 * @param text {const char *} : text to print
 */
void printRed(const char *text);

/**
 * @brief Prints text in green
 * 
 * @param text {const char *} : text to print
 */
void printGreen(const char *text);

/**
 * @brief Prints text in yellow
 * 
 * @param text {const char *} : text to print
 */
void printYellow(const char *test);

/**
 * @brief Prints text in blue
 * 
 * @param text {const char *} : text to print
 */
void printBlue(const char *text);

/**
 * @brief Check if provided string matches the given regex pattern
 * 
 * @param myStr {char *} : string to check
 * @param pattern {char *} : regex pattern
 * @return regmatch_t : pmatch array
 */
int regCheck(char *myStr, char *pattern, size_t nmatch, regmatch_t pmatch[]);