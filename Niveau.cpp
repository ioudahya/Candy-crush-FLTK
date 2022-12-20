
#include "Niveau.hpp"


Niveau::Niveau() {}

/*
 * Vérifie si il existe un glacage encore dans le partie en cours
 */
bool Niveau::isGlacage(std::vector<std::vector<Bonbon *>> square) {
    for(int i=0;i<=8;i++){
        for(int j=0;j<=8;j++){
            if(square[i][j]->getID() == 11 || square[i][j]->getID() == 12){
                return false;
            }
        }
    }
    return true;
}

/*
 * Initialise les type de niveau et les objectifs
 */
void Niveau::init() {
    auto label = atoi(max->label());
    if(nbNiveau == 1 ){
        label = maxMove1;
        scorencours = maxScore1;
        target->copy_label(quest1);
    }
    else if(nbNiveau ==2 ){
        label = maxMove2;
        scorencours = maxScore2;
        target->copy_label(quest2);
    }
    else if(nbNiveau ==3 ){
        label = maxMove3;
        scorencours = maxScore3;
        target->copy_label(quest3);
    }
    char buf[12];
    snprintf(buf,12,"%d",label);
    max->copy_label(buf);
}

/*
 * Retourne le score en cours en tant que integer
 */
int Niveau::getScore() const{
    return scorencours;
}

/*
/*
 * Méthode draw() permettant de dessiner les mouvements faisables
 * et sont décrémenter de 1 à chaque fois que le joueur fait un mouvement
 */
int Niveau::draw() {
    auto label = atoi(max->label());
    label--;
    int check = getCount(label);
    char buf[12];
    snprintf(buf,12,"%d",label);
    max->copy_label(buf);
    return check;
}

/*
 * getter pour recupèrer les mouvements faisables.
 */
int Niveau::getCount(int lab) {
    return lab;
}
/*
 * setter permettant de poser un certain niveau.
 */
void Niveau::setNiveau(int nb) {
    nbNiveau = nb;
}






