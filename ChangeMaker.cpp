#include "ChangeMaker.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// creating constant variables for coin values
const int PENNY = 1;
const int NICKEL = 5;
const int DIME = 10;
const int QUARTER = 25;

ChangeMaker::~ChangeMaker(){
    while (!stackOfCoins.isEmpty()){
        stackOfCoins.pop();
    }
    quarterCount = 0, dimeCount = 0, nickelCount = 0, pennyCount = 0;
    quartersDesired = 0, dimesDesired = 0, nickelsDesired = 0,penniesDesired = 0;
}

ChangeMaker::ChangeMaker(){
    Stack stackOfCoins;
    quarterCount = 0, dimeCount = 0, nickelCount = 0, pennyCount = 0;
    quartersDesired = 0, dimesDesired = 0, nickelsDesired = 0,penniesDesired = 0;
};

void ChangeMaker::readCoins() {
    // Declaring/Initializing variables
    quarterCount = 0, dimeCount = 0, nickelCount = 0, pennyCount = 0;
    string tempString;
    bool validFile;
    char * pch;

    // checking/opening input file
    do {
        validFile = true;
        cout << "Enter the input file:";
        cin >> inputFileName;
        ifstream inputFile;
        inputFile.open(inputFileName);
        if (!inputFile) { // Error Catching
            validFile = false;
            cout << "\t**ERROR: No valid file with name: '" << inputFileName << "' found. Please try again."<< endl;
        }
        else { // file found, now check to see if data is valid

            // creating array of characters from input file
            string stringy;
            getline(inputFile, stringy);
            char *str = new char[stringy.length()+1];
            int index = 0;
            for (index; index < stringy.length(); index++){
                str[index] = stringy[index];
            }
            str[index] = '\0';

            // creating tokens (sectioning input by commas and ignoring " ,.-$"
            pch = strtok (str," ,.-$");
            while (pch != nullptr && validFile){
                if (*pch == '1' && pch[1] == '\0'){ // value == penny
                    pennyCount++;
                    stackOfCoins.push(1);
                }
                else if (*pch == '5' && pch[1] == '\0'){ // value == nickel
                    nickelCount++;
                    stackOfCoins.push(5);
                }
                else if (*pch == '1' && pch[1] == '0' && pch[2] == '\0') { // value == dime
                    dimeCount++;
                    stackOfCoins.push(10);
                }
                else if (*pch == '2' && pch[1] == '5' && (pch[2] == '\0' || pch[2] == '\n')){ // value == quarter
                    quarterCount++;
                    stackOfCoins.push(25);
                }
                else { // value != coin
                    cout << "\t**ERROR: Invalid character found in file: '" << inputFileName << "'. Please try again." << endl;
                    validFile = false;
                }
                pch = strtok (nullptr, " ,.-$");
            }
        }
        inputFile.close();
    } while (!validFile);
}

void ChangeMaker::getChange() {
    // initialize variables
    bool validChangePlan = true;
    quartersDesired = 0, dimesDesired = 0, nickelsDesired = 0, penniesDesired = 0;
    double inputDesiredChange;
    Stack holdingStack;

    // check user input for change amount
    cout << "Enter the change amount: $";
    while (true) {
        if (cin >> inputDesiredChange && inputDesiredChange > 0 &&  to_string(inputDesiredChange).find('.')+1!='\0' && to_string(inputDesiredChange).find('.')+2!='\0') { // valid change amount
            inputDesiredChange+= .000001; // enables input to not need to have two decimal places
            break;
        } else { // invalid change amount
            cout << "Invalid change amount." << endl;
            cout << "Enter the change amount: $";
            cin.clear();
            while (cin.get() != '\n') ; // clears cin
        }
    }

    // open output file
    outputFileName = inputFileName;
    outputFileName.erase(inputFileName.length()-4);
    outputFileName += "-change.txt";
    ofstream outputFile(outputFileName);

    // formatting desired change into int for future calculations
    inputDesiredChange = inputDesiredChange * 100;
    int desiredChange = inputDesiredChange;
    inputDesiredChange = inputDesiredChange / 100;
    validChangePlan = checkChange(desiredChange); // get count of each coin to get back

    if (validChangePlan) { // if change plan is possible
        int quartersBack = quartersDesired, dimesBack = dimesDesired;
        int nickelsBack = nickelsDesired, penniesBack = penniesDesired;
        double coinSum = 0;

        // searching and popping desired coins & pushing undesired coins on holdingStack
        if (quartersDesired > 0 || dimesDesired > 0 || nickelsDesired > 0 || penniesDesired > 0) {
            while (!stackOfCoins.isEmpty()) {
                if (stackOfCoins.getTop() == 25 && quartersDesired >= 1) {
                    stackOfCoins.pop();
                    quartersDesired--;
                    coinSum += .25;
                } else if (stackOfCoins.getTop() == 10 && dimesDesired >= 1) {
                    stackOfCoins.pop();
                    dimesDesired--;
                    coinSum += .10;
                } else if (stackOfCoins.getTop() == 5 && nickelsDesired >= 1) {
                    stackOfCoins.pop();
                    nickelsDesired--;
                    coinSum += .05;
                } else if (stackOfCoins.getTop() == 1 && penniesDesired >= 1) {
                    stackOfCoins.pop();
                    penniesDesired--;
                    coinSum += .01;
                } else { // undesired coin on top of stack
                    holdingStack.push(stackOfCoins.getTop());
                    stackOfCoins.pop();
                }
            }
        }
        while (!holdingStack.isEmpty()) {
            stackOfCoins.push(holdingStack.getTop());
            holdingStack.pop();
        }

        // declaring variables
        double pennyValue = penniesBack, nickelValue = nickelsBack, dimeValue = dimesBack, quarterValue = quartersBack;
        pennyValue *= .01, nickelValue *= .05, dimeValue *= .10, quarterValue *= .25;
        double totalChangeBack = pennyValue + nickelValue + dimeValue + quarterValue;

        // formatting output
        ios init(nullptr);
        init.copyfmt(outputFile);
        outputFile << showpoint << fixed;
        outputFile.precision(2);

        // formatting output to file
        outputFile << "# of pennies:\t0.01 x " << penniesBack << " = " << pennyValue << endl;
        outputFile << "# of nickels:\t0.05 x " << nickelsBack << " = " << nickelValue << endl;
        outputFile << "# of dimes:\t\t0.10 x " << dimesBack << " = " << dimeValue << endl;
        outputFile << "# of quarters:\t0.25 x " << quartersBack << " = " << quarterValue << endl;
        outputFile << "Total: $" << totalChangeBack << endl << endl;
    } else {
        outputFile << "No change plans can be found for $" << inputDesiredChange  << "." << endl << endl;
    }
    outputFile << "Remaining coins:" << endl;

    // flip stack to correct order
    while (!stackOfCoins.isEmpty()){
        holdingStack.push(stackOfCoins.getTop());
        stackOfCoins.pop();
    }

    // print out stack of coins in order
    if (!holdingStack.isEmpty()) {
        outputFile << holdingStack.getTop();
        stackOfCoins.push(holdingStack.getTop());
        holdingStack.pop();
    }
    while (!holdingStack.isEmpty()){
        outputFile << ", " << holdingStack.getTop();
        stackOfCoins.push(holdingStack.getTop());
        holdingStack.pop();
    }

    // closing the ofstream
    outputFile.close();
}

bool ChangeMaker::checkChange(int desiredChange){
    if (desiredChange / QUARTER >= 1 && quarterCount >= 1) { // if we have a quarter and need a quarter
        quartersDesired++;
        quarterCount--;
        desiredChange -= QUARTER;
        checkChange(desiredChange);
    }
    else if (desiredChange / DIME >= 1 && dimeCount >= 1) { // if we have a dime and need a dime
        dimesDesired++;
        dimeCount--;
        desiredChange -= DIME;
        checkChange(desiredChange);
    }
    else if (desiredChange / NICKEL >= 1 && nickelCount >= 1) { // if we have a nickel and need a nickel
        nickelsDesired++;
        nickelCount--;
        desiredChange -= NICKEL;
        checkChange(desiredChange);
    }
    else if (desiredChange >= PENNY && pennyCount >= 1) { // if we have a penny and need a penny
        penniesDesired++;
        pennyCount--;
        desiredChange -= PENNY;
        checkChange(desiredChange);
    }
    else if (desiredChange > 0) { // invalid change amount
        // resetting values
        quarterCount += quartersDesired;
        dimeCount += dimesDesired;
        nickelCount += nickelsDesired;
        pennyCount += penniesDesired;
        quartersDesired = 0;
        dimesDesired = 0;
        nickelsDesired = 0;
        penniesDesired = 0;
        return false;
    }
}