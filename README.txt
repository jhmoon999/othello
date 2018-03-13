Our team is Jason and Katerina. 
Jason set up the repository on his github, wrote the random player that works. 
We worked together on the heuristics regarding the score and edge positions, with
Katerina writing the initial messy code, Jason rewriting it in a smart way,
and Katerina debugging. 
We both ran test games many many times and made sure there are no bugs and that the heuristics algorithm beat SimplePlayer at least 8 out of 10 games.
Katerina wrote a messy version of minimax that is not really minimax because we
assume the opponent only asssesses the current board state. It wins on average 8 out of 10 games against ConstatntTimePlayer.

We think that our AI splendidavocados is tournament worthy. ConstantTimePlayer is right now in the middle of the leaderboard, and we beat it most of the time.
The improvements we made include assigning different values to different edge cells.
Also in some sense we assume that our opponent is ConstantTimePlayer, because instead of minimax we assume that the opponent uses the greedy way to assess the constant state of the board.
We sometimes switch between greedy and almost-minimax. For instance, when the opponent has 3 times more discs than us, we use greedy. 


