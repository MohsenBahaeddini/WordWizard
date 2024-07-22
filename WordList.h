// WordList.h
#ifndef WORDLIST_H
#define WORDLIST_H

#include "Word.h"
#include <iostream>
#include <stdexcept>

/**
 * @class WordList
 * @brief A class to represent a doubly linked list of Words.
 */
class WordList {
private:
    struct Node {
        Word theWord; ///< The word stored in this node
        Node* next; ///< Pointer to the next node
        Node* prev; ///< Pointer to the previous node

        /**
         * @brief Constructor for Node.
         * @param word The word to store in this node.
         * @param nxt Pointer to the next node.
         * @param prv Pointer to the previous node.
         */
        Node(const Word& word, Node* nxt = nullptr, Node* prv = nullptr)
            : theWord(word), next(nxt), prev(prv) {}

        Node() = delete; // Prevent default construction
        Node(const Node& other) = delete; // Prevent copy construction
        Node(Node&& other) = delete; // Prevent move construction
        Node& operator=(const Node& other) = delete; // Prevent copy assignment
        Node& operator=(Node&& other) = delete; // Prevent move assignment
        virtual ~Node() = default; // Default virtual destructor
    };

    Node* head; ///< Pointer to the first node in the list
    Node* tail; ///< Pointer to the last node in the list
    size_t size; ///< Number of nodes in the list

    // Private methods
    /**
     * @brief Releases ownership of all nodes in the list.
     */
    void releaseOwnership();

    /**
     * @brief Copies all nodes from another list into this list.
     * @param other The WordList to copy from.
     */
    void copy(const WordList& other);

    /**
     * @brief Searches for a node containing the specified word.
     * @param word The word to search for.
     * @return Pointer to the node containing the word, or nullptr if not found.
     */
    Node* search(const Word& word) const;

    /**
     * @brief Gets the node at the specified index.
     * @param n The index of the node.
     * @return Pointer to the node at the specified index, or nullptr if out of range.
     */
    Node* getWord(int n) const;

public:
    /**
     * @brief Default constructor. Initializes an empty list.
     */
    WordList();

    /**
     * @brief Destructor. Removes all nodes.
     */
    ~WordList();

    /**
     * @brief Copy constructor. Initializes head and tail to nullptr and size to 0, then copies all nodes from 'other' to this list.
     * @param other The WordList to copy from.
     */
    WordList(const WordList& other);

    /**
     * @brief Copy assignment operator. Checks for self-assignment, clears this list, then copies all nodes from 'other' to this list.
     * @param other The WordList to copy from.
     * @return A reference to this object.
     */
    WordList& operator=(const WordList& other);

    /**
     * @brief Move constructor. Takes ownership from 'other' and releases ownership of 'other'.
     * @param other The WordList to move from.
     */
    WordList(WordList&& other) noexcept;

    /**
     * @brief Move assignment operator. Checks for self-assignment, clears this list, takes ownership from 'other', and releases ownership of 'other'.
     * @param other The WordList to move from.
     * @return A reference to this object.
     */
    WordList& operator=(WordList&& other) noexcept;

    /**
     * @brief Returns the word in the head node.
     * @return The word in the head node.
     * @throws std::runtime_error if the list is empty.
     */
    const Word& front() const;

    /**
     * @brief Returns the word in the tail node.
     * @return The word in the tail node.
     * @throws std::runtime_error if the list is empty.
     */
    const Word& back() const;

    /**
     * @brief Inserts a new node at the head of this list.
     * @param word The word to insert.
     */
    void push_front(const Word& word);

    /**
     * @brief Removes the node at the head of this list and returns the removed node.
     * @return Pointer to the removed head node.
     * @throws std::runtime_error if the list is empty.
     */
    Node* pop_front();

    /**
     * @brief Inserts a new node at the tail of this list.
     * @param word The word to insert.
     */
    void push_back(const Word& word);

    /**
     * @brief Removes the node at the tail of this list and returns the removed node.
     * @return Pointer to the removed tail node.
     * @throws std::runtime_error if the list is empty.
     */
    Node* pop_back();

    /**
     * @brief Inserts a new node in the correct position to keep the list sorted.
     * @param word The word to insert.
     */
    void insertSorted(const Word& word);

    /**
     * @brief Removes all nodes from the list.
     */
    void clear();

    /**
     * @brief Removes the node containing the given word from the list.
     * @param word The word to remove.
     * @return true if the word was found and removed, false otherwise.
     */
    bool remove(const Word& word);

    /**
     * @brief Returns a copy of the word in the node at the given index.
     * @param index The index of the node.
     * @return A copy of the word in the node.
     * @throws std::runtime_error if the index is out of range.
     */
    Word fetchWord(int index) const;

    /**
     * @brief Determines whether this WordList is empty.
     * @return True if the list is empty, false otherwise.
     */
    inline bool isEmpty() const { return head == nullptr; };

    /**
     * @brief Checks if the given word is in the list.
     * @param word The word to look up.
     * @return true if the word is found in the list, false otherwise.
     */
    bool lookup(const Word& word) const;

    /**
     * @brief Returns a list of words starting with the given letter.
     * @param letter The initial letter of the words to return.
     * @return A list of words starting with the given letter.
     */
    WordList wordsStartingWith(const char letter) const;

    /**
     * @brief Prints the words in the list to the given output stream, with a maximum of n words per line.
     * @param os The output stream to print to.
     * @param n The maximum number of words per line.
     * @return The total number of words printed.
     */
    int print(std::ostream& os, const int n = 5) const;

    /**
     * @brief Overloads the insertion operator to print a WordList object.
     * @param sout The output stream to print to.
     * @param wl The WordList object to print.
     * @return The output stream.
     */
    friend std::ostream& operator<<(std::ostream& sout, const WordList& wl);
};

#endif // WORDLIST_H
