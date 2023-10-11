//
// Created by Manuel on 10/10/2023.
//

#include "../headers/prime.h"
#include <iostream>

/*
 * Return whether x is prime or not
 *
 * Returns:
 *   1  - prime
 *   0  - not prime
 *   -1 - undefined (i.e. x < 2)
 */
int is_prime (const int x) {
    if (x < 2) {
        return -1;
    }
    if (x%2 == 0) {
        return 0;
    }
    for (int i = 2; i <= floor(sqrt(x)); i += 2) {
        if (x % i == 0) {
            return 0;
        }
    }
    return 1;
}


int next_prime (const int x) {
    int temp = x;
    while (!is_prime(temp)) {
        temp++;
    }
    return temp;
}