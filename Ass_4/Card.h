//b"h

#ifndef ASS_4_CARD_H
#define ASS_4_CARD_H
#include <iostream>
using namespace std;

/**
 * Represents card object stores a rank (char) sign (char) and a numeric value (int).
 * The class provides various constructors for initialization and
 * overloaded operators to compare cards or print them.
 */
class Card {
    private:
    char rank;
    char sign;
    int value;
    int calc_val() const;

    public:

    /**
     * Default constructor.
     * Initializes a new Card object with default placeholder values.
     * The rank and sign are set to 'Z', and the numeric value is set to 0.
     * @return A new instance of a Card object.
     */
    Card();

    /**
     * Parameterized constructor.
     * Initializes a card with a specific rank and sign, then calculates
     * its numeric value using an internal helper method.
     * @param rank The character representing the card's rank.
     * @param sign The character representing the card's sign.
     * @return A new instance of a Card object.
     */
    Card(char rank, char sign);

    /**
     * char*-based constructor.
     * Creates a new card using a C-string that contains rank and sign.
     * It calls the parameterized constructor using the first two characters.
     * @param RS A pointer to a character array (e.g., "AS").
     * @return A new instance of a Card object.
     */
    Card(const char* RS);

    /**
     * Copy constructor.
     * Creates a new card by copying the rank, sign, and value from an existing card.
     * @param card A reference to the card object to be copied.
     * @return A new instance of a Card object.
     */
    Card(const Card &card);

    /**
     * Destructor.
     * Cleans up the card object when it is destroyed.
     * @return None.
     */
    ~Card();

    /**
     * Assignment operator.
     * Copies the data members from the source card to the current card.
     * Since all members are primitive, a direct assignment is performed.
     * @param other A reference to the source card to copy from.
     * @return A reference to the current card (*this).
     */
    Card& operator=(const Card &other);

    /**
     * Equality operator.
     * Checks if the current card is identical to another card by comparing
     * both their rank and their sign.
     * @param other A reference to the card to compare with.
     * @return True if both rank and sign are equal, false otherwise.
    */
    bool operator==(const Card& other) const;

    /**
     * Inequality operator.
     * Checks if the current card is different from another card by reusing
     * the equality operator logic.
     * @param other A reference to the card to compare with.
     * @return True if the cards are not equal, false otherwise.
     */
    bool operator!=(const Card& other) const;

    /**
     * Greater-than operator.
     * Compares two cards based on their numeric value and rank. If ranks are
     * equal, it compares based on the sign hierarchy. Includes special
     * logic to handle cases where different ranks share the same numeric value.
     * @param other A reference to the card to compare against.
     * @return True if the current card is stronger than the other, false otherwise.
     */
    bool operator>(const Card& other) const;

    /**
     * Greater-than-or-equal operator.
     * Determines if the current card is greater than or equal to another card
     * by combining the logic of the equality and greater-than operators.
     * @param other A reference to the card to compare against.
     * @return True if the current card is greater than or equal to the other, false otherwise.
     */
    bool operator>=(const Card& other) const;

    /**
     * Less-than operator.
     * Determines if the current card is weaker than another card by
     * reversing the logic of the greater-than operator.
     * @param other A reference to the card to compare against.
     * @return True if the current card is less than the other, false otherwise.
     */
    bool operator<(const Card& other) const;

    /**
     * Less-than-or-equal operator.
     * Determines if the current card is smaller than or equal to another card
     * by reversing the logic of the greater-than-or-equal operator.
     * @param other A reference to the card to compare against.
     * @return True if the current card is less than or equal to the other, false otherwise.
     */
    bool operator<=(const Card& other) const;

    /**
     * Output stream operator.
     * Prints the card's rank and sign characters to the output stream.
     * @param os The output stream to write to.
     * @param card A reference to the card object to be printed.
     * @return A reference to the output stream.
     */
    friend ostream& operator<<(ostream &os, const Card &card);
};

#endif //ASS_4_CARD_H