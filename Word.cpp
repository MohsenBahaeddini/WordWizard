#include "Word.h"

/**
 * @brief Default constructor. Initializes to empty word.
 */
Word::Word() : word_ptr(nullptr), size(0) {
    // Initialize word_ptr to nullptr and size to 0
}

/**
 * @brief Conversion constructor. Converts C-string to Word object.
 * @param str The C-string to convert.
 */
Word::Word(const char* str) : word_ptr(new char[strlen(str) + 1]), size(strlen(str)) {
    // Allocate memory for word_ptr and copy the C-string into it
    std::strcpy(word_ptr, str); // Copy the input string into word_ptr
}

/**
 * @brief Copy constructor. Performs deep copy of another Word object.
 * @param source The source Word object.
 */
Word::Word(const Word& source) : word_ptr(new char[source.size + 1]), size(source.size) {
    // Allocate memory for word_ptr and copy the content from source
    std::strcpy(word_ptr, source.word_ptr); // Copy the source string into word_ptr
}

/**
 * @brief Move constructor. Transfers ownership of resources from another Word object.
 * @param source The source Word object.
 */
Word::Word(Word&& source) noexcept : word_ptr(source.word_ptr), size(source.size) {
    // Transfer ownership of word_ptr and size from source to this object
    source.word_ptr = nullptr; // Set source's word_ptr to nullptr
    source.size = 0; // Set source's size to 0
}

/**
 * @brief Copy assignment operator. Performs deep copy and handles self-assignment.
 * @param source The source Word object.
 * @return Reference to the assigned object.
 */
Word& Word::operator=(const Word& source) {
    if (this != &source) { // Avoid self-assignment
        delete[] word_ptr; // Free existing resource
        word_ptr = new char[source.size + 1]; // Allocate new memory for word_ptr
        size = source.size; // Copy size from source
        std::strcpy(word_ptr, source.word_ptr); // Copy content from source to word_ptr
    }
    return *this; // Return the current object
}

/**
 * @brief Move assignment operator. Transfers ownership and handles self-assignment.
 * @param source The source Word object.
 * @return Reference to the assigned object.
 */
Word& Word::operator=(Word&& source) noexcept {
    if (this != &source) { // Avoid self-assignment
        delete[] word_ptr; // Free existing resource
        word_ptr = source.word_ptr; // Transfer ownership of word_ptr from source
        size = source.size; // Transfer ownership of size from source
        source.word_ptr = nullptr; // Set source's word_ptr to nullptr
        source.size = 0; // Set source's size to 0
    }
    return *this; // Return the current object
}

/**
 * @brief Destructor. Deallocates dynamically allocated memory.
 */
Word::~Word() {
    delete[] word_ptr; // Deallocate memory assigned to word_ptr
}

/**
 * @brief Gets the length of the word.
 * @return The length of the word.
 */
size_t Word::length() const {
    return size; // Return the size of the word
}

/**
 * @brief Gets the C-style string representation of the word.
 * @return The C-style string.
 */
const char* Word::c_str() const {
    return word_ptr; // Return the C-string representation of the word
}

/**
 * @brief Changes the word to a new Word object.
 * @param newWord The new Word object.
 */
void Word::changeWord(const Word& newWord) {
    *this = newWord; // Use the assignment operator to change the word
}

/**
 * @brief Changes the word to a new C-string.
 * @param newWord The new C-string.
 */
void Word::changeWord(const char* newWord) {
    *this = Word(newWord); // Utilize conversion constructor and assignment operator
}

/**
 * @brief Concatenates with another Word object using a delimiter.
 * @param other The other Word object.
 * @param delimiter The delimiter to use.
 * @return The concatenated Word object.
 */
Word Word::concat(const Word& other, const char* delimiter) const {
    size_t newSize = size + std::strlen(delimiter) + other.size; // Calculate the size of the new concatenated word
    char* newStr = new char[newSize + 1]; // Allocate memory for the new word

    std::strcpy(newStr, word_ptr); // Copy the current word into the new word
    std::strcat(newStr, delimiter); // Append the delimiter to the new word
    std::strcat(newStr, other.word_ptr); // Append the other word to the new word

    Word newWord(newStr); // Create a new Word object with the concatenated string
    delete[] newStr; // Deallocate the temporary buffer
    return newWord; // Return the new Word object
}

/**
 * @brief Compares alphabetically with another Word object.
 * @param other The other Word object.
 * @return True if this word is less than the other.
 */
bool Word::isLess(const Word& other) const {
    return std::strcmp(word_ptr, other.word_ptr) < 0; // Compare this word with the other word
}

/**
 * @brief Gets the character at a specific position.
 * @param n The position index.
 * @return The character at the given position.
 * @throws std::out_of_range If index is out of bounds.
 */
char Word::at(size_t n) const {
    if (n >= size) throw std::out_of_range("Index out of range"); // Throw exception if index is out of range
    return word_ptr[n]; // Return the character at the specified position
}

/**
 * @brief Reads a word from an input stream.
 * @param sin The input stream.
 */
void Word::read(std::istream& sin) {
    static char buffer[LONGEST_WORD_PLUS_ONE]; // Static buffer for input
    sin.getline(buffer, LONGEST_WORD_PLUS_ONE - 1); // Read input into buffer ensuring null-termination
    buffer[LONGEST_WORD_PLUS_ONE - 1] = '\0'; // Ensure buffer is null-terminated

    if (word_ptr) delete[] word_ptr; // Avoid memory leak by deleting existing word_ptr

    word_ptr = new char[std::strlen(buffer) + 1]; // Allocate space for the new word
    size = std::strlen(buffer); // Set size to the length of the buffer
    std::strcpy(word_ptr, buffer); // Copy buffer into word_ptr
}

/**
 * @brief Prints the word to an output stream.
 * @param out The output stream.
 */
void Word::print(std::ostream& out) const {
    if (word_ptr != nullptr) out << word_ptr; // Print the word to the output stream if not null
}

/**
 * @brief Overloaded insertion operator for output.
 * @param out The output stream.
 * @param word The Word object.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& out, const Word& word) {
    word.print(out); // Use the print method to insert the word into the output stream
    return out; // Return the output stream
}

/**
 * @brief Overloaded extraction operator for input.
 * @param in The input stream.
 * @param word The Word object.
 * @return The input stream.
 */
std::istream& operator>>(std::istream& in, Word& word) {
    word.read(in); // Use the read method to extract the word from the input stream
    return in; // Return the input stream
}

/**
 * @brief Overloaded equality operator.
 * @param lhs The left-hand side Word object.
 * @param rhs The right-hand side Word object.
 * @return True if both words are equal.
 */
bool operator==(const Word& lhs, const Word& rhs) {
    return std::strcmp(lhs.word_ptr, rhs.word_ptr) == 0; // Compare the C-string representations of the two words
}
