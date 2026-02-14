//b"h

#ifndef ASS_4_DECK_H
#define ASS_4_DECK_H
#include "Card.h"

/**
 * @class Deck
 * Represents a collection of Card objects using a dynamic array of pointers,
 * providing tools for deck management and card manipulation.
 * @member (Card**) array - Dynamic array of pointers to Card objects stored in the deck.
 * @member (int) size - The current number of cards present in the deck.
 * @member static (int) cnt_deck - counter used to track the total number of Deck instances created.
 */
class Deck {
    private:
    Card** array;
    int size;
    static int cnt_deck;

    public:

    /**
     * Default constructor.
     * Initializes an empty deck with no cards and increments the global deck counter.
     * @return A new instance of a Deck object.
     */
    Deck();

    /**
     * Copy constructor.
     * Performs a deep copy of another deck by allocating a new array and
     * creating new Card instances for each element. Increments the global deck counter.
     * @param other A reference to the source deck to be copied.
     * @return A new instance of a Deck object.
     */
    Deck(const Deck &other);

    /**
     * Destructor.
     * Safely deallocates all dynamically allocated Card objects and the
     * internal array of pointers, then decrements the global deck counter.
     */
    ~Deck();

    /**
     * Assignment operator.
     * Implements the copy-and-swap logic to perform a deep copy of the source deck.
     * Ensures self-assignment protection and manages memory by deallocating old
     * data before assigning new elements.
     * @param other A reference to the source deck to copy from.
     * @return A reference to the current deck (*this).
     */
    Deck& operator=(const Deck &other);

    /**
     * Addition assignment operator.
     * Prepends a new card to the end of the deck. This method performs a
     * deep copy of the provided card, shifts existing card pointers, and
     * reallocates the internal array to accommodate the new size.
     * @param other A reference to the card to be added.
     * @return A reference to the current deck (*this).
     */
    Deck& operator+=(const Card& other);

    /**
     * Subtraction assignment operator.
     * Removes 'n' cards from the top (first) of the deck. Deallocates the
     * memory of the removed cards and shrinks the internal array. If 'n'
     * exceeds or equals the deck size, the entire deck is cleared.
     * @param n The number of cards to remove.
     * @return A reference to the modified deck (*this).
     */
    Deck& operator-=(int n);

    /**
     * Peek method.
     * Prints the first 'n' cards of the deck to the console, starting from the
     * top-most card. If 'n' is greater than the deck size, it prints all
     * available cards.
     * @param n The number of cards to display from the end of the deck.
     * @return None.
     */
    void peek(int n) const;

    /**
     * Subscript operator.
     * Provides access to the card at the specified index. Assumes the index
     * is valid (0 to size-1) per the assignment instructions.
     * @param idx The index of the card to retrieve.
     * @return A reference to the card at the given index.
     */
    Card& operator[](int idx);

    /**
     * Subscript operator (const version).
     * Provides read-only access to the card at the specified index. Assumes the
     * index is valid (0 to size-1) per the assignment instructions.
     * @param idx The index of the card to retrieve.
     * @return A constant reference to the card at the given index.
     */
    const Card& operator[](int idx) const;

    /**
     * Output stream operator for the Deck class.
     * Formats and prints the entire deck as a comma-separated list enclosed in brackets.
     * For an empty deck, it prints "[]".
     * @param os The output stream to write to.
     * @param deck A reference to the deck object to be printed.
     * @return A reference to the output stream.
     */
    friend ostream& operator<<(ostream &os, const Deck &deck);

    /**
     * Size getter.
     * Returns the current number of cards stored in the deck.
     * @return The integer value of the size member.
     */
    int getSize() const {return size;}

    /**
     * Static deck counter getter.
     * Returns the total number of Deck instances currently active in the program.
     * @return The current value of the static cnt_deck member.
     */
    static int get_cnt_deck(){return cnt_deck;}

};
#endif //ASS_4_DECK_H