// main.cpp
#include <iostream>  // Includes the standard input-output stream
#include "WordList.h"  // Includes the WordList header file
#include "WordCat.h"  // Includes the WordCat header file
#include "WordCatVec.h"  // Includes the WordCatVec header file

/**
 * @brief Tests the WordCatVec class by running its main loop.
 */
void testWordCatVec() {
    WordCatVec word_cat_vec;  // Creates an instance of WordCatVec
    word_cat_vec.run();  // Runs the main loop of WordCatVec
}

// /**
//  * @brief Tests the WordCat class by running its main loop.
//  */
// void testWordCat() {
//     WordCat word_cat;  // Creates an instance of WordCat
//     word_cat.run();  // Runs the main loop of WordCat
// }

// /**
//  * @brief Tests the WordList class.
//  */
// void testWordList() {
//     WordList word_list;  // Creates an instance of WordList
//     // Add words to the list
//     word_list.insertSorted("apple");
//     word_list.insertSorted("banana");
//     word_list.insertSorted("cherry");

//     // Print the list
//     std::cout << "WordList contains:\n" << word_list << std::endl;

//     // Test other WordList methods here
// }

/**
 * @brief Tests the Word class.
 */
// void test_Word() {
//     Word word1("hello");  // Creates an instance of Word with "hello"
//     Word word2("world");  // Creates an instance of Word with "world"

//     // Print the words
//     std::cout << "Word1: " << word1 << std::endl;
//     std::cout << "Word2: " << word2 << std::endl;

//     // Test other Word methods here
// }


/**
 * @brief The main function of the program. Calls the test function for WordCatVec.
 * @return int Returns 0 to indicate successful execution.
 */
int main() {

    // Uncomment the following lines to test the classes:

    testWordCatVec();  // Calls the test function for WordCatVec
    // testWordCat();  // Calls the test function for WordCat
    // testWordList();  // Calls the test function for WordList
    // test_Word();  // Calls the test function for Word

    return 0;  // Returns 0 to indicate successful execution
}
