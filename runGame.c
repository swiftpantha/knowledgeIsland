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

#define DEFAULT_DISCIPLINES { STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}


void runGame (void);
int getNewTurn (Game g);
char * getNewPath (void);
int getDisciplineFrom (void);
int getDisciplineTo (void);
int getMostKPIpoints (Game g);
int rollDice (void);
void printScore(Game g);
void printGame(Game g);
int isValidAction (int a);
int isDigit(char c);
        
int main (int argc, char *argv[]) {
    runGame ();
    return EXIT_SUCCESS;
}

void runGame (void) {
    // create a dummy game
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    int newActionSet = FALSE;
    Game g = newGame (disciplines, dice);
    
    printf ("Running a test game...\n");
    // roll the dice
    int diceScore;
    diceScore = rollDice ();
    // progress the game
    throwDice (g, diceScore);
    
    action newAction;
    newAction.actionCode = getNewTurn (g);
    if (isValidAction (newAction.actionCode) != TRUE) {
        // keep getting new actions from the input until you get the valid one i.e. a number
        while (isValidAction (newAction.actionCode) != TRUE) {
            newAction.actionCode = getNewTurn (g);
        }
    }
    while (isValidAction(newAction.actionCode) && getMostKPIpoints (g) < 150 && newAction.actionCode != 99) {
        // if the player PASSES
        if (newAction.actionCode == PASS) {
            diceScore = rollDice ();
            // progress the game
            throwDice (g, diceScore);
        }
        // if the player makes an actual action
        else {
            // for building actions request the paths
            if (newAction.actionCode == BUILD_CAMPUS || 
                newAction.actionCode == BUILD_GO8 || 
                newAction.actionCode == OBTAIN_ARC) {
                strcpy (newAction.destination, getNewPath ());
            }
            // for retraining students request the disciplines
            else if (newAction.actionCode == RETRAIN_STUDENTS) {
                newAction.disciplineFrom = getDisciplineFrom ();
                newAction.disciplineTo = getDisciplineTo ();
            }
            if (isLegalAction (g, newAction)) {
                makeAction (g, newAction);
            } else {
                printf (">>> I'm sorry but you can't do that!\n");
            }
        }
        newActionSet = FALSE;
        // get the next turn
        // if new action has not been set yet or it has but it's not valid - run loop
        // till it gets to the point...
        while(!newActionSet || isValidAction(newAction.actionCode) != TRUE) {
            newAction.actionCode = getNewTurn (g);
            newActionSet = TRUE;
        }
    }
    disposeGame (g);
    // the game is over
    printf ("\nGame over.\n");
}

int getNewTurn (Game g) {
    int actionCode;
    printGame(g);
    printScore(g);
    printf ("\nPASS = 0");
    printf ("\nBUILD_CAMPUS = 1");
    printf ("\nBUILD_GO8 = 2");
    printf ("\nOBTAIN_ARC = 3");
    printf ("\nSTART_SPINOFF = 4");
    printf ("\nRETRAIN_STUDENTS = 7");
    printf ("\nYour next action, Player %d? (Write 99 to quit) ", getWhoseTurn (g));
    scanf ("%d", &actionCode);
    return actionCode;
}

char * getNewPath (void) {
    char * actionPath = " ";
    printf ("Specify the path? ");
    actionPath = malloc(sizeof(path));
    scanf ("%s", actionPath);
    printf ("%s\n", actionPath);
    assert (strlen (actionPath) <= PATH_LIMIT);
    return actionPath;
}

int getDisciplineFrom (void) {
    int disciplineFrom;
    printf ("From which discipline? ");
    scanf ("%d", &disciplineFrom);
    return disciplineFrom;
}

int getDisciplineTo (void) {
    int disciplineTo;
    printf ("To which discipline? ");
    scanf ("%d", &disciplineTo);
    return disciplineTo;
}

// function to identify whether we've reached the game over
// not sure if it's to be implemented in Game.c yet?
int getMostKPIpoints (Game g) {
    int player = 1;
    int points = 0;
    int max = 0;
    while (player <= 3) {
        points = getKPIpoints (g, player);
        if (points > max) {
            max = points;
        }
        player++;
    }
    return max;
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
    printf ("============== Player: %d==============\n", player);
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

void printGame (Game g) {
    printf ("\n============== Total score ==============\n");
    printf ("Most KPIs: %d\n", getMostKPIpoints (g));
    printf ("Most ARCs: %d\n", getARCs(g, getMostARCs (g)));
    // printf ("Built:\n");
    // printf ("ARCs: %d\n", getARCS (g, player));
    // printf ("Campuses: %d\n", getCampuses (g, player));
    // printf ("ARCs: %d\n", getARCs (g, player));
}

int isValidAction (int a) {
    int valid = FALSE;
    if (a == 99 || (a >= PASS && a <= RETRAIN_STUDENTS)) {
        valid = TRUE;
    }
    return valid;
}

int isDigit(char c) {
    int valid = FALSE;
    if(c >= '0' || c <= '9') {
        valid = TRUE;
    }
    return valid;
}