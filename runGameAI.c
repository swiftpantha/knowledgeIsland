/*
 *  runGame.c
 *  v1.0
 *  Runs a test game asking for turns to test AI (MechanicalTurk.c) 
 *  and the game functions (Game.c)
 *
 *  Created by Tuba Toothpaste team on 10/05/15.
 *  Licensed under Creative Commons SA-BY-NC 3.0.  
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Game.h"
#include "MechanicalTurk.h"

#define DEFAULT_DISCIPLINES { STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}


void runGame (void);
int getWinner (Game g);
int rollDice (void);
void printScore(Game g);
//void printGame(Game g);
int isValidAction (int a);

int main (int argc, char *argv[]) {
    runGame ();
    return EXIT_SUCCESS;
}

void runGame (void) {
    // create a dummy game
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game g = newGame (disciplines, dice);
    
    printf ("Running a test game...\n");
    // roll the dice
    int diceScore;
    diceScore = rollDice ();
    // progress the game
    throwDice (g, diceScore);
    
    printf ("Deciding on the action...\n");
    action newAction;
    newAction = decideAction (g);
    while (!getWinner (g)) {
        // if the player PASSES
        if (newAction.actionCode == PASS) {
            diceScore = rollDice ();
            // progress the game
            throwDice (g, diceScore);
        }
        else
        {
            if (isLegalAction (g, newAction)) {
                makeAction (g, newAction);
            } else {
                printf (">>> I'm sorry but you can't do that!\n");
            }
        }
        // get the next turn
        newAction = decideAction (g);
        
    }
    // the game is over
    printf ("\nGame over. Player %d wins\n", getWinner (g));
    disposeGame (g);
}

// function to identify whether we've reached the game over
// not sure if it's to be implemented in Game.c yet?
int getWinner (Game g) {
    int player = 1;
    int points = 0;
    int max = 0;
    int max_player = 0;
    while (player <= 3) {
        points = getKPIpoints (g, player);
        if (points > max) {
            max = points;
            max_player = player;
        }
        player++;
    }
    if (max < 150) {
        max_player = 0;
    }
    return max_player;
}

// roll the dice randomly
int rollDice (void) {
    printf ("Rolling dice...\n");
    // random int between 0 and 6
    int dice1 = rand () % 6 + 1;
    int dice2 = rand () % 6 + 1;
    int diceScore = dice1 + dice2;
    printf ("Score is: %d\n", diceScore);
    return diceScore;
}

void printScore (Game g) {
    int player = getWhoseTurn (g);
    printf ("============== YOUR STUFF ==============\n");
    printf ("Students:\n");
    printf ("THD: %d ", getStudents (g, player, STUDENT_THD));
    printf ("BPS: %d ", getStudents (g, player, STUDENT_BPS));
    printf ("BQN: %d ", getStudents (g, player, STUDENT_BQN));
    printf ("MJ: %d ", getStudents (g, player, STUDENT_MJ));
    printf ("MTV: %d ", getStudents (g, player, STUDENT_MTV));
    printf ("M$: %d\n", getStudents (g, player, STUDENT_MMONEY));
    printf ("Your current score:\n");
    printf ("KPI: %d ", getKPIpoints (g, player));
    printf ("Pubs: %d ", getPublications (g, player));
    printf ("IPs: %d\n", getIPs (g, player));
    printf ("Built:\n");
    printf ("ARCs: %d ", getARCs (g, player));
    printf ("Campuses: %d ", getCampuses (g, player));
    printf ("GO8s: %d\n", getGO8s (g, player));
    printf ("========================================\n");
}

/*void printGame (Game g) {
    printf ("\n============== Total score ==============\n");
    printf ("Most KPIs: %d\n", getMostKPIpoints (g));
    printf ("Most ARCs: %d\n", getMostARCs (g));
    // printf ("Built:\n");
    // printf ("ARCs: %d\n", getARCS (g, player));
    // printf ("Campuses: %d\n", getCampuses (g, player));
    // printf ("ARCs: %d\n", getARCs (g, player));
}*/