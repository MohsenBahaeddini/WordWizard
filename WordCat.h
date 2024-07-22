// WordCat.h
#ifndef WORDCAT_H
#define WORDCAT_H

#include "Word.h"
#include "WordList.h"
#include <iostream>

/**
 * @class WordCat
 * @brief A class to represent a word category.
 */
class WordCat {
private:
    Word category; ///< The name of the category
    WordList wordList; ///< The list of words in the category

    /**
     * @brief Displays a menu to the user and returns the user's choice.
     * @return The user's menu choice
     */
    int menu() const;

    /**
     * @brief Performs an action based on the user's menu choice.
     * @param choice The user's menu choice
     */
    void perform(const int choice);

public:
    /**
     * @brief Default constructor. Initializes category and wordList to their default values.
     */
    WordCat();

    /**
     * @brief Conversion constructor. Initializes category to the input Word and wordList to its default value.
     * @param category The Word to convert
     */
    WordCat(const Word& category);

    /**
     * @brief Destructor. Deallocates any memory that was previously reserved by the WordCat object.
     */
    ~WordCat();

    /**
     * @brief Copy constructor. Initializes a new WordCat object as a copy of an existing one.
     * @param other The WordCat object to copy.
     */
    WordCat(const WordCat& other);

    /**
     * @brief Copy assignment operator. Assigns the values of an existing WordCat object to another.
     * @param other The WordCat object to copy.
     * @return A reference to this object.
     */
    WordCat& operator=(const WordCat& other);

    /**
     * @brief Move constructor. Initializes a new WordCat object by taking ownership of the data in an existing one.
     * @param other The WordCat object to move.
     */
    WordCat(WordCat&& other) noexcept;

    /**
     * @brief Move assignment operator. Assigns the values of an existing WordCat object to another by moving data, not copying it.
     * @param other The WordCat object to move.
     * @return A reference to this object.
     */
    WordCat& operator=(WordCat&& other) noexcept;

    /**
     * @brief Runs the WordCat application. Displays a menu to the user and performs actions based on the user's choice.
     * @return True if the application ran successfully, false otherwise
     */
    bool run();

    /**
     * @brief Returns the name of the category.
     * @return The category name.
     */
    Word getCategoryName() const;

    /**
     * @brief Modifies the name of the category.
     * @param newCategoryName The new category name.
     */
    void modifyCategoryName(const Word& newCategoryName);

    /**
     * @brief Empties the category by clearing the word list.
     */
    void emptyCategory();

    /**
     * @brief Looks up a word in the word list.
     * @param newWord The word to look up.
     * @return True if the word exists in the list, false otherwise.
     */
    bool lookupWordInList(const Word& newWord) const;

    /**
     * @brief Returns a list of words that start with a given letter.
     * @param firstLetter The first letter of the words to return.
     * @return The list of words that start with the given letter.
     */
    WordList getWordsStartingWithLetter(const char firstLetter) const;

    /**
     * @brief Inserts a word into the word list.
     * @param word The word to insert.
     */
    bool insertWord(const Word& word);

    /**
     * @brief Removes a word from the word list.
     * @param word The word to remove.
     * @return True if the word was removed successfully, false otherwise.
     */
    bool removeWord(const Word& word);

    /**
     * @brief Saves the words in the category to a file.
     * @param filename The name of the file to save to.
     */
    void saveToFile(const char* filename) const;

    /**
     * @brief Loads words from a file into the category.
     * @param filename The name of the file to load from.
     */
    void loadFromFile(const char* filename);

    /**
     * @brief Prints each word in the word list on a new line.
     * @param sout The output stream to print to
     * @return The number of words printed
     */
    int printEachWordOfListOnNewLine(std::ofstream& sout) const;

    /**
     * @brief Overloads the << operator to print a WordCat object.
     * @param sout The output stream to print to.
     * @param wc The WordCat object to print.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& sout, const WordCat& wc);

    /**
     * @brief Shows words starting with a given letter.
     * @param letter The starting letter of the words to show.
     */
    void showWordsStartingWith(char letter) const;

    /**
     * @brief Returns the word list.
     * @return The word list.
     */
    const WordList& getWordList() const;
};

/**
 * @brief Helper function to check if a character indicates 'yes'.
 * 
 * This function returns true if the input character is 'Y' or 'y',
 * indicating a 'yes' response. It is used to handle user confirmations
 * consistently across different parts of the program.
 * 
 * @param input The character to check.
 * @return True if the input character is 'Y' or 'y', false otherwise.
 */
inline bool isYes(char input) {
    return input == 'Y' || input == 'y';
}

#endif // WORDCAT_H
