//B"H

#ifndef ASS_5_BATTLE_STATS_H
#define ASS_5_BATTLE_STATS_H

/**
 * @struct BattleResult
 * Encapsulates the numerical outcomes of a combat turn.
 * @var enemy_damage The amount of health points to deduct from the enemy.
 * @var player_heal The amount of health points the player recovers.
 * @var player_damage The amount of health points the player loses from the enemy's attack.
 */
struct BattleResult {
    int enemy_damage;
    int player_heal;
    int player_damage;
};

//enum used to indicate the state of the deck after an operation.
enum class deck_status {Empty,Not_Empty};

#endif //ASS_5_BATTLE_STATS_H