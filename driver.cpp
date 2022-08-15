/*    SECTION: COMP 116 - Data Structures
 * ASSIGNMENT: Project 7 - ChangeMaker.cpp
 *       DATE: 22 November 2019
 *   DUE DATE: 22 November 2019
 *
 *      INPUT: The user inputs into the console the filename of a file containing comma separated
 *              integer values that denote the value of a coin (1,5,10,25) and amount of change desired.
 *
 *     OUTPUT: Printed to the console is a summary of the amount of each coin from the input file
 *              that would be given to the user to total the amount of desired change they inputted. It also
 *              prints out the list of the remaining coins in their same order, with the coins given back removed
 *              from the list.
 *
 *    SUMMARY: With the input file of coin values and inputted desired change, the code will calculate the
 *              amount of change in coins from the input file to remove from the file, keeping intact the
 *              order of the coins and printing a summary of the process.
 *
 *   COMMENTS: I decided to create this code in a way that returns the least amount of coins back to the user (i.e.
 *              instead of giving the user 25 pennies, it would give them 1 quarter when possible). This code deals
 *              with invalid user input for file name, change amount, and input file values by asking the user to
 *              retry and re-enter values. I included the checks and user input inside the readCoins() and getChange()
 *              functions themselves. I have tested and implemented sections of the code to handle certain
 *              inputs/situations, such as a change plan too large, a change plan that cannot be made (i.e.$.03 with only
 *              nickels), when input does not include the appropriate amount of decimals to denote cents ($2.3 is still
 *              read as $2.30), if the file does not exist, and if the contents of the file are not valid coins.
 *              This code took me far longer than I was intending, however, I am very proud of how it turned out.
 *
 * PROGRAMMER: Jacob Libby
 *             I have abided by the Wheaton Honor Code
 */
#include "ChangeMaker.h"
using namespace std;
int main() {
    ChangeMaker cm; // create ChangeMaker object
    cm.readCoins(); // read in coins from input file
    cm.getChange(); // create and implement change plan
    return 0;
}