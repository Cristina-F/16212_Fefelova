#include "GameTournament.h"

GameTournament:: GameTournament ( const Dealer &  dealer,  const std:: vector<Player*> players): dealer_(dealer), players_(players) {
    size_ = players.size();
    count_win_ = new int[size_];
    std::fill(count_win_, (count_win_ + size_), 0 );
}

GameTournament:: ~GameTournament() {
    delete [] count_win_;
}

Player * GameTournament:: findWinnerOfTournament() {
    int idx = 0;
    for ( int i = 1; i < size_; i++ ) {
        if ( count_win_[i] > count_win_[idx] ) {
           idx = i;
        }
    }
    return players_[idx];
}

Player * GameTournament:: game() {
    std::cout<<" TOURNAMENT "<<std::endl;
    for ( int i = 0; i < size_ - 1; i++ ) {
        for ( int j = 1; j < size_; j++ ) {
            if ( i != j ) {
                std::vector < Player* > tmpPlayers = { players_[i], players_[j] };
                tmpPlayers[0] -> clear();
                tmpPlayers[1] -> clear();
                GameFast game( dealer_, tmpPlayers );
                Player * winner = game.game();
                if ( winner ) {
                    if ( tmpPlayers[0] == winner ) {
                        (count_win_[i])++;
                    }
                    else{
                       (count_win_[j])++;
                    }
                }
            }
        }
    }
    return findWinnerOfTournament();
}