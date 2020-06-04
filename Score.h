#include <iostream>
#define BROKEN_LENGTH 20

class Score {
public:

   // Constructor/Desctructor
   Score();

   // get round score
   int getRoundScore();

   // get the final total score
   int getFinalScore();

   // Calculates the score for a single tile, by counting the contiguous row and/or column of it
   void scoreTile(char** wall, bool extension);

   // in the final round, calculate the row Bonus
   void rowBonus(char** wall);

   // in the final round, calculate the col Bonus
   void colBonus(char** wall);
   
   // in the final round, calculate the diagonal Bonus
   void colorBonus(char** wall);

   // to reduce scores of brokenTiles
   void brokenScore(char* tiles);

private:
   int roundScore, totalScore, mosaic_length;
};