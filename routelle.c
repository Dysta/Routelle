#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "routelle.h"

#define SIZE_BUFFER 10

int main(int argc, char* arv[]){
    srand(time(NULL));
    unsigned int credit = 200;
    
    char* input = malloc(sizeof(char) * SIZE_BUFFER);
    if(input == NULL){
        fprintf(stderr, "Not enough memory for malloc\n");
        exit(EXIT_FAILURE);
    }

    printf("+-+-+-+-+-+-+-+-+\n|R|O|U|T|E|L|L|E|\n+-+-+-+-+-+-+-+-+  by Dysta\n");
    printf("Faites !c pour obtenir 200 credits\n");
    printf("Faites !p <mise> pour jouer votre mise, mise par défaut = 5\n");
    printf("Faites !h pour afficher l'aide\n\n");           
    do{
        get_user_input(input);
        parse_user_input(input, &credit);
        //printf("\033[2J"); // clear the terminal
    }while(credit > 0);

    printf("Vous n'avez plus de crédit !\n");

    free(input);
    return EXIT_SUCCESS;
}

void get_user_input(char* str){
    printf("~: ");
    fgets(str, SIZE_BUFFER, stdin);
    clear(str);
}

void parse_user_input(char* input, unsigned int* credit){
    if(input[0] == '!' && (input[2] == '\0' || input[2] == ' ')){
        // Some useful var
        char* tok = NULL;
        int mise = 0;
        switch(input[1]){
            case 'c': // add some credit
                *credit += 200;
                break; 
            case 'p': // play her credit
                tok = strtok(input, " "); // get out the !p
                tok = strtok(NULL, " "); // get the mise
    
                mise = (tok != NULL) ? atoi(tok) : 5;
                if(mise == 0) // error in atoi or otherwise
                   break;
                if(mise < 0)
                    mise *= -1;
                
                if(mise > *credit){
                    printf("Vous n'avez pas assez de crédits !\n");
                    break;
                }
                
                *credit -= mise;
                launch_roulette(credit, &mise);
                break;
            case 'h': // some help for player
                 break;
        }
    }
}

void launch_roulette(unsigned int* credit, int* mise){
    bool win = false;
    int gain = 0;
    char* line[] = { random_symbole(), random_symbole(), random_symbole() };


    for(int i = 0; i < 2; i++ ){
        print_roulette(line, random(0,1), gain, mise, credit);
        printf("\033[11A"); // Move up 11 lines;
        line[0] = random_symbole();
        line[1] = random_symbole();
        line[2] = random_symbole();
        sleep(1);
    }

    line[0] = random_symbole();
    line[1] = random_symbole();
    line[2] = random_symbole();

    // two identical symbols
    if(strcmp(line[0], line[1]) == 0 || strcmp(line[0], line[2]) == 0 || strcmp(line[1], line[2]) == 0){
        gain = *mise * 3 + *mise; 
        win = true;
    }
    
    // all identical symbols
    if(strcmp(line[0], line[1]) == 0 && strcmp(line[0], line[2]) == 0 && strcmp(line[1], line[2]) == 0){
        gain = *mise * 5 + *mise;
        win = true;
    }
    *credit += gain;

    print_roulette(line, win, gain, mise, credit);
}

void print_roulette(char* line[], bool win, int gain, int* mise, unsigned int* credit){
    printf("[:: ROUTELLE ::]\n");
    printf("----------------\n");
    printf("|  %s   %s   %s   |  \n", random_symbole(), random_symbole(), random_symbole());
    printf("|  %s   %s   %s   |<<  \n", line[0], line[1], line[2]);
    printf("|  %s   %s   %s   |  \n", random_symbole(), random_symbole(), random_symbole());
    printf("----------------\n");
    if(win)
        printf("|::   WIN    ::|\n");
    else
        printf("|::   LOST   ::|\n");
    printf("|: CRDT :%4d :|\n", *credit);
    printf("|: MISE :%4d :|\n", *mise);
    printf("|: GAIN :%4d :|\n", (gain == 0) ? gain : gain - *mise);
    printf("----------------\n");
}

char* random_symbole(){
    switch(random(0, 15)){
        case 0: return "🔵";
        case 1: return "⭕";
        case 2: return "🍎";
        case 3: return "🍏";
        case 4: return "🍊";
        case 5: return "🍒";
        case 6: return "🍋";
        case 7: return "🍇";
        case 8: return "🍓";
        case 9: return "💎";
        case 10: return "🍄";
        case 11: return "❌";
        case 12: return "👑";
        case 13: return "🌰";
        case 14: return "🌺";
        default: return "🍌";
    }
}

void clear(char* str){
    char* end = strchr(str, '\n');
    // if we have a end, we replace \n by \0
    if(end != NULL)
        *end = '\0';
    else { // otherwise, we clear all data too much
        char c;
        while(c != '\n' && c != EOF)
            c = getchar();
    }
}

int random(int a, int b){
    b++; // we include b into the interval
    if(a < b)
        return rand()%(b-a) + a;
    else
        return rand()%(a-b) + b;
}