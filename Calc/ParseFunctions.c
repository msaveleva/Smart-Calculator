//
//  ParseFunctions.c
//  Calc
//
//  Created by Maria Saveleva on 07/02/14.
//  Copyright (c) 2014 Maria Saveleva. All rights reserved.
//

#include <stdio.h>
#include <ctype.h>
#include "ParseFunctions.h"

rpnData* parse_string(char *string)
{
    char result_digits[50][50];
    char result_operators[50];
    static rpnData result_string[100];
    double result_numbers[100];

    int i = 0;
    int digits_cnt = 0;
    int digit_string = 0;
    int operators_cnt = 0;
    while (string[i] != '\n') {
        if (detect_symbol_type(string[i]) == sym_digit || string[i] == '.') {
            result_digits[digit_string][digits_cnt] = string[i];
            digits_cnt++;
        } else {
            if (detect_symbol_type(string[i]) == sym_operator) {
                result_operators[operators_cnt] = string[i];
                result_digits[digit_string][digits_cnt] = '\n';
                operators_cnt++;
                digit_string++;
                digits_cnt = 0;
            } else {
                if (detect_symbol_type(string[i]) == sym_constant) {
                    textType type = parse_consts_and_functions(string, i);
                    switch (type) {
                        case const_pi:
                            result_numbers[digit_string] = kMPI;
                            break;
                        case const_eil:
                            result_numbers[digit_string] = kME;
                            break;
                        case func_sin:
                            
                            break;
                        case func_cos:
                            
                            break;
                        case func_exp:
                            
                            break;
                            
                        default:
                            break;
                    }
                }
            }
        }
        i++;
    }
    
    result_operators[operators_cnt] = '\n';
    
    for (int i = 0; i <= digit_string; i++) {
        
        if (result_numbers[i] == kMPI || result_numbers[i] == kME) {
            continue;
        }
        
        double result = 0;
        sscanf(result_digits[i], "%lf", &result);
        result_numbers[i] = result;
        printf("Parse result: %lf\n", result);
    }
    
    int k = 0;
    for (int i = 0; i <= (digit_string + operators_cnt); i++) {
        result_string[i].number = result_numbers[k];
        result_string[i].type = sym_digit;
        printf("%lf", result_string[i].number);
        i++;
        result_string[i].op = result_operators[k];
        result_string[i].type = sym_operator;
        printf("%c", result_string[i].op);
        k++;
    }
    result_string[i].type = sym_operator;
    result_string[i].op = '\n';
    
    return result_string;
}

symbolType detect_symbol_type(char symbol)
{
    if (isdigit(symbol)) {
        return sym_digit;
    } else {
        if (isalpha(symbol)) {
            return sym_constant;
        } else {
            if (ispunct(symbol)) {
                return sym_operator;
            } else {
                return sym_space;
            }
        }
    }
}

priority detect_symbol_priority(char symbol)
{
    if (symbol == '+' || symbol == '-') {
        return low;
    } else {
        if (symbol == '*' || symbol == '/') {
            return normal;
        } else {
            return high;
        }
    }
}

textType parse_consts_and_functions(char *string, int cnt)
{
    if (string[cnt] == 'P' && string[cnt+1] == 'i') {
        return const_pi;
    }
    
    if (string[cnt] == 'E') {
        return const_eil;
    }
    
    return can_not_read;
}
