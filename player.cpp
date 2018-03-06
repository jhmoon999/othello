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
    Board *b_copy = b->copy();

    if (b->hasMoves(playerside)) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {

                m->setX(i);
                m->setY(j);

                if (b->checkMove(m, playerside)) {
                    //cerr << m->getX() << " " << m->getY() << endl;

                    b_copy = b->copy();
                    b_copy->doMove(m, playerside);

                    move_points = b_copy->count(playerside) - b_copy->count(otherside);

                    if ((i % 7 == 0) && (j % 7 == 0)) {
                        move_points = move_points * 4;
                    }

                    else if ((i % 5 == 1) && (j % 5 == 1))
                        move_points *= -4;
                    
                    else if ((i % 5 == 1) && (j % 7 == 0))
                        move_points *= -3;

                    else if ((j % 5 == 1) && (i % 7 == 0))
                        move_points *= -3;

                    else if ((i % 7 == 0) || (j % 7 == 0))
                        move_points *= 3;


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