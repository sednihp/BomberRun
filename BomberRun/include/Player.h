#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

class Player
{
    private:
        const int startingLives;
        int lives;
        int levelScore, totalScore;

		Player& operator=(const Player&);
		Player(const Player&);

    public:
        Player();
        ~Player();

        const int getTotalScore() const { return totalScore; }
        const int getLevelScore() const { return levelScore; }
        const int getLives() const { return lives; }
        const bool isAlive() const { return lives > 0; }

        void startGame();
        void startLevel() { levelScore = 0; }
        void setScore(const int theScore);
        void loseLife() { --lives; }
};

#endif // PLAYER_H_INCLUDED
