#include "Score.h"
Score::Score(){
    score = 0;
}

void Score::scoreTile(char** wall)
{
    for (int row = 0; row < MOSAIC_LENGTH; row++)
    {
        for (int col = 0; col < MOSAIC_LENGTH; col++)
        {
            if (row + 1 < MOSAIC_LENGTH && col + 1 < MOSAIC_LENGTH && row - 1 >= 0 && col - 1 >= 0)
            {
                if (wall[row][col] != '.'){
                    score++;
                    if (wall[row + 1][col] != '.' || wall[row][col + 1] != '.' ||
                        wall[row - 1][col] != '.' || wall[row][col - 1] != '.')
                    {
                        score += 2;
                    }
                }
            }
            if ((row == 0 && col < 4) || (row < 4 && col == 0) || (row == 0 && col == 0))
            {
                if (wall[row][col] != '.'){
                    score++;
                    if (wall[row + 1][col] != '.' || wall[row][col + 1] != '.'){
                            score += 2;
                    }
                }
            }
            if ((row == 4 && col > 0) || (row > 0 && col == 4) || (row == 4 && col == 4)){
                if (wall[row][col] != '.'){
                    score++;
                    if (wall[row - 1][col] != '.' || wall[row][col - 1] != '.')
                    {
                        score += 2;
                    }
                }
            }
            if (row == 0 && col == 4){
                if (wall[row][col] != '.')
                {
                    score++;
                    if (wall[row][col + 1] != '.' || wall[row][col - 1] != '.')
                    {
                        score += 2;
                    }
                }    
            }
            if (row == 4 && col == 0)
            {
                if (wall[row][col] != '.')
                {
                    score++;
                    if (wall[row - 1][col] != '.' || wall[row][col + 1] != '.')
                    {
                        score += 2;
                    }
                }
            }
        }
    }
}

void Score::brokenScore(char* tiles){
    for (int i = 0; i < BROKEN_LENGTH; i++){
        if (score < 0){
            score = 0;
            break;
        }
        if (i < 2){
            if (tiles[i] != '0'){
                score -= 1;
            }
        }
        else if (i >= 2 && i <= 4){
            if (tiles[i] != '0')
            {
                score -= 2;
            }
        }
        else{
            if (tiles[i] != '0')
            {
                score -= 3;
            }
        }
    }
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
            score += 2;
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
            score += 7;
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
            score += 10;
    }
}

int Score::getScore(){
    return score;
}