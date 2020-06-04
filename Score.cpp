#include "Score.h"
Score::Score(){
    roundScore = 0;
    totalScore = 0;
}

void Score::scoreTile(char** wall, bool extension)
{
    if (extension){
        mosaic_length = 6;
    }else{
        mosaic_length = 5;
    }
    roundScore = 0;
    for (int row = 0; row < mosaic_length; row++)
    {
        for (int col = 0; col < mosaic_length; col++)
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
        else if (i>4 && i < 7){
            if (tiles[i] != '0')
            {
                deduct += 3;
            }
        }else if (i == 8){
            if (tiles[i] != '0')
            {
                deduct += 4;
            }
        }else{
            deduct += 0;
        }
    }
    roundScore -= deduct;
    if (roundScore < 0)
    {
        roundScore = 0;
        return;
    }
    totalScore += roundScore;
    
}

// Adds 2 to this player's score for every complete row
void Score::rowBonus(char** wall)
{
    bool complete;
    for (int row = 0; row < mosaic_length; ++row)
    {
        complete = true;
        for (int col = 0; col < mosaic_length; ++col)
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
    for (int col = 0; col < mosaic_length; ++col)
    {
        complete = true;
        for (int row = 0; row < mosaic_length; ++row)
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
    for (int color = 0; color < mosaic_length; ++color)
    {
        complete = true;
        for (int row = 0; row < mosaic_length; ++row)
        {
            if (wall[row][(row + color) % mosaic_length] == '.')
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