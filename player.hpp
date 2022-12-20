#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Menu.hpp"
#include <string>
#include <iostream>
#include <fstream>


class player {
private:
    int score;
    int maxScore;
    Fl_Box *texteBestScore = new Fl_Box(850,100,100,40,"Best score: ");
    Fl_Box *max = new Fl_Box(880,150,50,40,"0");

    Fl_Box *count;
    Fl_Box *textScore;

public :

    player(int score);
    void init();
    void bestScore();
    void draw();
    void addScore(int s);
    void setbestScore();
    void setScore(int s);
    int getScore();


};


#endif //OOP_PLAYER_HPP
