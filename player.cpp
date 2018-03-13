#include "player.hpp"
#include <vector>

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    // Initializes the side of the player and the opponent
    playerside = side;
    otherside = (side == BLACK) ? WHITE : BLACK;

}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    // check if game is finished
    // if not:
    //      check every square on board for valid move
    //      if valid, do the move

    // opponent does move / skips move
    if (b->hasMoves(otherside)) {
        b->doMove(opponentsMove, otherside);
    }

    Move *m = new Move(0, 0), *best_move = new Move(0, 0);
    int move_points, best_move_points = -1000;
    int opm_points, worst_move_points = 1000;
    Board *b_copy = b->copy();
    Board *b2_copy = b->copy();
    int free_cells = 0;

    if (b->hasMoves(playerside)) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

                m->setX(i);
                m->setY(j);

                if (b->checkMove(m, playerside)) {
                    //cerr << m->getX() << " " << m->getY() << endl;

                    //we check that m is a valid move on our side
                    //now for m we should check what is the min score we get after 
                    //the opponent makes a move



                    b_copy = b->copy();
                    b_copy->doMove(m, playerside);

                    //b_copy is a mew board with our move
                    //now we try all the moves our guy can make 

                    //if the guy doesn't have moves our score is just our score
                    // im too lazy to write a separate func for that

                    free_cells = 64 - b_copy->countBlack() -  b_copy->countWhite();

                    if ((! b_copy->hasMoves(otherside)) || (b_copy->count(otherside) > 3* b_copy->count(playerside)))

                   // if (! b_copy->hasMoves(otherside))

                    {

                        move_points = b_copy->count(playerside) - b_copy->count(otherside);


                    }

                    else //if the guy has moves

                        //we check what's our worst score after his move
                        //that's the score for our move

                    {

                        Move *opm = new Move(0, 0); //opponent move
                        for (int k = 0; k< 8; k++)
                        {
                            for (int n = 0; n < 8; n++)
                            {
                                opm->setX(k);
                                opm->setY(n);

                                if (b_copy->checkMove(opm, otherside)) //if valid move for the guy
                                {

                                    b2_copy = b_copy->copy();
                                    b2_copy->doMove(opm, otherside); //we made a copy of the b_copy and applied oppoent move


                                    //the guy makes a move so that our score after his is minimal
                                    //so he does the same stuff copies the board and checks for every move our score
                                    //haven't implemented yet

                                    opm_points = b2_copy->count(playerside) - b2_copy->count(otherside);


                                   // if ((n % 7 == 0) || (k % 7 == 0)) 
                                    //    opm_points += abs(opm_points) * (-3);




                                    //we counted our points after the guys move, thats opm_points
                                    //he will make a move so that we have less points

                                    if (opm_points < worst_move_points)
                                    {
                                        worst_move_points = opm_points;
                                    }

                                }

                            }
                        }


                        move_points = worst_move_points;
                    }
                    

                    if ((free_cells > 4) && (b_copy->count(playerside) > 2))
                    {

                        if ((i % 7 == 0) && (j % 7 == 0)) 
                            move_points += abs(move_points) * 5;
                        

                        else if ((i % 5 == 1) && (j % 5 == 1))
                            move_points += abs(move_points) * (-3);
                            
                        else if ((i % 5 == 1) && (j % 7 == 0))
                            move_points += abs(move_points) * (-2);

                        else if ((j % 5 == 1) && (i % 7 == 0))
                            move_points += abs(move_points) *(-2);

                        else if ((i % 7 == 0) || (j % 7 == 0))
                            move_points += abs(move_points)* (5);
                    }



                    //old code
                    if (best_move_points < move_points) {
                        best_move_points = move_points;
                        best_move->setX(i);
                        best_move->setY(j);

                        //cerr << "Best Move: " << best_move->getX() << " " << best_move->getY() << endl;
                        //cerr << "Best Points: " << best_move_points << endl << endl;
                    }
                }
                //cerr << "BBM: " << best_move->getX() << " " << best_move->getY() << endl;
            }
        }

        b->doMove(best_move, playerside);
        return best_move;
    }

    return nullptr;
}

// LOREM IPSUM

// CS2 great class