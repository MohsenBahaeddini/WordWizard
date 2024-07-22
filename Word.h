// Word.h
#ifndef WORD_H  // Checks if WORD_H is not defined. If WORD_H is not defined, it means the header file has not been included yet in this translation unit.
#define WORD_H  // defines the macro WORD_H. This ensures that if this header file is included again, the compiler will know it has already been included and will skip its contents to prevent multiple inclusions.

#include <iostream> // Provides input and output stream functionalities
#include <cstring>  // Provides functions for C-style string manipulation

/**
 * @class Word
 * @brief Class to represent a dynamically allocated word.
 */
class Word {
private:
    char* word_ptr; ///< Pointer to the dynamically allocated array of characters
    size_t size; ///< Size of the word

public:
    static constexpr int LONGEST_WORD_PLUS_ONE = 65; ///< Maximum length of a word plus one

    /**
     * @brief Default constructor. Initializes to empty word.
     */
    Word();

    /**
     * @brief Conversion constructor. Converts C-string to Word object.
     * @param str The C-string to convert.
     */
    Word(const char* str);

    /**
     * @brief Copy constructor. Performs deep copy of another Word object.
     * @param source The source Word object.
     */
    Word(const Word& source);

    /**
     * @brief Move constructor. Transfers ownership of resources from another Word object.
     * @param source The source Word object.
     */
    Word(Word&& source) noexcept;

    /**
     * @brief Copy assignment operator. Performs deep copy and handles self-assignment.
     * @param source The source Word object.
     * @return Reference to the assigned object.
     */
    Word& operator=(const Word& source);

    /**
     * @brief Move assignment operator. Transfers ownership and handles self-assignment.
     * @param source The source Word object.
     * @return Reference to the assigned object.
     */
    Word& operator=(Word&& source) noexcept;

    /**
     * @brief Destructor. Deallocates dynamically allocated memory.
     */
    ~Word();

    /**
     * @brief Gets the length of the word.
     * @return The length of the word.
     */
    size_t length() const;

    /**
     * @brief Gets the C-style string representation of the word.
     * @return The C-style string.
     */
    const char* c_str() const;

    /**
     * @brief Changes the word to a new Word object.
     * @param newWord The new Word object.
     */
    void changeWord(const Word& newWord);

    /**
     * @brief Changes the word to a new C-string.
     * @param newWord The new C-string.
     */
    void changeWord(const char* newWord);

    /**
     * @brief Concatenates with another Word object using a delimiter.
     * @param other The other Word object.
     * @param delimiter The delimiter to use.
     * @return The concatenated Word object.
     */
    Word concat(const Word& other, const char* delimiter = " ") const;

    /**
     * @brief Compares alphabetically with another Word object.
     * @param other The other Word object.
     * @return True if this word is less than the other.
     */
    bool isLess(const Word& other) const;

    /**
     * @brief Gets the character at a specific position.
     * @param n The position index.
     * @return The character at the given position.
     */
    char at(size_t n) const;

    /**
     * @brief Reads a word from an input stream.
     * @param sin The input stream.
     */
    void read(std::istream& sin);

    /**
     * @brief Prints the word to an output stream.
     * @param out The output stream.
     */
    void print(std::ostream& out) const;

    /**
     * @brief Overloaded insertion operator for output.
     * @param out The output stream.
     * @param word The Word object.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& out, const Word& word);

    /**
     * @brief Overloaded extraction operator for input.
     * @param in The input stream.
     * @param word The Word object.
     * @return The input stream.
     */
    friend std::istream& operator>>(std::istream& in, Word& word);

    /**
     * @brief Overloaded equality operator.
     * @param lhs The left-hand side Word object.
     * @param rhs The right-hand side Word object.
     * @return True if both words are equal.
     */
    friend bool operator==(const Word& lhs, const Word& rhs);
};

#endif // WORD_H
