// WordCatVec.h
#ifndef WORDCATVEC_H_
#define WORDCATVEC_H_

#include "WordCat.h"

/**
 * @class WordCatVec
 * @brief A class to represent a dynamic array of WordCat objects.
 */
class WordCatVec {
private:
    WordCat* word_category_array; // A pointer to the dynamic array of WordCat objects
    size_t capacity; // The capacity of the dynamic array
    size_t size; // The current size of the dynamic array

    /**
     * @brief Displays a menu to the user and returns the user's choice.
     * @return The user's choice as an integer
     */
    int menu() const;

    /**
     * @brief Performs an action based on the user's choice.
     * @param choice The user's choice as an integer
     */
    void perform(const int choice);

    /**
     * @brief Searches for a category in the array.
     * @param category The category to search for
     * @return A pointer to the found category, or nullptr if the category was not found
     */
    WordCat* search(const Word& category) const;

public:

    /**
     * @brief Default constructor. Initializes word_category_array to a new array with capacity 1, and sets capacity to 1 and size to 0.
     */
    WordCatVec();

    /**
     * @brief Destructor. Deallocates the memory reserved by word_category_array and sets capacity and size to 0.
     */
    ~WordCatVec();

    /**
     * @brief Copy constructor. Initializes word_category_array to a new array with the same capacity as the other object, and copies the elements from the other object's array.
     * @param other The WordCatVec object to copy
     * @throws std::runtime_error If the size of the other object exceeds its capacity
     */
    WordCatVec(const WordCatVec& other);

    /**
     * @brief Copy assignment operator. Replaces the current object's data with the data of the other object.
     * @param other The WordCatVec object to copy
     * @return A reference to the current object
     * @throws std::runtime_error If the size of the other object exceeds its capacity
     */
    WordCatVec& operator=(const WordCatVec& other);

    /**
     * @brief Move constructor. Takes ownership of the other object's data, and sets the other object's data to its default values.
     * @param other The WordCatVec object to move
     */
    WordCatVec(WordCatVec&& other) noexcept;

    /**
     * @brief Move assignment operator. Replaces the current object's data with the data of the other object, and sets the other object's data to its default values.
     * @param other The WordCatVec object to move
     * @return A reference to the current object
     */
    WordCatVec& operator=(WordCatVec&& other) noexcept;

    /**
     * @brief Runs the main loop of the program, displaying the menu and performing actions based on the user's choice.
     */
    void run();

    /**
     * @brief Adds a new category to the array. If the array is full, it is resized.
     * @param new_category The new category to add
     * @return true if the category was added successfully, false otherwise
     */
    bool addCategory(const WordCat& new_category);

    /**
     * @brief Removes a category from the array. If the array is less than half full after the removal, it is resized.
     * @param category_to_remove The category to remove
     * @return true if the category was removed successfully, false otherwise
     */
    bool removeCategory(const Word& category_to_remove);

    /**
     * @brief Checks if a category exists in the array.
     * @param category The category to check for
     * @return true if the category exists, false otherwise
     */
    bool lookup(const Word& category) const;

    /**
     * @brief Overloads the << operator to print the contents of the array.
     * @param sout The output stream to print to
     * @param wcv The WordCatVec object to print
     * @return The output stream
     */
    friend std::ostream& operator<<(std::ostream& sout, const WordCatVec& wcv);

    /**
     * @brief Loads categories from a file.
     * @param filename The path to the file to load from
     */
    void loadFromFile(const char* filename);

    /**
     * @brief Saves categories and words to a file.
     * @param filename The path to the file to save to
     */
    void saveToFile(const char* filename) const;

    /**
     * @brief Clears all categories from the array.
     */
    void clearCategories();
};

#endif // WORDCATVEC_H_