#include "Player.h"

Player::Player() : startingLives(1),
					lives(startingLives),                
					levelScore(0),
                    totalScore(0)
{

}

Player::~Player()
{

}

//To start the game, reset the scores and lives
void Player::startGame()
{
    levelScore = 0;
    totalScore = 0;
    lives = startingLives;
}

//set the players level score as the score they just achieved 
//then add this score to their total score
void Player::setScore(const int theScore)
{
    levelScore = theScore;

	totalScore += levelScore;
}
