#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

#define DEFAULT_DISCIPLINES { STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
                STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, \
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
#define REGION_0 0
#define REGION_1 1
#define REGION_2 2
#define REGION_3 3
#define REGION_4 4
#define REGION_5 5
#define REGION_6 6
#define REGION_7 7
#define REGION_8 8
#define REGION_9 9
#define REGION_10 10
#define REGION_11 11
#define REGION_12 12
#define REGION_13 13
#define REGION_14 14
#define REGION_15 15
#define REGION_16 16
#define REGION_17 17
#define REGION_18 18


void testDisposeGame (void);
void testGetDiscipline (void);
void testGetTurnNumber (void);
void testIsLegalAction (void);
void testGetCampuses (void);
void testMakeAction (void);
void testGetMostARCs (void);
void testGetCampus (void);
void testGetARCs (void);
void testGetPublications (void);
void testThrowDice (void);
void testGetMostPublications (void);
void testGetARC (void);
void testGetGO8s (void);
void testGetStudents (void);
void testGetDiceValue (void);
void testGetWhoseTurn (void);
void testGetKPIpoints (void);
void testGetIPs (void);
int rollDice (int no7);
void failedExternalTests(void);
void externalTest001(void);
void externalTest002(void);
void failedExternalTestSimon(void);
void failedExternalTestMeghana(void);
void printScore (Game g, int player);


int main (int argc, char *argv[]) {
    
    testDisposeGame ();
    testGetDiscipline ();
    testGetTurnNumber ();
    testGetCampuses ();
    testMakeAction ();
    testGetMostARCs ();
    testGetCampus ();
    testGetARCs ();
    testGetPublications ();
    testGetCampuses ();
    testThrowDice ();
    testGetMostPublications ();
    testGetARC ();
    testGetGO8s ();
    testGetStudents ();
    testGetDiceValue ();
    testGetWhoseTurn ();
    testGetKPIpoints ();
    printf("============================ Gameplay step-by-step test for isLegalAction ============================\n");
    testIsLegalAction ();
    // extrenal tests
    /*
    printf("============================ EXTERNAL TESTS FROM Round1 ============================\n");
    externalTest001();
    failedExternalTests ();
    failedExternalTestSimon ();
    failedExternalTestMeghana();
    failedExternalTests ();
    externalTest002();*/
    printf ("All tests passed. You are awesome!\n");

    return EXIT_SUCCESS;
}


void testThrowDice (void) {
    printf ("Testing throwDice\n");
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);
    //Throw the dice to advance the turn
    throwDice (testGame, 2);
    //Check that the turn is Terra Nullis
    assert (getTurnNumber (testGame) == 0);
    //Check that the turn advances again
    throwDice (testGame, 2);
    assert (getTurnNumber (testGame) == 1);
    //And Once more for luck
    throwDice (testGame, 2);
    assert (getTurnNumber (testGame) == 2);
    
    int turnNum = 3;
    while (turnNum < 9000) {
        throwDice (testGame, 2);
        assert (getTurnNumber (testGame) == turnNum);
        turnNum ++;
    }
    
    printf ("throwDice works - You are Awesome!\n\n");
}


void testGetMostPublications (void) {
    //Initialize Variables
    printf ("Testing getMostPublications\n");
    int playersTurn = 0;
    int newPlayersTurn = 0;
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);

    //Check that the most publications is currently NO_ONE
    assert (getMostPublications (testGame) == NO_ONE);

    //Make an action to obtain publication
    action testAction;
    testAction.actionCode = OBTAIN_PUBLICATION;

    //Throw the dice to progress to a turn
    throwDice (testGame, 2);

    //Get whose turn it is now
    playersTurn = getWhoseTurn (testGame);

    //Obtain a publication for them
    makeAction (testGame, testAction);  
    
    //Check that they now have the most publications
    assert (getMostPublications (testGame) == playersTurn);

    //Need to check proper tie behaviour
    newPlayersTurn = getWhoseTurn (testGame);

    //Obtain a publication for them
    makeAction (testGame, testAction);  

    //Check behaviour in a tie
    assert (getMostPublications (testGame) == playersTurn);

    printf ("getMostPublications works - You are Awesome!\n\n");
}



void testGetARC (void){
    printf ("Testing getARC\n");
    //Initialize varible 
    int playersTurn = 0;
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);

    //Check that a whole bunch of them are vacant
    assert (getARC (testGame, "L") == VACANT_ARC);
    assert (getARC (testGame, "R") == VACANT_ARC);
    assert (getARC (testGame, "LR") == VACANT_ARC);
    assert (getARC (testGame, "RL") == VACANT_ARC);
//    assert (getARC (testGame, "LLR") == VACANT_ARC);
    assert (getARC (testGame, "RRL") == VACANT_ARC);
//    assert (getARC (testGame, "RRR") == VACANT_ARC);
//    assert (getARC (testGame, "LLL") == VACANT_ARC);
//    assert (getARC (testGame, "LLLR") == VACANT_ARC);
//    assert (getARC (testGame, "RRRL") == VACANT_ARC);
    assert (getARC (testGame, "RRLL") == VACANT_ARC);
//    assert (getARC (testGame, "LLRR") == VACANT_ARC);
    assert (getARC (testGame, "LRRR") == VACANT_ARC);
    assert (getARC (testGame, "RLLL") == VACANT_ARC);
//    assert (getARC (testGame, "LLLL") == VACANT_ARC);
//    assert (getARC (testGame, "RRRR") == VACANT_ARC);
//    assert (getARC (testGame, "LLLLR") == VACANT_ARC);
//    assert (getARC (testGame, "RRRRL") == VACANT_ARC);
//    assert (getARC (testGame, "RRRLL") == VACANT_ARC);
//    assert (getARC (testGame, "LLLRR") == VACANT_ARC); 


    //Advance turn from Terra Nullis
    throwDice (testGame, 2);

    //Get whose turn it is now
    playersTurn = getWhoseTurn (testGame);

    //Setup the action
    action testAction;
    testAction.actionCode = OBTAIN_ARC;  
    strcpy (testAction.destination, "L");

    //Make the action
    makeAction (testGame, testAction);
    assert (getARC (testGame, "L") == playersTurn);

    //Advance turn from Previous
    throwDice (testGame, 2);

    //Get whose turn it is now
    playersTurn = getWhoseTurn (testGame);

    //Setup the action
    testAction.actionCode = OBTAIN_ARC;  
    strcpy (testAction.destination, "LR");

    //Make the action
    makeAction (testGame, testAction);
    assert (getARC (testGame, "LR") == playersTurn);

    //Advance turn from Previous
    throwDice (testGame, 2);

    //Get whose turn it is now
    playersTurn = getWhoseTurn (testGame);

    //Setup the action
    testAction.actionCode = OBTAIN_ARC;  
    strcpy (testAction.destination, "RR");

    //Make the action
    makeAction (testGame, testAction);
    assert (getARC (testGame, "RR") == playersTurn);

    printf ("getARCs works - You are Awesome!\n\n");
}


void testGetGO8s (void){
    printf ("Testing getGO8s\n");
    //Initialize varible 
    int player = 0;
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);

    //Test that everyone starts with none during Terra Nullis
    assert (getGO8s (testGame, UNI_A) == 0);
    assert (getGO8s (testGame, UNI_B) == 0);
    assert (getGO8s (testGame, UNI_C) == 0);

    //Advance turn from Terra Nullis
    throwDice (testGame, 2);

    //Get whose turn it is now
    player = getWhoseTurn (testGame);

    //Setup the action
    action testAction;
    testAction.actionCode = BUILD_GO8; 
    strcpy (testAction.destination, "LR");

    makeAction (testGame, testAction);

    assert (getGO8s (testGame, player) == 1);

    //Give him another one 
    testAction.actionCode = BUILD_GO8;  
    strcpy (testAction.destination, "LRR");

    makeAction (testGame, testAction);

    assert (getGO8s (testGame, player) == 2);

    //Change the player
    throwDice (testGame, 2);

    //Get whose turn it is now
    player = getWhoseTurn (testGame);

    //Give them a GO8
    testAction.actionCode = BUILD_GO8; 
    strcpy (testAction.destination, "LRR");

    makeAction (testGame, testAction);

    assert (getGO8s (testGame, player) == 1);

    printf ("getGO8s works - You are Awesome!\n\n");
}



// STILL NEED TO FIGURE OUT HOW TO ASSIGN PEOPLE STUDENTS###############
void testGetStudents (void) {
    //Initialize varible 
    //int player = 0;

    printf ("Testing getStudents\n");
    //Eh, setup another test game
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);

    //Check everyone has zero to start off with
    assert (getStudents (testGame, UNI_A, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_A, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_A, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_A, STUDENT_MMONEY) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_B, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_B, STUDENT_MMONEY) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_THD) == 0);
    assert (getStudents (testGame, UNI_C, STUDENT_BPS) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_BQN) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 1);
    assert (getStudents (testGame, UNI_C, STUDENT_MMONEY) == 1);

    //Advance turn from Terra Nullis
    throwDice (testGame, 11);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 2);
    throwDice (testGame, 8);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 2);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 2);
    throwDice (testGame, 8);
    assert (getStudents (testGame, UNI_C, STUDENT_MTV) == 3);
    assert (getStudents (testGame, UNI_C, STUDENT_MJ) == 3);
    throwDice (testGame, 11);
    assert (getStudents (testGame, UNI_A, STUDENT_MTV) == 3);
    throwDice (testGame, 9);
    assert (getStudents (testGame, UNI_B, STUDENT_BQN) == 4);
    throwDice (testGame, 6);
    //assert (getStudents (testGame, UNI_B, STUDENT_MJ) == 1);
    printf ("getStudents works - You are Awesome!\n\n");
}

void testMakeAction (void) {
    
    printf ("Testing makeAction\n");
    // test BUILD_CAMPUS and BUILD_GO8 and PASS 
    testGetCampus ();
    // test OBTAIN_ARC 
    testGetARCs ();
    // test START_SPINOFF and OBTAIN_PUBLICATION
    testGetPublications ();
    // test RETRAIN_STUDENTS
    testGetStudents ();
    // test OBTAIN_IP_PATENT 
    testGetIPs ();
    
    printf ("makeAction works - You are Awesome!\n\n");   
}


void testGetMostARCs (void) {
    printf ("Testing getMostARCs\n");
    // Create a game
    int disciplines [] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // Check all players start with 0 arcs
    assert (getMostARCs (testGame) == NO_ONE);
    
    // Go to next turn (A)
    throwDice (testGame, 3);
    
    // Create and execute action that creates an arc
    action testAction;
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "LBL");
    makeAction (testGame, testAction);
    
    // Check first player has most arcs
    
    assert (getMostARCs (testGame) == UNI_A);
    
    // Go to next player (B)
    throwDice (testGame, 5);
    
    // Create 2 arcs
    strcpy (testAction.destination, "RRL"); 
    makeAction (testGame, testAction);
    assert (getMostARCs (testGame) == UNI_A); 
    
    strcpy (testAction.destination, "RRLLL"); 
    makeAction (testGame, testAction);
    
    // Check player 2 has the most arcs
    assert (getMostARCs (testGame) == UNI_B);
    
    // Go to next player (C) and pass
    throwDice (testGame, 5);
    testAction.actionCode = PASS; 
    makeAction (testGame, testAction);
    
    // Check player 2 has the most arcs
    assert (getMostARCs (testGame) == UNI_B);
    
    // Go to next player (A)
    throwDice (testGame, 2);
    
    assert (getMostARCs (testGame) == UNI_B);
    
    //  Pass and check player B still has the most arcs
    makeAction (testGame, testAction);
    assert (getMostARCs (testGame) == UNI_B);
    
    // Go to next player (B)
    throwDice (testGame, 4);
    
    // Create an arc
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "LRLRL"); 
    makeAction (testGame, testAction);
    
    // Check player 2 still has most arcs
    assert (getMostARCs (testGame) == UNI_B);
    
    // Go to next player (C)
    throwDice (testGame, 9);
    
    strcpy (testAction.destination, "LRRLRLRLRLRBRL");
    makeAction (testGame, testAction);
    assert (getMostARCs (testGame) == UNI_B);
    
    strcpy (testAction.destination, "LRR");
    makeAction (testGame, testAction);
    assert (getMostARCs (testGame) == UNI_B);
    
    strcpy (testAction.destination, "LRLRRBR");
    makeAction (testGame, testAction);
    assert (getMostARCs (testGame) == UNI_B);
    
    strcpy (testAction.destination, "LRL");
    makeAction (testGame, testAction);
    assert (getMostARCs (testGame) == UNI_C);
    
    disposeGame (testGame);
    printf ("getMostARCs works - You are Awesome!\n\n");
}


void testGetCampus (void) {
    // Create a game
    printf ("Testing getCampus\n");
    int disciplines [] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // Check random vertices are vacant
    assert (getCampus (testGame, "LRLR") == VACANT_VERTEX);
    assert (getCampus (testGame, "RRLRLLRLLRBR") == VACANT_VERTEX);
    
    // Check starting campuses exist
    assert (getCampus (testGame, "") == CAMPUS_A);
    assert (getCampus (testGame, "LRLRLRRLRLRRLRL") == CAMPUS_A);
    assert (getCampus (testGame, "RRLRL") == CAMPUS_B);
    assert (getCampus (testGame, "LRLRLRRLRL") == CAMPUS_B);
    assert (getCampus (testGame, "LRLRL") == CAMPUS_C);

    assert (getCampus (testGame, "RRLRLLRLRL") == CAMPUS_C);
    
    // Go to next turn (A)
    throwDice (testGame, 3);

    // Create and execute action that creates a campus
    action testAction;
    testAction.actionCode = BUILD_CAMPUS; 
    strcpy (testAction.destination, "LRR");
    makeAction (testGame, testAction);
    
    // Check campus is built and other vertices are the same
    assert (getCampus (testGame, "LRLBR") == VACANT_VERTEX);
    assert (getCampus (testGame, "LRR") == CAMPUS_A);
    assert (getCampus (testGame, "LR") == VACANT_VERTEX);
    assert (getCampus (testGame, "LBLLRR") == VACANT_VERTEX);
    
    // Create a GO8 campus
    testAction.actionCode = BUILD_GO8;  
    strcpy (testAction.destination, "");
    makeAction (testGame, testAction);
    
    // Check campus is built and other vertices are correct
    assert (getCampus (testGame, "") == GO8_A);
    assert (getCampus (testGame, "LRR") == CAMPUS_A);
    assert (getCampus (testGame, "RLLRRLLRLR") == CAMPUS_B);
    assert (getCampus (testGame, "RLLRRLLRL") == VACANT_VERTEX);
    
    // Go to next player (B)
    throwDice (testGame, 5);
    
    // Create a campus
    testAction.actionCode = BUILD_CAMPUS;  
    strcpy (testAction.destination, "RLLRRLLRLR");
    makeAction (testGame, testAction);
    
    // Check campus is built and other vertices are correct
    assert (getCampus (testGame, "LRLBR") == VACANT_VERTEX);
    assert (getCampus (testGame, "LRR") == CAMPUS_A);
    assert (getCampus (testGame, "") == GO8_A);
    assert (getCampus (testGame, "RLLRRLLRLR") == CAMPUS_B);
    
    // Build another campus
    testAction.actionCode = BUILD_CAMPUS;  
    strcpy (testAction.destination, "RLLRRLLRLRRRBB");
    makeAction (testGame, testAction);
    
    // Check campus is built and other vertices are correct
    assert (getCampus (testGame, "LRLBR") == VACANT_VERTEX);
    assert (getCampus (testGame, "") == GO8_A);
    assert (getCampus (testGame, "RLLRRLLRLR") == CAMPUS_B);
    assert (getCampus (testGame, "RLLRRLLRLRRRBB") == CAMPUS_B);
    
    // Go to next player (C)
    throwDice (testGame, 5);
    
    // Create a campus
    testAction.actionCode = BUILD_CAMPUS;  
    strcpy (testAction.destination, "LRRRLRLRL");
    makeAction (testGame, testAction);
    
    // Check campus is built and other vertices are correct
    assert (getCampus (testGame, "LRLBRLB") == VACANT_VERTEX);
    assert (getCampus (testGame, "RLLRRLLRLR") == CAMPUS_B);
    assert (getCampus (testGame, "RLLRRLLRLRRRBB") == CAMPUS_B);
    assert (getCampus (testGame, "") == GO8_A);
    assert (getCampus (testGame, "LRRRLRLRL") == CAMPUS_C);
    
    // Go to next player (A)
    throwDice (testGame, 5);
    
    // Pass player
    testAction.actionCode = PASS;  
    makeAction (testGame, testAction);
    
    // Check vertices are still correct
    assert (getCampus (testGame, "LRR") == CAMPUS_A);
    assert (getCampus (testGame, "RLLRRLLRLR") == CAMPUS_B);
    assert (getCampus (testGame, "LRLRLRRLRL") == CAMPUS_B);
    assert (getCampus (testGame, "") == GO8_A);
    assert (getCampus (testGame, "LRRRLRLRL") == CAMPUS_C);
    
    // Go to next turn (B)
    throwDice (testGame, 3);
    
    // Create a campus
    testAction.actionCode = BUILD_GO8;  
    strcpy (testAction.destination, "RRLRL");
    makeAction (testGame, testAction);
    
    // Check campus is built and other vertices are still empty
    assert (getCampus (testGame, "LRLBR") == VACANT_VERTEX);
    assert (getCampus (testGame, "LRR") == CAMPUS_A);
    assert (getCampus (testGame, "RLLRRLLRLR") == CAMPUS_B);
    assert (getCampus (testGame, "RLLRRLLRLRRRBB") == CAMPUS_B);
    assert (getCampus (testGame, "RRLRL") == GO8_B);
    assert (getCampus (testGame, "") == GO8_A);
    assert (getCampus (testGame, "LRRRLRLRL") == CAMPUS_C);
    
    disposeGame (testGame);
    printf ("getCampus works - You are Awesome!\n\n");
    
}


// test GetArcs function
void testGetARCs (void) {
    
    printf ("Testing getARCs\n");
    // Create a game
    int disciplines [] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // Check all players start with 0 arcs
    assert (getARCs (testGame, UNI_A) == 0);
    assert (getARCs (testGame, UNI_B) == 0);
    assert (getARCs (testGame, UNI_C) == 0);
    
    // Go to next turn (A)
    throwDice (testGame, 3);
    
    // Create and execute action that creates an arc
    action testAction;
    testAction.actionCode = OBTAIN_ARC; 
    strcpy (testAction.destination, "LBL");
    makeAction (testGame, testAction);
    
    // Check first player has 1 arc, others still have none
    assert (getARCs (testGame, UNI_A) == 1);
    assert (getARCs (testGame, UNI_B) == 0);
    assert (getARCs (testGame, UNI_C) == 0);
    
    // Go to next player (B)
    throwDice (testGame, 5);
    
    // Create 2 arcs
    strcpy (testAction.destination, "RRLRL"); 
    makeAction (testGame, testAction);
    strcpy (testAction.destination, "RLLRRLL"); 
    makeAction (testGame, testAction);
    
    // Check each player has the right number of arcs
    assert (getARCs (testGame, UNI_A) == 1);
    assert (getARCs (testGame, UNI_B) == 2);
    assert (getARCs (testGame, UNI_C) == 0);
    
    // Go to next player (C)
    throwDice (testGame, 5);
    
    // Pass player
    testAction.actionCode = PASS; 
    makeAction (testGame, testAction);
    
    // Check each player has the right number of arcs
    assert (getARCs (testGame, UNI_A) == 1);
    assert (getARCs (testGame, UNI_B) == 2);
    assert (getARCs (testGame, UNI_C) == 0);
    
    // Go to next player (A)
    throwDice (testGame, 2);
    
    // Check each player has the right number of arcs
    assert (getARCs (testGame, UNI_A) == 1);
    assert (getARCs (testGame, UNI_B) == 2);
    assert (getARCs (testGame, UNI_C) == 0);
    
    // Pass player
    testAction.actionCode = PASS; 
    makeAction (testGame, testAction);
    
    // Go to next player (B)
    throwDice (testGame, 5);
    
    // Pass player
    testAction.actionCode = PASS; 
    makeAction (testGame, testAction);
    
    // Check each player has the right number of arcs
    assert (getARCs (testGame, UNI_A) == 1);
    assert (getARCs (testGame, UNI_B) == 2);
    assert (getARCs (testGame, UNI_C) == 0);
    
    // Go to next player (C)
    throwDice (testGame, 5);
    
    // Create an arc
    testAction.actionCode = OBTAIN_ARC; 
    strcpy (testAction.destination, "RLLRRLLRLRR"); 
    makeAction (testGame, testAction);
    
    // Check each player has the right number of arcs
    assert (getARCs (testGame, UNI_A) == 1);
    assert (getARCs (testGame, UNI_B) == 2);
    assert (getARCs (testGame, UNI_C) == 1);
    disposeGame (testGame);
    printf ("getARCs works - You are Awesome!\n\n");

}

void testGetPublications (void) {
    
    printf ("Testing getPublications\n");
    // Create a game
    int disciplines [] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // Check all players start with 0 publications
    assert (getPublications (testGame, UNI_A) == 0);
    assert (getPublications (testGame, UNI_B) == 0);
    assert (getPublications (testGame, UNI_C) == 0);
    
    // Go to next turn (A)
    throwDice (testGame, 3);
    
    // Create and execute action that creates a publication
    action testAction;
    testAction.actionCode = OBTAIN_PUBLICATION; 
    makeAction (testGame, testAction);
    
    // Check first player has 1 publication, others still have none
    assert (getPublications (testGame, UNI_A) == 1);
    assert (getPublications (testGame, UNI_B) == 0);
    assert (getPublications (testGame, UNI_C) == 0);
    
    // Go to next player (B)
    throwDice (testGame, 5);
    
    // Create 2 publications
    makeAction (testGame, testAction);
    makeAction (testGame, testAction);
    
    // Check B has 2 publications and other players are also correct
    assert (getPublications (testGame, UNI_A) == 1);
    assert (getPublications (testGame, UNI_B) == 2);
    assert (getPublications (testGame, UNI_C) == 0);
    
    // Go to next player (C)
    throwDice (testGame, 5);
    
    // Pass player
    testAction.actionCode = PASS; 
    makeAction (testGame, testAction);
    
    // Check number of publications is correct
    assert (getPublications (testGame, UNI_A) == 1);
    assert (getPublications (testGame, UNI_B) == 2);
    assert (getPublications (testGame, UNI_C) == 0);
    
    // Go to next player (A)
    throwDice (testGame, 2);
    assert (getPublications (testGame, UNI_A) == 1);
    assert (getPublications (testGame, UNI_B) == 2);
    assert (getPublications (testGame, UNI_C) == 0);
    
    // Pass player
    testAction.actionCode = PASS; 
    makeAction (testGame, testAction);
    
    // Check number of publications is correct
    assert (getPublications (testGame, UNI_A) == 1);
    assert (getPublications (testGame, UNI_B) == 2);
    assert (getPublications (testGame, UNI_C) == 0);
    
    // Go to next player (B)
    throwDice (testGame, 5);
    
    // Create a publications
    testAction.actionCode = OBTAIN_PUBLICATION; 
    makeAction (testGame, testAction);
    
    // Check number of publications is correct
    assert (getPublications (testGame, UNI_A) == 1);
    assert (getPublications (testGame, UNI_B) == 3);
    assert (getPublications (testGame, UNI_C) == 0);
    
    // Go to next player (C)
    throwDice (testGame, 5);
    
    // Create a publications
    makeAction (testGame, testAction);
    
    // Check number of publications is correct
    assert (getPublications (testGame, UNI_A) == 1);
    assert (getPublications (testGame, UNI_B) == 3);
    assert (getPublications (testGame, UNI_C) == 1);
    
    disposeGame (testGame);
    printf ("getPublications Works - You are Awesome!\n\n");
}

void testGetDiceValue (void) {
    
    printf ("Testing getDiceValue\n");
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    int dice[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);
    printf ("here!");
    assert (getDiceValue (testGame, REGION_0) == dice[0]);
    assert (getDiceValue (testGame, REGION_1) == dice[1]);
    assert (getDiceValue (testGame, REGION_2) == dice[2]);
    assert (getDiceValue (testGame, REGION_3) == dice[3]);
    assert (getDiceValue (testGame, REGION_4) == dice[4]);
    assert (getDiceValue (testGame, REGION_5) == dice[5]);
    assert (getDiceValue (testGame, REGION_6) == dice[6]);
    assert (getDiceValue (testGame, REGION_7) == dice[7]);
    assert (getDiceValue (testGame, REGION_8) == dice[8]);
    assert (getDiceValue (testGame, REGION_9) == dice[9]);
    assert (getDiceValue (testGame, REGION_10) == dice[10]);
    assert (getDiceValue (testGame, REGION_11) == dice[11]);
    assert (getDiceValue (testGame, REGION_12) == dice[12]);
    assert (getDiceValue (testGame, REGION_13) == dice[13]);
    assert (getDiceValue (testGame, REGION_14) == dice[14]);
    assert (getDiceValue (testGame, REGION_15) == dice[15]);
    assert (getDiceValue (testGame, REGION_16) == dice[16]);
    assert (getDiceValue (testGame, REGION_17) == dice[17]);
    assert (getDiceValue (testGame, REGION_18) == dice[18]);
    
    printf ("getDiceValue works - You are Awesome!\n\n");
}

// needs value of turn count which will be stored in the game struct
// determines which unis turn it is by using modulus 3
// if turn count is -1, it's no ones turn. Uni A always goes first.


void testGetWhoseTurn (void) {
    
    printf ("Testing getWhoseTurn\n");
    int turnCounter = 0;
    int turn2 = 1;
    
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);
    
    // test first 4 turns throw by throw

    assert (getWhoseTurn (testGame) == NO_ONE);
    throwDice (testGame, 2);
    assert (getWhoseTurn (testGame) == UNI_A);
    throwDice (testGame, 4);
    assert (getWhoseTurn (testGame) == UNI_B);
    throwDice (testGame, 6);
    assert (getWhoseTurn (testGame) == UNI_C);
    throwDice (testGame, 3);
    
    //test next heaps of turns so see if it breaks later on.
    
    
    while (turnCounter < 9000) {
        while (turn2 <= 3) {
            assert (getWhoseTurn (testGame) == turn2);
            throwDice (testGame, 3);
            turn2 ++;
        }
        turn2 = 1;
        turnCounter ++;
    }
  
    printf ("getWhoseTurn works - You are Awesome!\n\n");
    
}

void testGetKPIpoints (void) {
    
    printf("Testing getKPIpoints\n");
    
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);
    
    // assert initial KPIs are 2*no of campus points == 20
    
    assert (getKPIpoints (testGame, UNI_A) == 20);
    assert (getKPIpoints (testGame, UNI_B) == 20);
    assert (getKPIpoints (testGame, UNI_C) == 20);
    
    //advance turn to UNI_A, build campus, check +10 KPI points
    
    throwDice (testGame, 4);
    
    action testAction;
    testAction.actionCode = BUILD_CAMPUS;
    strcpy (testAction.destination, "LRRLRLRLRLRBRL");
    makeAction (testGame, testAction);
    
    assert (getKPIpoints (testGame, UNI_A) == 30);
    assert (getKPIpoints (testGame, UNI_B) == 20);
    assert (getKPIpoints (testGame, UNI_C) == 20);
    
    //advance to UNI_B build arc, check +2 for arc and +10 for most arcs
    
    throwDice (testGame, 6);
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "RRLLL"); 
    makeAction (testGame, testAction);
    
    assert (getKPIpoints (testGame, UNI_A) == 30);
    assert (getKPIpoints (testGame, UNI_B) == 32);
    assert (getKPIpoints (testGame, UNI_C) == 20);
    
    //advance to UNI_C get publication, check for most publications
    
    throwDice (testGame, 4);
    
    testAction.actionCode = OBTAIN_PUBLICATION;
    makeAction (testGame, testAction);
    
    assert (getKPIpoints (testGame, UNI_A) == 30);
    assert (getKPIpoints (testGame, UNI_B) == 32);
    assert (getKPIpoints (testGame, UNI_C) == 30);
    
    //advance to UNI_A get publication and get GO8, check only +10
    // as not first uni to reach most publications
    
    throwDice (testGame, 4);
    testAction.actionCode = BUILD_GO8;
    strcpy (testAction.destination, "LBL"); 
    makeAction (testGame, testAction);
    assert (getKPIpoints (testGame, UNI_A) == 40);
    assert (getKPIpoints (testGame, UNI_B) == 32);
    assert (getKPIpoints (testGame, UNI_C) == 30);
    
    //obtain arc, test is now most arcs
    
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "LRR");
    makeAction (testGame, testAction);
    strcpy (testAction.destination, "LRRL");
    makeAction (testGame, testAction);
    
    assert (getKPIpoints (testGame, UNI_A) == 54);
    assert (getKPIpoints (testGame, UNI_B) == 22);
    assert (getKPIpoints (testGame, UNI_C) == 30);
    
    //advance to UNI_B obtain IP
    
    throwDice (testGame, 4);
    testAction.actionCode = OBTAIN_IP_PATENT;
    makeAction (testGame, testAction);
    
    assert (getKPIpoints (testGame, UNI_A) == 54);
    assert (getKPIpoints (testGame, UNI_B) == 32);
    assert (getKPIpoints (testGame, UNI_C) == 30);
    
    
    
    printf ("getKPIpoints works - You are Awesome!\n\n");
    
}

void testGetIPs (void) {
    
    printf("Testing getIPs\n");
    
    // initialise testGame test all start at 0
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int diceScores[] = DEFAULT_DICE;
    //Create a new game to test on
    Game testGame = newGame (disciplines, diceScores);
    assert (getIPs (testGame, UNI_A) == 0);
    assert (getIPs (testGame, UNI_B) == 0);
    assert (getIPs (testGame, UNI_C) == 0);
    
    //advance turn to UNI_A obtain patent
    throwDice (testGame, 4);
    action testAction;
    testAction.actionCode = OBTAIN_IP_PATENT;
    makeAction (testGame, testAction);
    
    assert (getIPs (testGame, UNI_A) == 1);
    assert (getIPs (testGame, UNI_B) == 0);
    assert (getIPs (testGame, UNI_C) == 0);
    
    //advance turn to UNI_C obtain patent
    throwDice (testGame, 3);
    throwDice (testGame, 2);
    
    makeAction (testGame, testAction);
    
    assert (getIPs (testGame, UNI_A) == 1);
    assert (getIPs (testGame, UNI_B) == 0);
    assert (getIPs (testGame, UNI_C) == 1);
    
    //advance turn to UNI_B obtain patent
    
    throwDice (testGame, 6);
    throwDice (testGame, 8);
    makeAction (testGame, testAction);
    
    assert (getIPs (testGame, UNI_A) == 1);
    assert (getIPs (testGame, UNI_B) == 1);
    assert (getIPs (testGame, UNI_C) == 1);
    
    throwDice (testGame, 8);
    
    makeAction (testGame, testAction);
    makeAction (testGame, testAction);
    
    assert (getIPs (testGame, UNI_A) == 1);
    assert (getIPs (testGame, UNI_B) == 1);
    assert (getIPs (testGame, UNI_C) == 3);
    
    printf ("getIPs works - You are Awesome!\n\n");
}

// testing: void disposeGame (Game g);
// free all the memory malloced for the game
void testDisposeGame (void) {
    printf ("Testing disposeGame\n");
    
    // create a test game
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // just run the function
    // may be need to check if game is not pointing to anything meaningful anymore
    // i.e. pointer is cleared
    disposeGame (testGame);

    printf ("disposeGame works - You are Awesome!\n\n");
}

// testing: int getDiscipline (Game g, int regionID);
// what type of students are produced by the specified region?
void testGetDiscipline (void) {
    printf ("Testing getDiscipline\n");
    
    // create a test game
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // assert if the discipline in the region 1 is as defined in the DEFAULT_DISCIPLINES
    assert (getDiscipline (testGame, 1) == STUDENT_MMONEY);

    // assert if the discipline in the region 0 is as defined in the DEFAULT_DISCIPLINES
    assert (getDiscipline (testGame, 0) == STUDENT_BQN);

    // assert if the discipline in the region 18 (last) is as defined in the DEFAULT_DISCIPLINES
    assert (getDiscipline (testGame, 18) == STUDENT_BPS);

    printf ("getDiscipline works - You are Awesome!\n\n");
}

// testing: int getTurnNumber (Game g);
// return the current turn number of the game -1,0,1, ..
void testGetTurnNumber (void) {
    printf ("Testing getTurnNumber\n");
    
    // create a test game
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // use throwDice to make a turn
    throwDice (testGame, 2);
    // assert if the turn number has increased
    assert (getTurnNumber (testGame) == 0);
    // use throwDice to make a turn
    throwDice (testGame, 2);
    assert (getTurnNumber (testGame) == 1);
    printf ("getTurnNumber works - You are Awesome!\n\n");
}

// testing: int isLegalAction (Game g, action a);
// returns TRUE if it is legal for the current
// player to make the specified action, FALSE otherwise.
//
// "legal" means everything is legal: 
//   * that the action code is a valid action code which is legal to 
//     be made at this time
//   * that any path is well formed and legal ie consisting only of 
//     the legal direction characters and of a legal length, 
//     and which does not leave the island into the sea at any stage.
//   * that disciplines mentioned in any retraining actions are valid 
//     discipline numbers, and that the university has sufficient
//     students of the correct type to perform the retraining
//
// eg when placing a campus consider such things as: 
//   * is the path a well formed legal path 
//   * does it lead to a vacent vertex?
//   * under the rules of the game are they allowed to place a 
//     campus at that vertex?  (eg is it adjacent to one of their ARCs?)
//   * does the player have the 4 specific students required to pay for 
//     that campus?
// It is not legal to make any action during Terra Nullis ie 
// before the game has started.
// It is not legal for a player to make the moves OBTAIN_PUBLICATION 
// or OBTAIN_IP_PATENT (they can make the move START_SPINOFF)
// you can assume that any pths passed in are NULL terminated strings.
// 
// ACTIONS: 
// #define PASS 0
// #define BUILD_CAMPUS 1
// #define BUILD_GO8 2
// #define OBTAIN_ARC 3
// #define START_SPINOFF 4
// #define OBTAIN_PUBLICATION 5
// #define OBTAIN_IP_PATENT 6
// #define RETRAIN_STUDENTS 7
//
// DISCIPLINES:
// #define STUDENT_THD 0
// #define STUDENT_BPS 1
// #define STUDENT_BQN 2
// #define STUDENT_MJ  3
// #define STUDENT_MTV 4
// #define STUDENT_MMONEY 5
//
// LATER: this test will grow significantly to test all possible loopholes and exploits
// later: for all disciplines check valid/invalid situations depending on the rules
// later: obtain_pub/obtain_patent for player - not sure yet
// later: check amount of students for the campus placing
void testIsLegalAction (void) {
    printf("Testing isLegalAction\n");
    
    // (2,0) is the starting point
    
    // create a test game
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    int player = 0;
    printf("> Standard setup game. Step by step actions...\n");
    Game testGame = newGame(disciplines, dice);
    // create a test action
    action testAction;

    // it is not legal to make any action during Terra Nullis ie before the game started
    testAction.actionCode = PASS;
    assert(isLegalAction(testGame, testAction) == FALSE);
    
    /* Step by step giving resources, checking if he can do the action etc. emulating the game */
    
    // Give resources to player 1
    printf("> Giving player 1 resources on 6 and 11\n");
    throwDice(testGame, 6); // this gives 1 MJ and the turn to player 1
    throwDice(testGame, 6); // this gives 1 MJ -- player 2
    throwDice(testGame, 6); // this gives 1 MJ -- player 3
    throwDice(testGame, 11); // this gives 1 MTV -- player 1
    throwDice(testGame, 11); // this gives 1 MTV -- player 2
    throwDice(testGame, 11); // this gives 1 MTV -- player 3
    throwDice(testGame, 11); // this gives 1 MTV -- player 1
    
    // is it the turn of player 1?
    printf("> Is it the turn of player 1?\n");
    player = getWhoseTurn(testGame);
    assert(player == 1);
    
    // getKPIpoints - should have 36 now
    printf("> Starting points = 20. To make sure gameplay is working fine.\n");
    assert(getKPIpoints(testGame, 1) == 20); // that's what it should be
    
    
    printf("> Campus with no ARC test\n");
    // Player 1 has: 3 x BPS, 3 x B?, 5 x MTV, 4 x MJ, 1 x M$
    // check that he can't build a CAMPUS
    testAction.actionCode = BUILD_CAMPUS;
    strcpy(testAction.destination, "R"); // intersection between MMONEY and MTV
    assert(isLegalAction(testGame, testAction) == FALSE); // can't build there since no ARC

    printf("> Building ARCs\n");
    // but can build an ARC!
    testAction.actionCode = OBTAIN_ARC;
    strcpy(testAction.destination, "R"); // intersection between MMONEY and MTV
    assert(isLegalAction(testGame, testAction) == TRUE); // can build the ARC
    makeAction(testGame, testAction); // build
    printScore(testGame, 1);
    assert(getKPIpoints(testGame, 1) == 32); // that's what it should be - WE GET THE MOST ARCs BONUS
    // Player 1 has: 2 x BPS, 2 x B?, 5 x MTV, 4 x MJ, 1 x M$
    printf("> Campus on the same edge test\n");
    // check that he still can't build a CAMPUS
    testAction.actionCode = BUILD_CAMPUS;
    strcpy(testAction.destination, "R"); // intersection between MMONEY and MTV
    assert(isLegalAction(testGame, testAction) == FALSE); // can't build because on the same edge
    printf("> Two more valid ARCs\n");
    // two more ARCs
    testAction.actionCode = OBTAIN_ARC;
    strcpy(testAction.destination, "RL"); // intersection between MMONEY, MTV, BPS
    assert(isLegalAction(testGame, testAction) == TRUE); // can build the ARC
    makeAction(testGame, testAction); // build
    // Player 1 has: 1 x BPS, 1 x B?, 5 x MTV, 4 x MJ, 1 x M$
    testAction.actionCode = OBTAIN_ARC;
    strcpy(testAction.destination, "RLL"); // intersection between MTV, BPS, BQN
    assert(isLegalAction(testGame, testAction) == TRUE); // can build the ARC
    makeAction(testGame, testAction); // build
    printf("> No more resources for ARCs - test\n");
    // Player 1 has: 0 x BPS, 0 x B?, 5 x MTV, 4 x MJ, 1 x M$
    // shouldn't be able to build an ARC - no resources
    testAction.actionCode = OBTAIN_ARC;
    strcpy(testAction.destination, "RLLR"); // intersection between BPS, BQN, THD
    assert(isLegalAction(testGame, testAction) == FALSE); // can't build the ARC

    // getKPIpoints - should have 36 now
    printf("> Built 3 ARCs - 36 points total counting for Most ARCs Bonus\n");
    assert(getKPIpoints(testGame, 1) == 36); // that's what it should be


    // Player 1 has: 0 x BPS, 0 x B?, 5 x MTV, 4 x MJ, 1 x M$
    // retrain some students    
    printf("> Can't retrain from M$ - not enough\n");
    // can't retrain from M$ - not enough of them
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_MMONEY;
    testAction.disciplineTo = STUDENT_BPS;
    assert(isLegalAction(testGame, testAction) == FALSE);
    
    printf("> Can retrain from MTV to BPS\n");
    // now can retrain from MTV to BPS
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_MTV;
    testAction.disciplineTo = STUDENT_BPS;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    // Player 1 has: 1 x BPS, 0 x B?, 2 x MTV, 4 x MJ, 1 x M$
        
    printf("> Can retrain from MJ to BQN\n");
    // can retrain from MJ to BQN
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_MJ;
    testAction.disciplineTo = STUDENT_BQN;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    // Player 1 has: 1 x BPS, 1 x B?, 2 x MTV, 1 x MJ, 1 x M$
    
    printf("> Can build campus\n");
    // Now it should be possible to build a campus
    testAction.actionCode = BUILD_CAMPUS;
    strcpy(testAction.destination, "RLL"); // intersection between MTV, BPS, BQN
    assert(isLegalAction (testGame, testAction) == TRUE); // can build
    makeAction(testGame, testAction); // build
    // Player 1 has: 0 x BPS, 0 x B?, 1 x MTV, 0 x MJ, 1 x M$
    
    // LATER: put in getStudents test (use the setup above and increase like below)
    // to check if the point increasing works correctly

    // getKPIpoints - should have 36 now
    printf("> Built a Campus - 46 points total\n");
    assert(getKPIpoints(testGame, 1) == 46); // that's what it should be
    

    // more resources on 3,4,11
    throwDice(testGame, 11); // this gives 2 MTV to player 1 -- turn to player 2
    throwDice(testGame, 11); // this gives 2 MTV to player 1 -- turn to player 3
    throwDice(testGame, 11); // this gives 2 MTV to player 1 -- turn to player 1
    throwDice(testGame, 3); // this gives 1 BPS to player 1 -- turn to player 2
    throwDice(testGame, 3); // this gives 1 BPS to player 1 -- turn to player 3
    throwDice(testGame, 3); // this gives 1 BPS to player 1 -- turn to player 1
    throwDice(testGame, 3); // this gives 1 BPS to player 1 -- turn to player 2
    throwDice(testGame, 3); // this gives 1 BPS to player 1 -- turn to player 3
    throwDice(testGame, 3); // this gives 1 BPS to player 1 -- turn to player 1
    throwDice(testGame, 4); // this gives 1 BQN to player 1 -- turn to player 2
    throwDice(testGame, 4); // this gives 1 BQN to player 1 -- turn to player 3
    throwDice(testGame, 4); // this gives 1 BQN to player 1 -- turn to player 1
    throwDice(testGame, 4); // this gives 1 BQN to player 1 -- turn to player 2
    throwDice(testGame, 4); // this gives 1 BQN to player 1 -- turn to player 3
    throwDice(testGame, 4); // this gives 1 BQN to player 1 -- turn to player 1

    // LATER: check that 2 campuses indeed give 2 MTV!
    
    
    // Player 1 has: 6 x BPS, 6 x B?, 7 x MTV, 0 x MJ, 1 x M$
    // let's build GO8 on this same spot and check that it gives 10 KPIs only (as per spec - we're losing normal one)
    // at the same time check if isLegal works for GO8
    // now shouldn't be able to build - not enough resources
    testAction.actionCode = BUILD_GO8;
    strcpy(testAction.destination, "RLL"); // intersection between MTV, BPS, BQN
    assert(isLegalAction (testGame, testAction) == FALSE); // can't build
    // retrain to get 3 M$ and 2 MJ
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BPS;
    testAction.disciplineTo = STUDENT_MMONEY;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BPS;
    testAction.disciplineTo = STUDENT_MMONEY;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BQN;
    testAction.disciplineTo = STUDENT_MJ;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.disciplineFrom = STUDENT_BQN;
    testAction.disciplineTo = STUDENT_MJ;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    // Player 1 has: 0 x BPS, 0 x B?, 7 x MTV, 2 x MJ, 3 x M$
    // now should be able to build
    testAction.actionCode = BUILD_GO8;
    strcpy(testAction.destination, "RLL"); // intersection between MTV, BPS, BQN
    assert(isLegalAction (testGame, testAction) == TRUE); // can build
    makeAction(testGame, testAction); // build
    printf("> GO8 rebuilt on campus should give 10 points only\n");
    // check KPI points!
    assert(getKPIpoints(testGame, 1) == 56); // that's what it should be
    // Player 1 has: 0 x BPS, 0 x B?, 7 x MTV, 0 x MJ, 0 x M$
    
  
    // now build another G08 in a new place to check that it gives 20 points

    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 2
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 3
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 1
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 2
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 3
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 1
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 2
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 3
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 1
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 2
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 3
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 1
    // Player 1 has: 12 x BPS, 12 x B?, 7 x MTV, 0 x MJ, 0 x M$

    printScore(testGame, 1);
    // retrain to get 3 M$ and 3 MJ
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BPS;
    testAction.disciplineTo = STUDENT_MMONEY;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BPS;
    testAction.disciplineTo = STUDENT_MMONEY;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BPS;
    testAction.disciplineTo = STUDENT_MMONEY;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BQN;
    testAction.disciplineTo = STUDENT_MJ;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.disciplineFrom = STUDENT_BQN;
    testAction.disciplineTo = STUDENT_MJ;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    testAction.disciplineFrom = STUDENT_BQN;
    testAction.disciplineTo = STUDENT_MJ;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    printScore(testGame, 1);
    // Player 1 has: 3 x BPS, 3 x B?, 7 x MTV, 3 x MJ, 3 x M$

    // test building GO8 without an ARC
    printf("> GO8 without an ARC\n");
    testAction.actionCode = BUILD_GO8;
    strcpy(testAction.destination, "RR"); // edge on MMONEY and near MTV retraining centre
    assert(isLegalAction (testGame, testAction) == FALSE); // can't build - no ARC

    printf("> ARC into the sea\n");
    testAction.actionCode = OBTAIN_ARC;
    // off limit ARC check
    strcpy(testAction.destination, "RRR"); // in the sea
    assert(isLegalAction (testGame, testAction) == FALSE); // shouldn't be able to
    printf("> Valid ARC for GO8\n");
    // normal ARC to proceed with tests
    strcpy(testAction.destination, "RR"); // edge on MMONEY and near MTV retraining centre
    assert(isLegalAction (testGame, testAction) == TRUE); // should be able to
    makeAction(testGame, testAction); // build
    // Player 1 has: 2 x BPS, 2 x B?, 7 x MTV, 3 x MJ, 3 x M$
    printf("> GO8 with an ARC but without a normal campus\n");
    testAction.actionCode = BUILD_GO8;
    strcpy(testAction.destination, "RR"); // edge on MMONEY and near MTV retraining centre
    assert(isLegalAction (testGame, testAction) == FALSE); // can't build - no normal campus yet

    printf("> Build a normal campus first\n");
    testAction.actionCode = BUILD_CAMPUS;
    strcpy(testAction.destination, "RR"); // edge on MMONEY and near MTV retraining centre
    assert(isLegalAction (testGame, testAction) == TRUE); // can build
    makeAction(testGame, testAction); // build
    
    // Player 1 has: 1 x BPS, 1 x B?, 6 x MTV, 2 x MJ, 3 x M$

    printf("> And build GO8 now with all things valid\n");
    testAction.actionCode = BUILD_GO8;
    strcpy(testAction.destination, "RR"); // edge on MMONEY and near MTV retraining centre
    assert(isLegalAction (testGame, testAction) == TRUE); // can build
    makeAction(testGame, testAction); // build

    // Player 1 has: 1 x BPS, 1 x B?, 6 x MTV, 0 x MJ, 0 x M$

    
    printf("> New GO8 should give 20 points\n");
    printScore(testGame, 1);
    assert(getKPIpoints(testGame, 1) == 78); // that's what it should be (1xARC + 1xG08)
    
    // TO DO:
    // building arcs adjacent / crossing other people's arcs
    // building campuses on other's arcs - shouldn't be possible anyway because no arc of yours but still
    // you can build campus on the intersection of ARCs if there is no other campus
    // build campus on existing campus of other people (intersection of arcs is possible but this should not be)
    // spinoff with no enough resources
    // no more than 8 GO8s can exist in the game
    
    // Player 1 has: 1 x BPS, 1 x B?, 6 x MTV, 0 x MJ, 0 x M$
    
    /* Special checks */

    printf("> Turn MTVs and M$s into THDs on Score 7\n");
    // get resources
    throwDice(testGame, 11); // this gives 3 MTV to player 1 -- turn to player 2
    throwDice(testGame, 11); // this gives 3 MTV to player 1 -- turn to player 3
    throwDice(testGame, 11); // this gives 3 MTV to player 1 -- turn to player 1

    // Player 1 has: 1 x BPS, 1 x B?, 15 x MTV, 0 x MJ, 0 x M$

    throwDice(testGame, 12); // this gives 2 M$ to player 1 -- turn to player 2
    throwDice(testGame, 12); // this gives 2 M$ to player 1 -- turn to player 3
    throwDice(testGame, 12); // this gives 2 M$ to player 1 -- turn to player 1

    // Player 1 has: 1 x BPS, 1 x B?, 15 x MTV, 0 x MJ, 6 x M$
    printScore(testGame, 1);

    throwDice(testGame, 7); // MTV/M$ -> THD and the turn to player 2
    throwDice(testGame, 7); // MTV/M$ -> THD --- player 3
    throwDice(testGame, 7); // MTV/M$ -> THD --- player 1

    // LATER: check how many you actually got now - should be 21 THDs
    printScore(testGame, 1);
    

    printf("> Can't retrain from THDs\n");
    // check that we can't retrain from THDs
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_THD;
    testAction.disciplineTo = STUDENT_BPS;
    assert(isLegalAction(testGame, testAction) == FALSE);
    
    // Player 1 has: THD: 21 BPS: 1 BQN: 1 MJ: 0 MTV: 0 M$: 0

    // SPIN OFF
    // START_SPINOFF can't be done in makeAction it's turned into OBTAIN_PUBLICATION/OBTAIN_IP_PATENT
    // within the runGame of CSE using random
    // but START_SPINOFF should be a valid action in isLegalAction
    // however OBTAIN_IP_PATENT and OBTAIN_PUBLICATION should be invalid
    testAction.actionCode = START_SPINOFF;
    assert (isLegalAction (testGame, testAction) == FALSE); // not enough resources

    // give resources
    throwDice(testGame, 11); // this gives 3 MTV to player 1 -- turn to player 2
    throwDice(testGame, 11); // this gives 3 MTV to player 1 -- turn to player 3
    throwDice(testGame, 11); // this gives 3 MTV to player 1 -- turn to player 1
    // Player 1 has: THD: 21 BPS: 1 BQN: 1 MJ: 0 MTV: 9 M$: 0

    throwDice(testGame, 12); // this gives 2 M$ to player 1 -- turn to player 2
    throwDice(testGame, 12); // this gives 2 M$ to player 1 -- turn to player 3
    throwDice(testGame, 12); // this gives 2 M$ to player 1 -- turn to player 1
    // Player 1 has: THD: 21 BPS: 1 BQN: 1 MJ: 0 MTV: 9 M$: 6

    // retrain for MJ from MTV (2 for 1 as we have the retraining centre!)
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_MTV;
    testAction.disciplineTo = STUDENT_MJ;
    assert(isLegalAction(testGame, testAction) == TRUE);
    makeAction(testGame, testAction); // retrain
    makeAction(testGame, testAction); // retrain
    // Player 1 has: THD: 21 BPS: 1 BQN: 1 MJ: 2 MTV: 5 M$: 6

    // LATER: check that retraining centre works and we indeed get 2 for 1
    
    testAction.actionCode = START_SPINOFF;
    assert (isLegalAction (testGame, testAction) == TRUE); // enough resources
    
    testAction.actionCode = OBTAIN_PUBLICATION;
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = OBTAIN_IP_PATENT;
    assert (isLegalAction (testGame, testAction) == FALSE);
    
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 2
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 3
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 1
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 2
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 3
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 1
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 2
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 3
    throwDice(testGame, 3); // this gives 2 BPS to player 1 -- turn to player 1
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 2
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 3
    throwDice(testGame, 4); // this gives 2 BQN to player 1 -- turn to player 1
    
    // Player 1 has: THD: 21 BPS: 13 BQN: 13 MJ: 0 MTV: 0 M$: 0
    
    // Can build many ARCs, so check weird paths
    // PATHs checks
    printf("> Testing paths... \n");
    testAction.actionCode = OBTAIN_ARC;
    // in the sea
    strcpy (testAction.destination, "LL");
    assert (isLegalAction (testGame, testAction) == FALSE);
    // invalid character path
    strcpy (testAction.destination, "LXX");
    assert (isLegalAction (testGame, testAction) == FALSE);
    // path too long
    strcpy (testAction.destination, "LLLLLLLLLLLLLLLLRRRRRRRRRRRRRRLL");
    assert (isLegalAction (testGame, testAction) == FALSE);
    
    
    /*    
    
    OUTDATED TESTS
    
    |
    |
    V
    
    // do a bunch of throw dice to give resources
    int turn = 0;
    while (turn < 50) {
        throwDice (testGame, rollDice (TRUE));
        turn++;
    }
    // now is it legal? - should be
    assert (isLegalAction (testGame, testAction) == TRUE);

    // next turn (Player C)
    throwDice (testGame, 4);
    
    // test action codes
    testAction.actionCode = PASS;
    assert (isLegalAction (testGame, testAction) == TRUE);
    
    while (player != UNI_A) {
        throwDice (testGame, rollDice (TRUE));
        player = getWhoseTurn (testGame);
    }
    // when the player starts it's supposed to have resources to build the arc
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "R");
    assert (isLegalAction (testGame, testAction) == TRUE);
    
    testAction.actionCode = BUILD_CAMPUS;
    strcpy (testAction.destination, "RRL");
    assert (isLegalAction (testGame, testAction) == FALSE);
    strcpy (testAction.destination, "RRRRRR");
    testAction.actionCode = BUILD_GO8;
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "RRRRRR");
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = START_SPINOFF;
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = OBTAIN_PUBLICATION;
    //assert (isLegalAction (testGame, testAction) == TRUE);
    testAction.actionCode = OBTAIN_IP_PATENT;
    //assert (isLegalAction (testGame, testAction) == TRUE);
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BPS;
    testAction.disciplineTo = STUDENT_BQN;
    assert (isLegalAction (testGame, testAction) == TRUE);
    testAction.actionCode = 21; // invalid code
    assert (isLegalAction (testGame, testAction) == FALSE);
    
    action makeCampuses;
    makeCampuses.actionCode = BUILD_CAMPUS;
    strcpy (makeCampuses.destination, "RRL");
    makeAction (testGame, makeCampuses);
    makeCampuses.actionCode = BUILD_CAMPUS;
    strcpy (makeCampuses.destination, "LRL");
    makeAction (testGame, makeCampuses);
    strcpy (makeCampuses.destination, "RLRLR");
    makeAction (testGame, makeCampuses);
    
    testAction.actionCode = BUILD_CAMPUS;
    strcpy (testAction.destination, "R");
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = BUILD_GO8;
    strcpy (testAction.destination, "LRLRL");
    assert (isLegalAction (testGame, testAction) == TRUE);
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "LRLRL");
    assert (isLegalAction (testGame, testAction) == TRUE);
    testAction.actionCode = OBTAIN_ARC;
    strcpy (testAction.destination, "R");
    assert (isLegalAction (testGame, testAction) == FALSE);
    strcpy (testAction.destination, "L");
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = START_SPINOFF;
    assert (isLegalAction (testGame, testAction) == TRUE);
    testAction.actionCode = OBTAIN_PUBLICATION;
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = OBTAIN_IP_PATENT;
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_BPS;
    testAction.disciplineTo = STUDENT_BQN;
    assert (isLegalAction (testGame, testAction) == TRUE);
    testAction.actionCode = RETRAIN_STUDENTS;
    testAction.disciplineFrom = STUDENT_THD;
    testAction.disciplineTo = STUDENT_BQN;
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = 21; // invalid code
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.actionCode = 8; // invalid code
    assert (isLegalAction (testGame, testAction) == FALSE);
    
    
    // check paths
    testAction.actionCode = OBTAIN_ARC;
    // normal path not next to another path/campus
    strcpy (testAction.destination, "LR");
    assert (isLegalAction (testGame, testAction) == FALSE);
    // normal path next to another path/campus
    //strcpy (testAction.destination, "LRLRLR");
    //assert (isLegalAction (testGame, testAction) == TRUE);
    // invalid character path
    strcpy (testAction.destination, "LXX");
    assert (isLegalAction (testGame, testAction) == FALSE);
    // path too long
    strcpy (testAction.destination, "LLLLLLLLLLLLLLLLRRRRRRRRRRRRRRLL");
    assert (isLegalAction (testGame, testAction) == FALSE);
    // path leading to nowhere (sea)
    strcpy (testAction.destination, "LLLL");
    assert (isLegalAction (testGame, testAction) == FALSE);
    
    // do a bunch of throw dice to give resources
    turn = 0;
    while (turn < 50) {
        throwDice (testGame, rollDice (TRUE));
        turn++;
    }
    
    // check disciplines for the retraining
    testAction.actionCode = RETRAIN_STUDENTS;
    // from THD
    testAction.disciplineFrom = STUDENT_THD;
    testAction.disciplineTo = STUDENT_THD;
    assert (isLegalAction (testGame, testAction) == FALSE);
    testAction.disciplineFrom = STUDENT_THD;
    testAction.disciplineTo = STUDENT_BQN;
    assert (isLegalAction (testGame, testAction) == FALSE);
    // from THD
    testAction.disciplineFrom = STUDENT_THD;
    testAction.disciplineTo = STUDENT_THD;
    assert (isLegalAction (testGame, testAction) == FALSE);
    // normal retraining
    testAction.disciplineFrom = STUDENT_BQN;
    testAction.disciplineTo = STUDENT_MJ;
    assert (isLegalAction (testGame, testAction) == TRUE);
    // normal retraining
    testAction.disciplineFrom = STUDENT_MTV;
    testAction.disciplineTo = STUDENT_MMONEY;
    assert (isLegalAction (testGame, testAction) == TRUE);
    */
}

// Testing: int getCampuses (Game g, int player);
// return the number of normal Campuses the specified player currently has
void testGetCampuses (void) {
    printf ("Testing getCampuses\n");
    int player = 0;
    int anotherPlayer = 0;
    
    // create a test game
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    Game testGame = newGame (disciplines, dice);
    
    // check that there are 2 campuses per uni
    assert (getCampuses (testGame, UNI_A) == 2);
    assert (getCampuses (testGame, UNI_B) == 2);
    assert (getCampuses (testGame, UNI_C) == 2);
    
    // make a turn
    throwDice (testGame, 2);
        
    // assert that the vertex at the path is vacant
    assert (getCampus (testGame, "LRRRL") == VACANT_VERTEX);

    // get player ID
    player = getWhoseTurn (testGame);
    // create a test action to make a campus
    action testAction;
    testAction.actionCode = BUILD_CAMPUS;
    strcpy (testAction.destination, "LRRRL");
    // build the campus
    makeAction (testGame, testAction);
    // check that the campus amount is 3 now
    assert (getCampuses (testGame, player) == 3);
    
    // one more campus
    // assert that the vertex at the path is vacant
    assert (getCampus (testGame, "LRRRLL") == VACANT_VERTEX);
    strcpy (testAction.destination, "LRRRLL");
    // build the campus
    makeAction (testGame, testAction);
    // check that the campus amount is 4 now
    assert (getCampuses (testGame, player) == 4);

    // one campus for another player
    // make turns
    // get player ID that is different from player
    anotherPlayer = player;
    while (anotherPlayer == player) {
        throwDice (testGame, 3);        
        anotherPlayer = getWhoseTurn (testGame);
    }
    assert (getCampus (testGame, "LRR") == VACANT_VERTEX);
    // create a test action to make a campus
    testAction.actionCode = BUILD_CAMPUS;
    strcpy (testAction.destination, "LRR");
    // build the campus
    makeAction (testGame, testAction);
    // check that the campus amount is 3 now
    assert (getCampuses (testGame, anotherPlayer) == 3);
    printf ("getCampuses works - You are Awesome!\n\n");
}

// roll the dice randomly
int rollDice (int no7) {
    printf ("Rolling dice...\n");
    int dice1 = 0;
    int dice2 = 0;
    int diceScore = 7;
    while (!no7 || (no7 && diceScore == 7)) {
        // random int between 0 and 6
        dice1 = rand () % 6 + 1;
        dice2 = rand () % 6 + 1;
        diceScore = dice1 + dice2;
    }
    printf ("Score is: %d\n", diceScore);
    return diceScore;
}

void failedExternalTests(void){
    printf("Testing EXT1\n");
    action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 11);
    throwDice(g, 11);
    throwDice(g, 11);
    throwDice(g, 11);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "\0", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 0, a.disciplineTo = 0;
    assert (isLegalAction(g, a) == FALSE);
}

// this is a wrong test from others
// they assume we start with 24 points
// whereas the rules say we start with just 2 campuses
// online game version has 2 ARCs but it's not our spec
void externalTest001(void) {
    printf("External Test 001 start\n");
    //action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    //assert(getKPIpoints(g, 1) != 24); that's what they tested
    assert(getKPIpoints(g, 1) == 20); // that's what it should be
    printf("External Test 001 end\n");
}

// Test for simon.shield
void failedExternalTestSimon(void){
    printf("External Test Simon\n");
    int player = 1; 
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    assert(getExchangeRate(g, player, 1, 2) == 3);
    printf("External Test Simon END\n");
}

void failedExternalTestMeghana(void){
    printf("External Test Meghana\n");
    action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 2);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 134542712, a.disciplineTo = -1076558664;
    assert(isLegalAction(g, a) == FALSE);
    printf("External Test Meghana END\n");
}


// Authors: vidler 
// Testing make
// Author code style is kept!
// testing if we have 0 students left after trading
// by the looks of it it's an invalid setup
void externalTest002(void) {
    printf("External Test 002 start\n");
    action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    printf("PLayer 3 had %d student in 0\n", getStudents(g, 3, 0));
    printf("PLayer 3 had %d student in 1\n", getStudents(g, 3, 1));
    printf("PLayer 3 had %d student in 2\n", getStudents(g, 3, 2));
    printf("PLayer 3 had %d student in 3\n", getStudents(g, 3, 3));
    printf("PLayer 3 had %d student in 4\n", getStudents(g, 3, 4));
    printf("PLayer 3 had %d student in 5\n", getStudents(g, 3, 5));

    printf("Throwing the dice three times\n");
    throwDice(g, 8);
    throwDice(g, 8);
    throwDice(g, 8);
    printf("PLayer 3 had %d student in 0\n", getStudents(g, 3, 0));
    printf("PLayer 3 had %d student in 1\n", getStudents(g, 3, 1));
    printf("PLayer 3 had %d student in 2\n", getStudents(g, 3, 2));
    printf("PLayer 3 had %d student in 3\n", getStudents(g, 3, 3));
    printf("PLayer 3 had %d student in 4\n", getStudents(g, 3, 4));
    printf("PLayer 3 had %d student in 5\n", getStudents(g, 3, 5));

    assert(getStudents(g, 3, 1) == 3);

    a.actionCode = RETRAIN_STUDENTS;
    strncpy(a.destination, "RRL", PATH_LIMIT - 1);
    a.disciplineFrom = 3, a.disciplineTo = 5;
    makeAction(g, a);

    printf("Make the Trade\n");

    printf("PLayer 3 had %d student in 0\n", getStudents(g, 3, 0));
    printf("PLayer 3 had %d student in 1\n", getStudents(g, 3, 1));
    printf("PLayer 3 had %d student in 2\n", getStudents(g, 3, 2));
    printf("PLayer 3 had %d student in 3\n", getStudents(g, 3, 3));
    printf("PLayer 3 had %d student in 4\n", getStudents(g, 3, 4));
    printf("PLayer 3 had %d student in 5\n", getStudents(g, 3, 5));


    assert(getStudents(g, 3, 5) == 2);
    printf("PLayer 3 had %d student in 1\n", getStudents(g, 3, 1));
    assert(getStudents(g, 3, 1) == 3);
    printf("External Test 002 end\n");
}


// print player's current score for testing purposes
void printScore (Game g, int player) {
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
