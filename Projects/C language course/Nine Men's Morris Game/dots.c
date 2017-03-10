/**
* @Plik:  dots.c
* @Autor: Elżbieta Plaszczyk
* @opis:  Zawiera funkcję, która przypisuje początkowy wartośći do tablicy struktur "pointsDefinitions"
*/
#include "dots.h"

void initPoints() {
    pointsDefinitions[0] = (dot)
            {.player = 0, .x = 17.0, .y = 17.0, .horizontal1 = &pointsDefinitions[1],
                    .horizontal2 = &pointsDefinitions[2], .vertical1 = &pointsDefinitions[7],
                    .vertical2 = &pointsDefinitions[6], .possible1 = &pointsDefinitions[1],
                    .possible2 = &pointsDefinitions[7], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[1] = (dot)
            {.player = 0, .x = 175.0, .y = 17.0, .horizontal1 = &pointsDefinitions[0],
                    .horizontal2 = &pointsDefinitions[2], .vertical1 = &pointsDefinitions[9],
                    .vertical2 = &pointsDefinitions[17], .possible1 = &pointsDefinitions[0],
                    .possible2 = &pointsDefinitions[2], .possible3 = &pointsDefinitions[9],
                    .possible4 =NULL};
    pointsDefinitions[2] = (dot)
            {.player = 0, .x = 335.0, .y = 17.0, .horizontal1 = &pointsDefinitions[0],
                    .horizontal2 = &pointsDefinitions[1], .vertical1 = &pointsDefinitions[3],
                    .vertical2 = &pointsDefinitions[4], .possible1 = &pointsDefinitions[1],
                    .possible2 = &pointsDefinitions[3], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[3] = (dot)
            {.player = 0, .x = 335.0, .y = 225.0, .horizontal1 = &pointsDefinitions[11],
                    .horizontal2 = &pointsDefinitions[19], .vertical1 = &pointsDefinitions[2],
                    .vertical2 = &pointsDefinitions[4], .possible1 = &pointsDefinitions[2],
                    .possible2 = &pointsDefinitions[4], .possible3 = &pointsDefinitions[11],
                    .possible4 =NULL};
    pointsDefinitions[4] = (dot)
            {.player = 0, .x = 335.0, .y = 435.0, .horizontal1 = &pointsDefinitions[5],
                    .horizontal2 = &pointsDefinitions[6], .vertical1 = &pointsDefinitions[2],
                    .vertical2 = &pointsDefinitions[3], .possible1 = &pointsDefinitions[3],
                    .possible2 = &pointsDefinitions[5], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[5] = (dot)
            {.player = 0, .x = 175.0, .y = 435.0, .horizontal1 = &pointsDefinitions[4],
                    .horizontal2 = &pointsDefinitions[6], .vertical1 = &pointsDefinitions[13],
                    .vertical2 = &pointsDefinitions[21], .possible1 = &pointsDefinitions[4],
                    .possible2 = &pointsDefinitions[6], .possible3 = &pointsDefinitions[13],
                    .possible4 =NULL};
    pointsDefinitions[6] = (dot)
            {.player = 0, .x = 17.0, .y = 435.0, .horizontal1 = &pointsDefinitions[5],
                    .horizontal2 = &pointsDefinitions[4], .vertical1 = &pointsDefinitions[7],
                    .vertical2 = &pointsDefinitions[0], .possible1 = &pointsDefinitions[5],
                    .possible2 = &pointsDefinitions[7], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[7] = (dot)
            {.player = 0, .x = 17.0, .y = 225.0, .horizontal1 = &pointsDefinitions[15],
                    .horizontal2 = &pointsDefinitions[23], .vertical1 = &pointsDefinitions[6],
                    .vertical2 = &pointsDefinitions[0], .possible1 = &pointsDefinitions[0],
                    .possible2 = &pointsDefinitions[6], .possible3 = &pointsDefinitions[15],
                    .possible4 =NULL};
    pointsDefinitions[8] = (dot)
            {.player = 0, .x = 60.0, .y = 60.0, .horizontal1 = &pointsDefinitions[9],
                    .horizontal2 = &pointsDefinitions[10], .vertical1 = &pointsDefinitions[15],
                    .vertical2 = &pointsDefinitions[14], .possible1 = &pointsDefinitions[9],
                    .possible2 = &pointsDefinitions[15], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[9] = (dot)
            {.player = 0, .x = 175.0, .y = 60.0, .horizontal1 = &pointsDefinitions[8],
                    .horizontal2 = &pointsDefinitions[10], .vertical1 = &pointsDefinitions[1],
                    .vertical2 = &pointsDefinitions[17], .possible1 = &pointsDefinitions[1],
                    .possible2 = &pointsDefinitions[8], .possible3 = &pointsDefinitions[10],
                    .possible4 =&pointsDefinitions[17]};
    pointsDefinitions[10] = (dot)
            {.player = 0, .x = 290.0, .y = 60.0, .horizontal1 = &pointsDefinitions[8],
                    .horizontal2 = &pointsDefinitions[9], .vertical1 = &pointsDefinitions[11],
                    .vertical2 = &pointsDefinitions[12], .possible1 = &pointsDefinitions[9],
                    .possible2 = &pointsDefinitions[11], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[11] = (dot)
            {.player = 0, .x = 290.0, .y = 225.0, .horizontal1 = &pointsDefinitions[19],
                    .horizontal2 = &pointsDefinitions[3], .vertical1 = &pointsDefinitions[10],
                    .vertical2 = &pointsDefinitions[12], .possible1 = &pointsDefinitions[3],
                    .possible2 = &pointsDefinitions[19], .possible3 = &pointsDefinitions[10],
                    .possible4 =&pointsDefinitions[12]};
    pointsDefinitions[12] = (dot)
            {.player = 0, .x = 290.0, .y = 390.0, .horizontal1 = &pointsDefinitions[14],
                    .horizontal2 = &pointsDefinitions[13], .vertical1 = &pointsDefinitions[10],
                    .vertical2 = &pointsDefinitions[11], .possible1 = &pointsDefinitions[13],
                    .possible2 = &pointsDefinitions[11], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[13] = (dot)
            {.player = 0, .x = 175.0, .y = 390.0, .horizontal1 = &pointsDefinitions[14],
                    .horizontal2 = &pointsDefinitions[12], .vertical1 = &pointsDefinitions[21],
                    .vertical2 = &pointsDefinitions[5], .possible1 = &pointsDefinitions[5],
                    .possible2 = &pointsDefinitions[14], .possible3 = &pointsDefinitions[21],
                    .possible4 =&pointsDefinitions[12]};
    pointsDefinitions[14] = (dot)
            {.player = 0, .x = 60.0, .y = 390.0, .horizontal1 = &pointsDefinitions[13],
                    .horizontal2 = &pointsDefinitions[12], .vertical1 = &pointsDefinitions[8],
                    .vertical2 = &pointsDefinitions[15], .possible1 = &pointsDefinitions[13],
                    .possible2 = &pointsDefinitions[15], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[15] = (dot)
            {.player = 0, .x = 60.0, .y = 225.0, .horizontal1 = &pointsDefinitions[7],
                    .horizontal2 = &pointsDefinitions[23], .vertical1 = &pointsDefinitions[8],
                    .vertical2 = &pointsDefinitions[14], .possible1 = &pointsDefinitions[8],
                    .possible2 = &pointsDefinitions[14], .possible3 = &pointsDefinitions[23],
                    .possible4 =&pointsDefinitions[7]};
    pointsDefinitions[16] = (dot)
            {.player = 0, .x = 105.0, .y = 105.0, .horizontal1 = &pointsDefinitions[17],
                    .horizontal2 = &pointsDefinitions[18], .vertical1 = &pointsDefinitions[23],
                    .vertical2 = &pointsDefinitions[22], .possible1 = &pointsDefinitions[23],
                    .possible2 = &pointsDefinitions[17], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[17] = (dot)
            {.player = 0, .x = 175.0, .y = 105.0, .horizontal1 = &pointsDefinitions[16],
                    .horizontal2 = &pointsDefinitions[18], .vertical1 = &pointsDefinitions[1],
                    .vertical2 = &pointsDefinitions[9], .possible1 = &pointsDefinitions[9],
                    .possible2 = &pointsDefinitions[16], .possible3 = &pointsDefinitions[18],
                    .possible4 = NULL};
    pointsDefinitions[18] = (dot)
            {.player = 0, .x = 245.0, .y = 105.0, .horizontal1 = &pointsDefinitions[16],
                    .horizontal2 = &pointsDefinitions[17], .vertical1 = &pointsDefinitions[19],
                    .vertical2 = &pointsDefinitions[20], .possible1 = &pointsDefinitions[17],
                    .possible2 = &pointsDefinitions[19], .possible3 = NULL, .possible4 =NULL};
    pointsDefinitions[19] = (dot)
            {.player = 0, .x = 245.0, .y = 225.0, .horizontal1 = &pointsDefinitions[11],
                    .horizontal2 = &pointsDefinitions[3], .vertical1 = &pointsDefinitions[18],
                    .vertical2 = &pointsDefinitions[20], .possible1 = &pointsDefinitions[11],
                    .possible2 = &pointsDefinitions[18], .possible3 = &pointsDefinitions[20],
                    .possible4 = NULL};
    pointsDefinitions[20] = (dot)
            {.player = 0, .x = 245.0, .y = 345.0, .horizontal1 = &pointsDefinitions[22],
                    .horizontal2 = &pointsDefinitions[21], .vertical1 = &pointsDefinitions[18],
                    .vertical2 = &pointsDefinitions[19], .possible1 = &pointsDefinitions[19],
                    .possible2 = &pointsDefinitions[21], .possible3 = NULL, .possible4 = NULL};
    pointsDefinitions[21] = (dot)
            {.player = 0, .x = 175.0, .y = 345.0, .horizontal1 = &pointsDefinitions[22],
                    .horizontal2 = &pointsDefinitions[20], .vertical1 = &pointsDefinitions[13],
                    .vertical2 = &pointsDefinitions[5], .possible1 = &pointsDefinitions[13],
                    .possible2 = &pointsDefinitions[20], .possible3 = &pointsDefinitions[22], .possible4 = NULL};
    pointsDefinitions[22] = (dot)
            {.player = 0, .x = 105.0, .y = 345.0, .horizontal1 = &pointsDefinitions[21],
                    .horizontal2 = &pointsDefinitions[20], .vertical1 = &pointsDefinitions[23],
                    .vertical2 = &pointsDefinitions[16], .possible1 = &pointsDefinitions[23],
                    .possible2 = &pointsDefinitions[21], .possible3 = NULL, .possible4 = NULL};
    pointsDefinitions[23] = (dot)
            {.player = 0, .x = 105.0, .y = 225.0, .horizontal1 = &pointsDefinitions[7],
                    .horizontal2 = &pointsDefinitions[15], .vertical1 = &pointsDefinitions[16],
                    .vertical2 = &pointsDefinitions[22], .possible1 = &pointsDefinitions[16],
                    .possible2 = &pointsDefinitions[22], .possible3 = &pointsDefinitions[15], .possible4 = NULL};
}