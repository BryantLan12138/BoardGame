#include <iostream>
#define MOSAIC_LENGTH 5
#define BROKEN_LENGTH 20

class Score {
public:

   // Constructor/Desctructor
   Score();

   // get current score
   int getScore();

   // Calculates the score for a single tile, by counting the contiguous row and/or column of it
   void scoreTile(char** wall);

   // in the final round, calculate the row Bonus
   void rowBonus(char** wall);

   // in the final round, calculate the col Bonus
   void colBonus(char** wall);
   
   // in the final round, calculate the diagonal Bonus
   void colorBonus(char** wall);

   // to reduce scores of brokenTiles
   void brokenScore(char* tiles);

private:
   int score;
};