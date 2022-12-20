#include "player.hpp"

player::player(int score) : score(score){

}

/*
 * Rajoute au socre du joueur un entier s généralement c'est 1 points par bonbon
 */
void player::addScore(int s) {
    this->score += s;
}

/*
 * Recupère le score du joueur
 */
int player::getScore() {
    return this->score;
}

/*
 * Setter du score du joueur
 */
void player::setScore(int s){
    this->score = s;
}

/*
 * On affiche le score du joueur a chaque mouvement
 */
void player::draw() {
    auto label = atoi(count->label());
    label = score;
    char buf[12];
    snprintf(buf,12,"%d",label);
    count->copy_label(buf);
}

/*
 * On ouvre dans le dossier le meilleur score qui a déjà été fait
 * durant la partie du joueur et on l'affiche avec une suite
 * de changement de type
 */
void player::bestScore() {
    std::ifstream inFile("score/bestScore");
    std::string myText;

    while(getline(inFile,myText)){
        maxScore = std::stoi(myText);
    }
    auto label = atoi(max->label());
    label = maxScore;
    char buf[12];
    snprintf(buf,12,"%d",label);
    max->copy_label(buf);

}
/*
 * On modifie dans le fichier bestScore le meilleur score que le
 * joueur a pu faire durant la partie.
 */
void player::setbestScore(){
    std::ofstream myText;
    myText.open("score/bestScore");
    char buf[12];
    snprintf(buf,12,"%d",score);
    if(maxScore < score){
        myText << score <<std::endl;
    }
    myText.close();
}

/*
 * Affiche la fenêtre score joueur avec le score à l'intérieur et initialiser
 * a 0.
 */
void player::init() {
    auto scoring = new Fl_Window(150,150,"Score joueur");
    scoring->resize(100,0,150,150);
    scoring->show();
    scoring->begin();
    count = new Fl_Box(50,50,50,50,"0");
    textScore = new Fl_Box(50,70,50,50,"Score: ");
    scoring->end();
}
