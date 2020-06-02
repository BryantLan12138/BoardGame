#include "Score.h"
Score::Score(){
    roundScore = 0;
    totalScore = 0;
}

void Score::scoreTile(char** wall)
{
    roundScore = 0;
    for (int row = 0; row < MOSAIC_LENGTH; row++)
    {
        for (int col = 0; col < MOSAIC_LENGTH; col++)
        {
            if (row > 0 && col > 0)
            {
                if (wall[row][col] != '.'){
                    roundScore++;
                    if (wall[row - 1][col] != '.' || wall[row][col - 1] != '.'){
                        roundScore++;
                    }
                }
            }
            if (row == 0 && col > 0){
                if (wall[row][col] != '.'){
                    roundScore++;
                    if (wall[row][col - 1] != '.'){
                        roundScore++;
                    }
                }
            }
            if (row == 0 && col == 0){
                if (wall[row][col] != '.'){
                    roundScore++;
                }
            }
        }
    }
}

void Score::brokenScore(char* tiles){
    int deduct = 0;
    for (int i = 0; i < BROKEN_LENGTH; i++){
        if (roundScore < 0){
            roundScore = 0;
            return;
        }
        if (i < 2){
            if (tiles[i] != '0'){
                deduct++;
            }
        }
        else if (i >= 2 && i <= 4){
            if (tiles[i] != '0')
            {
                deduct += 2;
            }
        }
        else{
            if (tiles[i] != '0')
            {
                deduct += 3;
            }
        }
    }
    roundScore -= deduct;
    totalScore += roundScore;
    
}

// Adds 2 to this player's score for every complete row
void Score::rowBonus(char** wall)
{
    bool complete;
    for (int row = 0; row < MOSAIC_LENGTH; ++row)
    {
        complete = true;
        for (int col = 0; col < MOSAIC_LENGTH; ++col)
        {
            if (wall[row][col] == '.')
            {
                // This row is not complete, check the next one.
                complete = false;
            }
        }
        if (complete)
            totalScore += 2;
    }
}

// Adds 7 to this player's score for every complete column
void Score::colBonus(char** wall)
{
    bool complete;
    for (int col = 0; col < MOSAIC_LENGTH; ++col)
    {
        complete = true;
        for (int row = 0; row < MOSAIC_LENGTH; ++row)
        {
            if (wall[row][col] == '.')
            {
                // This column is not complete, check the next one.
                complete = false;
            }
        }
        if (complete)
            totalScore += 7;
    }
}

// Adds 10 to this player's score for every complete color (all 5 tiles of one color)
void Score::colorBonus(char** wall)
{
    bool complete;
    for (int color = 0; color < MOSAIC_LENGTH; ++color)
    {
        complete = true;
        for (int row = 0; row < MOSAIC_LENGTH; ++row)
        {
            if (wall[row][(row + color) % MOSAIC_LENGTH] == '.')
            {
                // This color is not complete, check the next one.
                complete = false;
            }
        }
        if (complete)
            totalScore += 10;
    }
}

int Score::getRoundScore(){
    return roundScore;
}

int Score::getFinalScore(){
    return totalScore;
}