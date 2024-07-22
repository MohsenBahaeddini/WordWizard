// WordList.cpp
#include "WordList.h"
#include <iostream>

// Default constructor. Initializes an empty list.
WordList::WordList() : head(nullptr), tail(nullptr), size(0) {}

/**
 * @brief Destructor. Removes all nodes.
 */
WordList::~WordList() {
    clear(); // Remove all nodes
}

/**
 * @brief Copy constructor. Initializes head and tail to nullptr and size to 0, then copies all nodes from 'other' to this list.
 * @param other The WordList to copy from.
 */
WordList::WordList(const WordList& other) : head(nullptr), tail(nullptr), size(0) {
    copy(other); // Copy all nodes from 'other' to this list
}

/**
 * @brief Copy assignment operator. Checks for self-assignment, clears this list, then copies all nodes from 'other' to this list.
 * @param other The WordList to copy from.
 * @return A reference to this object.
 */
WordList& WordList::operator=(const WordList& other) {
    if (this != &other) { // Check for self-assignment
        clear(); // Clear this list
        copy(other); // Copy all nodes from 'other' to this list
    }
    return *this; // Return a reference to this object
}

/**
 * @brief Move constructor. Takes ownership from 'other' and releases ownership of 'other'.
 * @param other The WordList to move from.
 */
WordList::WordList(WordList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
    other.releaseOwnership(); // Release ownership of 'other'
}

/**
 * @brief Move assignment operator. Checks for self-assignment, clears this list, takes ownership from 'other', and releases ownership of 'other'.
 * @param other The WordList to move from.
 * @return A reference to this object.
 */
WordList& WordList::operator=(WordList&& other) noexcept {
    if (this != &other) { // Check for self-assignment
        clear(); // Clear this list
        head = other.head; // Take ownership from 'other'
        tail = other.tail; // Take ownership from 'other'
        size = other.size; // Take ownership from 'other'
        other.releaseOwnership(); // Release ownership of 'other'
    }
    return *this; // Return a reference to this object
}

/**
 * @brief Returns the word in the head node.
 * @return The word in the head node.
 * @throws std::runtime_error if the list is empty.
 */
const Word& WordList::front() const {
    if (isEmpty()) throw std::runtime_error("List is empty");
    return head->theWord; // Return the word in the head node
}

/**
 * @brief Returns the word in the tail node.
 * @return The word in the tail node.
 * @throws std::runtime_error if the list is empty.
 */
const Word& WordList::back() const {
    if (isEmpty()) throw std::runtime_error("List is empty");
    return tail->theWord; // Return the word in the tail node
}

/**
 * @brief Inserts a new node at the head of this list.
 * @param word The word to insert.
 */
void WordList::push_front(const Word& word) {
    Node* newNode = new Node(word, head); // Create a new node
    if (isEmpty()) {
        head = tail = newNode; // If list is empty, head and tail are the new node
    } else {
        head->prev = newNode; // Update previous head's previous pointer
        head = newNode; // Update head to new node
    }
    size++; // Increment size
}

/**
 * @brief Removes the node at the head of this list and returns it.
 * This method provides direct access to the node, facilitating external use or reassignment.
 * @return Node* Pointer to the removed head node.
 * @throws std::runtime_error if the list is empty, indicating no nodes to remove.
 */
WordList::Node* WordList::pop_front() {
    if (isEmpty()) throw std::runtime_error("List is empty");

    Node* oldHead = head; // Save the current head node
    head = head->next; // Move the head pointer to the next node

    if (head) {
        head->prev = nullptr; // Set the new head's prev pointer to nullptr
    } else {
        tail = nullptr; // If the list becomes empty, also set tail to nullptr
    }

    oldHead->next = nullptr; // Disconnect the old head from the list
    size--; // Decrement the size of the list
    return oldHead; // Return the old head node
}

/**
 * @brief Inserts a new node at the tail of this list.
 * @param word The word to insert.
 */
void WordList::push_back(const Word& word) {
    Node* newNode = new Node(word, nullptr, tail); // Create a new node

    if (tail != nullptr) {
        tail->next = newNode; // If the list isn't empty, set the next pointer of the current tail node to the new node.
    }

    tail = newNode; // The new node is now the tail of the list.

    if (head == nullptr) {
        head = newNode; // If the list was empty, the new node is also the head of the list.
    }

    size++; // Increment the size of the list.
}

/**
 * @brief Removes the node at the tail of this list and returns it.
 * This method allows for managing the node outside the WordList structure,
 * particularly useful for custom memory management or advanced manipulations.
 * @return Node* Pointer to the removed tail node.
 * @throws std::runtime_error if the list is empty, indicating no nodes to remove.
 */
WordList::Node* WordList::pop_back() {
    if (isEmpty()) throw std::runtime_error("List is empty");

    Node* oldTail = tail; // Save the current tail node
    tail = tail->prev; // Move the tail pointer to the previous node

    if (tail) {
        tail->next = nullptr; // Set the new tail's next pointer to nullptr
    } else {
        head = nullptr; // If the list becomes empty, also set head to nullptr
    }

    oldTail->prev = nullptr; // Disconnect the old tail from the list
    size--; // Decrement the size of the list
    return oldTail; // Return the old tail node
}

/**
 * @brief Inserts a new node in the correct position to keep the list sorted.
 * @param word The word to insert.
 */
void WordList::insertSorted(const Word& word) {
    if (head == nullptr || word.isLess(front())) {
        push_front(word); // If the list is empty or the word is less than the head, use push_front
    } else if (back().isLess(word)) { // If the new node should be inserted at the end
        push_back(word); // Use push_back
    } else { // The new node should be inserted in the middle
        Node* current = head->next; // Initialize current node as the second node
        Node* previous = head; // Initialize previous node as head

        while (current != nullptr && current->theWord.isLess(word)) { // Traverse the list to find the correct position
            previous = current; // Update previous to current
            current = current->next; // Move to the next node
        }

        Node* newNode = new Node(word, current, previous); // Create a new node for the word
        previous->next = newNode; // The next pointer of the previous node points to the new node
        
        if (current != nullptr) {
            current->prev = newNode; // The previous pointer of the current node points to the new node
        } else {
            tail = newNode; // The new node should be inserted at the end
        }

        size++; // Increment the size of the list.
    }
}

/**
 * @brief Removes all nodes from the list.
 */
void WordList::clear() {
    while (!isEmpty()) {
        pop_front(); // Remove the front node of the list while the list is not empty
    }
}

/**
 * @brief Removes the node containing the given word from the list.
 * @param word The word to remove.
 * @return true if the word was found and removed, false otherwise.
 */
bool WordList::remove(const Word& word) {
    Node* node = search(word); // Search for the node containing the word

    if (node == nullptr) {
        return false; // If the word is not found, return false
    }

    if (node->prev != nullptr) {
        node->prev->next = node->next; // If the node has a previous node, update the next pointer of the previous node
    } else {
        head = node->next; // If the node is the head of the list, update the head pointer
    }

    if (node->next != nullptr) {
        node->next->prev = node->prev; // If the node has a next node, update the prev pointer of the next node
    } else {
        tail = node->prev; // If the node is the tail of the list, update the tail pointer
    }

    delete node; // Delete the node and decrement the size of the list
    size--; // Decrement the size of the list

    return true; // Return true to indicate successful removal
}

/**
 * @brief Returns a copy of the word in the node at the given index.
 * @param index The index of the node.
 * @return The word at the given index.
 * @throws std::runtime_error if the index is out of range.
 */
Word WordList::fetchWord(int index) const {
    Node* node = getWord(index); // Get the node at the given index
    if (node == nullptr) throw std::runtime_error("Index out of range"); // If the node is nullptr, throw a runtime error
    return node->theWord; // Return a copy of the word in the node
}

// /**
//  * @brief Determines whether this WordList is empty.
//  * @return true if the list is empty, false otherwise.
//  */
// inline bool WordList::isEmpty() const {
//     return head == nullptr; // The list is empty if the head pointer is null or size == 0
// }

/**
 * @brief Checks if the given word is in the list.
 * @param word The word to check.
 * @return true if the word is found, false otherwise.
 */
bool WordList::lookup(const Word& word) const {
    return search(word) != nullptr; // If the word is found in the list, return true, otherwise, return false
}

/**
 * @brief Returns a list of words starting with the given letter.
 * @param letter The initial letter of the words to return.
 * @return A WordList containing words starting with the given letter.
 */
WordList WordList::wordsStartingWith(const char letter) const {
    WordList initialLetterWords; // Words starting with the given letter

    Node* node = head; // Start at the head of the list
    while (node != nullptr) { // Traverse the list until the end
        if (node->theWord.at(0) == letter) { // If the word starts with the given letter
            initialLetterWords.push_back(node->theWord); // Add it to the list of words starting with the given letter
        }
        node = node->next; // Move to the next node in the list
    }

    return initialLetterWords; // Return the list of words starting with the given letter
}

/**
 * @brief Prints the words in the list to the given output stream, with a maximum of n words per line.
 * @param sout The output stream.
 * @param n The maximum number of words per line.
 * @return The total number of words printed.
 */
int WordList::print(std::ostream& sout, const int n) const {
    int wordCount{ 0 }; // Initialize word count to 0

    Node* node = head; // Start from the head of the list
    while (node != nullptr) { // Traverse the list until the end
        size_t len = node->theWord.length(); // Get the length of the word

        if (n != 1) {
            size_t padding = len >= 15 ? 0 : 15 - len; // Calculate the number of spaces needed

            for (int i = 0; i < padding; ++i) {
                sout << ' '; // Add spaces to the output stream
            }
        }

        sout << node->theWord; // Output the word

        if (++wordCount % n == 0 || n == 1) {
            sout << "\n"; // Start a new line if the word count is a multiple of n or n equals 1
        } else {
            sout << " "; // Add a space after the word if n is not 1
        }

        node = node->next; // Move to the next node in the list
    }

    if (wordCount % n != 0 && n != 1) {
        sout << "\n"; // Add a newline at the end if the last line contains less than n words and n is not 1
    }

    return wordCount; // Return the total number of words printed
}

/**
 * @brief Overloaded insertion operator. Prints the WordList to an output stream.
 * @param sout The output stream.
 * @param wl The WordList to print.
 * @return The output stream.
 */
std::ostream& operator<<(std::ostream& sout, const WordList& wl) {
    wl.print(sout); // Call the print function of the WordList object
    return sout;  // Return the output stream
}

/**
 * @brief Releases ownership of all nodes in the list.
 */
void WordList::releaseOwnership() {
    head = nullptr; // Set the head pointer to nullptr, indicating that the list no longer has a first node
    tail = nullptr; // Set the tail pointer to nullptr, indicating that the list no longer has a last node
    size = 0; // Set the size to 0, indicating that the list no longer contains any nodes
}

/**
 * @brief Copies all nodes from another list into this list.
 * @param other The WordList to copy from.
 */
void WordList::copy(const WordList& other) {
    head = nullptr; // This is an empty list, for now
    tail = nullptr; // This is an empty list, for now
    size = 0; // No nodes, yet

    if (other.isEmpty()) return; // Nothing to do

    Node* current = other.head; // First node to copy into this list
    head = new Node(current->theWord, nullptr, nullptr); // First node copied
    tail = head; // Both head and tail point to the first node
    size = 1; // First node counted

    Node* lastNode = head; // Last node copied into this list
    current = current->next; // Next node to copy into this list
    while (current) { // While other list has nodes to copy into this list
        Node* newNode = new Node(current->theWord, nullptr, lastNode); // Allocate a new node with current data and link to lastNode
        lastNode->next = newNode; // Append the new node
        tail = newNode; // Tail always points to the last node

        lastNode = newNode; // Update lastNode
        current = current->next; // Advance to next node in other list

        size++; // Count the newly added node
    }
}

/**
 * @brief Searches for a node containing the given word in the list.
 * @param word The word to search for.
 * @return A pointer to the node containing the word, or nullptr if not found.
 */
WordList::Node* WordList::search(const Word& word) const {
    Node* node = head; // Start at the head of the list

    while (node != nullptr) { // Traverse the list until the end
        if (strcmp(node->theWord.c_str(), word.c_str()) == 0) {
            return node; // If they match, return the current node
        }
        node = node->next; // Move to the next node in the list
    }

    return nullptr; // If no match was found, return nullptr
}

/**
 * @brief Returns a pointer to the node at the given index in the list.
 * @param n The index of the node.
 * @return A pointer to the node at the given index, or nullptr if out of range.
 */
WordList::Node* WordList::getWord(const int n) const {
    if (n < 0 || n >= size) { // Check if the index is valid
        return nullptr; // If the index is out of bounds, return nullptr
    }

    Node* node = head; // Start at the head of the list
    for (int i = 0; i < n; i++) {
        node = node->next; // Follow the 'next' pointers n times to reach the nth node
    }

    return node; // Return a pointer to the nth node
}
