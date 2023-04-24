#include "random.h"
using namespace std;

int generateRandom(int max) {
    
    int randomNumber = rand();
    float random = (randomNumber % max) + 1; //generuje od liczby 1 do maximum
    int myRandom = random;
    
    return myRandom;
}