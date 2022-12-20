#ifndef NIVEAU_HPP
#define NIVEAU_HPP
#include "Bonbon.hpp"
class Niveau {
private :
    int nbNiveau;
    int maxMove1 = 3;
    int maxScore1 = 10;
    int maxMove2 = 20;
    int maxScore2 = 50;
    int maxMove3 = 20;
    int maxScore3 = 70;
    int scorencours;
    const char* quest1 = "Avoir plus de 10 points";
    const char* quest2 = "Détruire tout les glacages";
    const char* quest3 = "Détruire tout les glacages et avoir plus de 75 points";

    Fl_Box *move = new Fl_Box(880,200,100,40,"Maximum mouvement possible: ");
    Fl_Box *max = new Fl_Box(880,250,50,40,"0");
    Fl_Box *target=new Fl_Box(900,300,100,40,"fill here");


public:
    Niveau();
    void setNiveau(int nb);
    int getScore() const;
    void init();
    int draw();
    bool isGlacage(std::vector<std::vector<Bonbon *>> square);
    int getCount(int lab);
};


#endif //OOPNEW_NIVEAU_HPP
