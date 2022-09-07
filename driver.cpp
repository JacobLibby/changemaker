#include "ChangeMaker.h"
using namespace std;
int main() {
    ChangeMaker cm; // create ChangeMaker object
    cm.readCoins(); // read in coins from input file
    cm.getChange(); // create and implement change plan
    return 0;
}
