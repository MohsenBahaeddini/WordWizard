// WordCatVec.cpp
#include "WordCatVec.h"
#include <iostream>
#include <fstream> // To handle files
#include <cstring> 

/**
 * @brief Default constructor. Initializes the WordCatVec with a capacity of 1 and size 0.
 */
WordCatVec::WordCatVec() : word_category_array{ new WordCat[1] }, capacity{ 1 }, size{ 0 } {}

/**
 * @brief Destructor. Deallocates the memory used by the word_category_array.
 */
WordCatVec::~WordCatVec() {
    delete[] word_category_array; // Deletes the array to free memory
    capacity = 0; // Resets capacity to 0
    size = 0; // Resets size to 0
}

/**
 * @brief Copy constructor. Initializes a new WordCatVec object as a copy of an existing one.
 * @param other The WordCatVec to copy from.
 */
WordCatVec::WordCatVec(const WordCatVec& other) : 
    word_category_array{ new WordCat[other.capacity] }, 
    capacity{ other.capacity }, 
    size{ other.size } {
    for (size_t i = 0; i < other.size; ++i) { // Iterates over each element
        if (i < other.capacity) { // Checks if the index is within the capacity
            word_category_array[i] = other.word_category_array[i]; // Copies the element
        } else {
            throw std::runtime_error("Size exceeds capacity in copy constructor"); // Throws an error if size exceeds capacity
        }
    }
}

/**
 * @brief Copy assignment operator. Assigns the values of an existing WordCatVec object to another.
 * @param other The WordCatVec to copy from.
 * @return A reference to the current object.
 */
WordCatVec& WordCatVec::operator=(const WordCatVec& other) {
    if (this != &other) { // Checks for self-assignment
        delete[] word_category_array; // Deletes the old array
        capacity = 0; // Resets capacity
        size = 0; // Resets size

        word_category_array = new WordCat[other.capacity]; // Allocates memory for the new array
        capacity = other.capacity; // Sets the new capacity
        size = other.size; // Sets the new size
        for (size_t i = 0; i < other.size; ++i) { // Copies the elements
            if (i < other.capacity) {
                word_category_array[i] = other.word_category_array[i];
            } else {
                throw std::runtime_error("Size exceeds capacity in copy assignment operator"); // Throws an error if size exceeds capacity
            }
        }
    }
    return *this; // Returns a reference to the current object
}

/**
 * @brief Move constructor. Initializes a new WordCatVec object by taking ownership of the data in an existing one.
 * @param other The WordCatVec to move from.
 */
WordCatVec::WordCatVec(WordCatVec&& other) noexcept : word_category_array(other.word_category_array), capacity(other.capacity), size(other.size) {
    other.word_category_array = nullptr; // Sets the other's array pointer to null
    other.capacity = 0; // Resets the other's capacity
    other.size = 0; // Resets the other's size
}

/**
 * @brief Move assignment operator. Assigns the values of an existing WordCatVec object to another by moving data, not copying it.
 * @param other The WordCatVec to move from.
 * @return A reference to the current object.
 */
WordCatVec& WordCatVec::operator=(WordCatVec&& other) noexcept {
    if (this != &other) {
        delete[] word_category_array; // Deletes the old array
        capacity = 0; // Resets capacity
        size = 0; // Resets size

        word_category_array = other.word_category_array; // Takes ownership of the other's array
        capacity = other.capacity; // Takes ownership of the other's capacity
        size = other.size; // Takes ownership of the other's size

        other.word_category_array = nullptr; // Sets the other's array pointer to null
        other.capacity = 0; // Resets the other's capacity
        other.size = 0; // Resets the other's size
    }
    return *this; // Returns a reference to the current object
}

/**
 * @brief Displays a menu to the user and returns the user's choice.
 * @return The user's menu choice.
 */
int WordCatVec::menu() const {
    const int max_attempts{ 3 }; // Maximum number of input attempts allowed
    int attempts{ 0 }; // Counter for the number of attempts made
    int choice; // Variable to store the user's choice

    std::cout << "===========================\n";
    std::cout << "Word Vocabulary Center\n";
    std::cout << "===========================\n";
    std::cout << "1. Print all categories\n";
    std::cout << "2. Add a new category\n";
    std::cout << "3. Remove a category\n";
    std::cout << "4. Clear a category\n";
    std::cout << "5. Modify a category\n";
    std::cout << "6. Search all categories for a specific word\n";
    std::cout << "7. Show all the words starting with a given letter\n";
    std::cout << "8. Load from a text file\n";
    std::cout << "9. Save to a text file\n";
    std::cout << "0. Exit the program\n";
    std::cout << "===========================\n";

    while (attempts < max_attempts) { // Loop to allow a certain number of attempts for valid input
        if (attempts == 0) {
            std::cout << "Enter Your Choice: "; // Prompt for the first attempt
        } else {
            std::cout << "Please enter a valid choice: "; // Prompt for subsequent attempts
        }

        std::cin >> choice; // Read the user's choice
        if (std::cin.fail() || !(choice >= 0 && choice <= 9)) { // Check for input failure or choice not in the valid range
            std::cin.clear(); // Clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line

            attempts++; // Increment the attempt counter
            if (attempts != max_attempts) std::cout << "\nBad input. (" << max_attempts - attempts << " attempts remaining)\n";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line
            return choice; // Return the valid choice
        }
    }

    std::cout << "\nNo attempts remaining.\n"; // Inform the user that no attempts are left

    return 0; // Return 0 indicating that the user failed to enter a valid choice
}

/**
 * @brief Performs an action based on the user's menu choice.
 * @param choice The user's menu choice.
 */
void WordCatVec::perform(const int choice) {
    switch (choice) {
        case 1: {
            std::cout << "\n*** Printing all the category names ***\n";
            if (size == 0) { // If there are no categories
                std::cout << "No categories to print\n";
                std::cout << "Try adding a new category and words in the category\n";
            } else { // If there are categories
                for (size_t i = 0; i < size; ++i) { // Loop through each category
                    std::cout << word_category_array[i] << "\n"; // Print the category name and its words if any
                }
            }
            std::cout << "\n";
            break;
        }

        case 2: {
            Word input; // Variable to hold the user's input
            int inserted_word_count{ 0 }; // Counter for the number of words added

            std::cout << "\n*** Adding new category names ***\n";
            while (true) { // Infinite loop to keep asking for input
                std::cout << "Please enter the name of a category (or press ENTER to stop): ";

                std::cin >> input; // Read the word

                if (input.length() == 0) { // Check if the input is empty (user pressed ENTER)
                    std::cout << "\n";
                    break; // Exit the loop if input is empty
                }

                WordCat new_category(input);
                if (addCategory(new_category)) inserted_word_count++; // Increment the count if the word was successfully added
            }

            std::cout << "\n" << inserted_word_count << " new category name(s) added. ";
            break;
        }

        case 3: {
            Word input; // Variable to hold the user's input
            char user_confirmation; // Variable to hold the user's confirmation

            std::cout << "\n*** Removing a given category ***\n";
            std::cout << "Please enter the name of the category to remove (or press ENTER to cancel): ";

            std::cin >> input; // Read the word

            if (input.length() == 0) { // Check if the input is empty (user pressed ENTER)
                std::cout << "\n";
                break; // Exit the loop if input is empty
            }

            std::cout << "\nAre you sure you want to remove the category '" << input << "' ? (Y / N) : ";
            std::cin >> user_confirmation; // Get the user's confirmation

            if (isYes(user_confirmation)) { // If the user confirms the removal
                if (this->removeCategory(input)) { // If the category is removed successfully
                    std::cout << "\n'" << input << "' was successfully removed. ";
                } else { // If the category is not found
                    std::cout << "\n'" << input << "' could not be found. ";
                }
            } else { // If the user cancels the removal
                std::cout << "\nRemoving Operation cancelled. ";
            }
            break;
        }

        case 4: {
            Word input; // Variable to hold the user's input
            char user_confirmation; // Variable to hold the user's confirmation

            std::cout << "\n*** Clearing a category ***\n";
            std::cout << "Please enter the name of the category to clear (or press ENTER to cancel): ";
            
            std::cin >> input; // Read the word

            if (input.length() == 0) { // Check if the input is empty (user pressed ENTER)
                std::cout << "\n";
                break; // Exit the loop if input is empty
            }

            WordCat* found_category = this->search(input); // Search for the category

            if (found_category != nullptr) { // If the category is found
                std::cout << "\nAre you sure you want to clear the category '" << input << "' ? (Y / N) : ";
                std::cin >> user_confirmation; // Get the user's confirmation

                if (isYes(user_confirmation)) { // Proceed if the user confirms with 'Y' or 'y'
                    found_category->emptyCategory(); // Clear the category
                } else { // If the user cancels the clearing
                    std::cout << "\nClearing Operation cancelled. ";
                }
            } else { // If the category is not found
                std::cout << "\n'" << input << "' could not be found. ";
            }

            break;
        }

        case 5: {
            Word input; // Variable to hold the user's input

            std::cout << "\n*** Modifying a category ***\n";
            std::cout << "Please enter the name of the category to modify (or press ENTER to cancel): ";

            std::cin >> input; // Read the word

            if (input.length() == 0) { // Check if the input is empty (user pressed ENTER)
                std::cout << "\n";
                break; // Exit the loop if input is empty
            }

            WordCat* found_category = this->search(input); // Search for the category

            if (found_category != nullptr) { // If the category is found
                std::cout << "\nModifying the category '" << input << "'\n\n";
                found_category->run(); // Run the WordCat menu
            } else { // If the category is not found
                std::cout << "\n'" << input << "' could not be found. ";
            }

            break;
        }

        case 6: {
            Word input; // Variable to hold the user's input

            std::cout << "\n*** Searching all categories for a specific word ***\n";
            std::cout << "Please enter the word to search for in all categories (or press ENTER to cancel): ";

            std::cin >> input; // Read the word

            if (input.length() == 0) { // Check if the input is empty (user pressed ENTER)
                std::cout << "\n";
                break; // Exit the loop if input is empty
            }

            for (size_t i = 0; i < size; ++i) { // Loop through each category
                WordCat category_to_search(word_category_array[i]); // Create a WordCat object for searching
                Word category_to_search_name = category_to_search.getCategoryName(); // Get the name of the category

                if (category_to_search.lookupWordInList(input)) { // If the word is found in the category
                    std::cout << "\nCategory '" << category_to_search_name << "' has word " << input;
                } else { // If the word is not found in the category
                    std::cout << "\nCategory '" << category_to_search_name << "' does not have word " << input;
                }
            }

            std::cout << "\n\n";

            break;
        }

        case 7: {
            char first_letter; // Variable to store the first letter

            std::cout << "\n*** Showing all the words in all categories starting with a given letter ***\n";
            std::cout << "Please enter the first letter of the words to search for: ";

            std::cin >> first_letter; // Read the first letter from the user
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line

            for (size_t i = 0; i < size; ++i) { // Loop through each category
                WordCat category_to_search(word_category_array[i]); // Create a WordCat object for searching
                Word category_to_search_name = category_to_search.getCategoryName(); // Get the name of the category

                WordList same_first_letter_words = category_to_search.getWordsStartingWithLetter(first_letter); // Get words starting with the given letter

                if (!same_first_letter_words.isEmpty()) { // If there are words starting with the given letter
                    std::cout << "\nWord(s) beginning with '" << first_letter << "' in the category '" << category_to_search_name << "':\n";
                    std::cout << same_first_letter_words; // Print the words
                } else { // If there are no words starting with the given letter
                    std::cout << "\nSorry, no words beginning with '" << first_letter << "' in the category '" << category_to_search_name << "'.\n";
                }
            }
            std::cout << "\n";
            break;
        }

        case 8: {
            char file_path[256]; // Array to store the file path

            std::cout << "\n*** Loading categories and words from a text file ***\n";
            std::cout << "Please enter the path to the file containing categories and words (or press ENTER to cancel): ";
            std::cin.getline(file_path, 256); // Get the file path from the user

            loadFromFile(file_path);
            break;
        }

        case 9: {
            char file_path[256]; // Array to store the file path

            std::cout << "\n*** Saving categories and words to a text file ***\n";
            std::cout << "Please enter the path to the file where you want to save categories and words (or press ENTER to cancel): ";
            std::cin.getline(file_path, 256); // Get the file path from the user

            saveToFile(file_path);
            break;
        }

        default:
            std::cout << "Invalid choice. Please try again.\n"; // Inform the user that the choice was invalid
            break;
    }
}

/**
 * @brief Runs the main loop of the program, displaying the menu and performing actions based on the user's choice.
 */
void WordCatVec::run() {
    int choice = this->menu(); // Call the menu function and get the user's choice
    while (choice != 0) { // Continue until the user chooses to exit (option 0)
        perform(choice); // Perform the action corresponding to the user's choice
        std::cout << "Returning to menu...\n\n"; // Inform the user that the program is returning to the menu
        choice = this->menu(); // Call the menu function again to get the next choice
    }

    char confirm_exit; // Variable to store the user's confirmation to exit
    std::cout << "\nAre you sure you want to exit? (Y/N): "; // Ask the user to confirm exit
    std::cin >> confirm_exit; // Read the user's response
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the rest of the line

    if (isYes(confirm_exit)) { // If the user confirms to exit
        std::cout << "\nExiting...\n\nGoodbye.\n"; // Print an exit message
    } else { // If the user does not confirm to exit
        std::cout << "\nReturning to menu...\n\n"; // Inform the user that the program is returning to the menu
        run();  // Call the run function again to return to the menu
    }
}

/**
 * @brief Adds a new category to the array.
 * @param new_category The new category to add.
 * @return True if the category was successfully added, false otherwise.
 */
bool WordCatVec::addCategory(const WordCat& new_category) {
    if (lookup(new_category.getCategoryName())) { // Check if the category already exists
        std::cout << "\nThe category '" << new_category.getCategoryName() << "' already exists!\n";
        return false; // Return false as the category was not added
    }

    if (size == capacity) { // If the array is full
        size_t new_capacity = capacity * 2; // Double the capacity
        WordCat* new_category_array = new WordCat[new_capacity]; // Create a new array with the new capacity

        for (size_t i = 0; i < size; ++i) { // Loop through each category
            if (i < new_capacity) {
                new_category_array[i] = word_category_array[i]; // Copy each category
            } else {
                throw std::runtime_error("Size exceeds capacity"); // Throw an error if the size exceeds the new capacity
            }
        }

        delete[] word_category_array; // Delete the old array

        word_category_array = new_category_array; // Set the pointer to the new array
        capacity = new_capacity; // Update the capacity
    }

    if (size < capacity) { // If there is space in the array
        word_category_array[size++] = new_category; // Add the new category and increment the size
    } else {
        throw std::runtime_error("Size exceeds capacity"); // Throw an error if there is no space left in the array
    }

    return true; // Return true as the category was successfully added
}

/**
 * @brief Removes a category from the array.
 * @param category_to_remove The name of the category to remove.
 * @return True if the category was successfully removed, false otherwise.
 */
bool WordCatVec::removeCategory(const Word& category_to_remove) {
    for (size_t i = 0; i < size; ++i) { // Loop through the categories
        if (word_category_array[i].getCategoryName() == category_to_remove) { // Compare the category to remove with the current category
            for (size_t j = i; j < size - 1; ++j) { // Shift all elements to the left
                word_category_array[j] = word_category_array[j + 1];
            }
            size--; // Decrement the size of the array

            if (size < capacity / 2) { // If the size is less than half the capacity, resize the array
                size_t new_capacity = (capacity / 2 > 1) ? capacity / 2 : 1; // Calculate the new capacity

                WordCat* new_category_array = new WordCat[new_capacity]; // Create a new array with the new capacity

                for (size_t i = 0; i < size; ++i) { // Loop through each category
                    if (i < new_capacity) {
                        new_category_array[i] = word_category_array[i];// Copy the categories to the new array
                    } else {
                        throw std::runtime_error("Size exceeds capacity"); // Error if the new capacity is exceeded
                    }
                }

                delete[] word_category_array; // Delete the old array

                word_category_array = new_category_array; // Point to the new array
                capacity = new_capacity; // Update the capacity
            }

            return true; // Return true if the category was removed
        }
    }
    return false; // Return false if the category was not found
}

/**
 * @brief Searches for a category in the array.
 * @param category The name of the category to search for.
 * @return A pointer to the found WordCat, or nullptr if not found.
 */
WordCat* WordCatVec::search(const Word& category) const {
    for (size_t i = 0; i < size; ++i) { // Loop through the categories
        if (word_category_array[i].getCategoryName() == category) { // Compare the category to search with the current category
            return &word_category_array[i]; // Return a pointer to the found WordCat
        }
    }
    return nullptr; // Return nullptr if the WordCat is not found
}

/**
 * @brief Checks if a category exists in the array.
 * @param category The name of the category to check.
 * @return True if the category is found, false otherwise.
 */
bool WordCatVec::lookup(const Word& category) const {
    return search(category) != nullptr; // Return true if the category is found, false otherwise
}

/**
 * @brief Overloads the << operator to print a WordCatVec object.
 * @param sout The output stream.
 * @param wcv The WordCatVec to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& sout, const WordCatVec& wcv) {
    for (size_t i = 0; i < wcv.size; ++i) { // Loop through the categories
        sout << wcv.word_category_array[i] << "\n"; // Output each category
    }
    return sout; // Return the ostream object
}

/**
 * @brief Trims leading and trailing spaces from a string in place.
 * 
 * This function modifies the input string by removing leading and trailing
 * spaces. It also shifts the trimmed content to the start of the original
 * string buffer if necessary.
 * 
 * @param str The input string to be trimmed.
 */
void trim(char* str) {
    char* start = str; // Pointer to the start of the string
    char* end = str + strlen(str) - 1; // Pointer to the end of the string

    // Trim leading spaces
    while (isspace((unsigned char)*start)) start++; // Move start pointer past any leading spaces

    // Trim trailing spaces
    while (end > start && isspace((unsigned char)*end)) end--; // Move end pointer before any trailing spaces

    // Null terminate after the last non-space character
    *(end + 1) = '\0'; // Place the null terminator right after the last non-space character

    // Move the adjusted string to the start if necessary
    if (start > str) { // If the start pointer moved past the beginning of the original string
        memmove(str, start, end - start + 2); // Shift the trimmed string to the beginning (including null terminator)
    }
}

/**
 * @brief Loads categories and words from a file.
 * 
 * This function reads from a specified file, processing lines to categorize
 * words under appropriate categories indicated by lines starting with '#'.
 * It trims spaces from each line and processes only non-empty lines.
 * 
 * @param filename The path to the file to load from.
 */
void WordCatVec::loadFromFile(const char* filename) {
    std::ifstream file(filename); // Open the file for reading
    if (!file) { // Check if the file was opened successfully
        std::cerr << "Error opening file: " << filename << std::endl; // Print error message if file cannot be opened
        return; // Exit the function
    }

    char line[256]; // Buffer to store each line read from the file
    WordCat* currentCategory = nullptr; // Pointer to keep track of the current category
    while (file.getline(line, 256)) { // Read each line from the file
        trim(line); // Trim leading and trailing spaces from the line

        if (line[0] == '#') { // Check if the line indicates a new category
            if (currentCategory != nullptr) { // If there's an existing category being processed
                addCategory(*currentCategory); // Add the existing category to the list
                delete currentCategory; // Delete the current category to free memory
            }
            // Create a new category, ensuring the category name is also trimmed
            char* categoryName = line + 1; // Skip the '#' character to get the category name
            trim(categoryName); // Trim spaces from the category name
            currentCategory = new WordCat(Word(categoryName)); // Create a new WordCat object for the category
        } else if (currentCategory != nullptr && line[0] != '\0') { // Check if line is not empty and there's an active category
            currentCategory->insertWord(Word(line)); // Add the word to the current category
        }
    }
    if (currentCategory != nullptr) { // After reading all lines, if there's an active category
        addCategory(*currentCategory); // Add the final category to the list
        delete currentCategory; // Delete the current category to free memory
    }

    file.close(); // Close the file
    std::cout << "Loaded categories from " << filename << std::endl; // Print confirmation message
}

/**
 * @brief Saves categories and words to a file.
 * @param filename The name of the file to save to.
 */
void WordCatVec::saveToFile(const char* filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (size_t i = 0; i < size; ++i) {
        file << "#" << word_category_array[i].getCategoryName() << "\n";
        word_category_array[i].getWordList().print(file, 5); // Print up to 5 words per line
        file << "\n"; // Adding a new line after each category for better readability
    }

    file.close();
    std::cout << "Saved categories to " << filename << std::endl;
}

/**
 * @brief Clears all categories from the array.
 */
void WordCatVec::clearCategories() {
    delete[] word_category_array;
    word_category_array = new WordCat[1];
    capacity = 1;
    size = 0;
}
