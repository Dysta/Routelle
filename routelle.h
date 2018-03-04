#ifndef MAIN_H
#define MAIN_H
/**
 * @brief get user input
 * @param str a pointer to the variable that stock the user input
 **/
void get_user_input(char* str);

/**
 * @brief parse the input and call a specifique action in function
 * @param input the user input who need to be parse
 * @param credit the user credit
 **/
void parse_user_input(char* input, unsigned int* credit);

/**
 * @brief launches roulette if the input says
 * @param credit the user credit
 * @param mise the user mise
 **/
void launch_roulette(unsigned int *credit, int* mise);

/**
 * @brief print roulette 
 * @param credit the user credit
 * @param mise the user mise
 **/
void print_roulette(char* line[], bool win, int gain, int* mise, unsigned int* credit);

/**
 * @brief return a random symbole 
 * @return a random symbole
 **/
char* random_symbole(void);

/**
 * @brief clear the stdinput from a previous input or erase \n from a string
 * @param str the string to clear
 **/
void clear(char* str);

/**
 * @brief return a random number between a and b
 * @param a minimum number included of intervals
 * @param b maximum number included of intervals
 * @return random value between a and b
 **/
int random(int a, int b);
#endif