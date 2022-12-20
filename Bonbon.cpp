//
// Created by ismail on 26/12/21.
//

#include "Bonbon.hpp"

#include <utility>


Bonbon::Bonbon(int id, int x, int y, int h, int w)
        :id(id),x(x),y(y),h(h),w(w){
    idX = x/90;
    idY = y/90;
    xprime = x;
    yprime = y;
    numBonbon =  0;

}

int Bonbon::getID(){
    return this->id;
}

void Bonbon::draw(){
    if(pulse)
        pulsage();
    else
        image->draw(x,y,w,h);
}

void Bonbon::setID(int number){
    this->id = number;
}

void Bonbon::setFontImage(Fl_PNG_Image* newImage){
    image = newImage;
}

void Bonbon::pulsage(){
    if(animation){//si l'animation es activé on bouge dans l'autre sense
        animation = false;
        xprime -= 5;
        yprime -= 5;
        pulse = false;
    }
    else{//si l'animation est désactivé on bouge dans un sens
        animation = true;
        xprime += 5;
        yprime += 5;
    }
    image->draw(xprime,yprime,w,h);//on dessine l'le bonbon avec les coordonés provisoires afin de ne pas fausser le mouvement du joueur
}

void Bonbon::startPulse(){
    pulse = true;
}

std::vector<int> Bonbon::verif(std::vector<std::vector<Bonbon *>> square,int i,int j) {
    // left 0 , right 1 , up 2 , down 3
    std::vector<int> move{0,0,0,0};
    int forward = 1;
    int backward = -1;

    bool done1 = true;
    bool done2 = true;
    bool doneup = true;
    bool donedown = true;
    bool doneleft = true;
    bool doneright = true;

    while((done1 or done2)){//tant que la direction verticale et horizontale n'ont pas été finies d'être explorés
        if(((i+forward) <= 8 or (j+forward) <= 8)  and done1){
            if((j+forward) <= 8){
                if(square[i][j+forward]->getID() == square[i][j]->getID() && donedown){//si il rencontre un bonbon similaire en avançant verticalement (bas)
                    move[3]+=1;
                }
            }
            if((i+forward) <= 8){
                if(square[i+forward][j]->getID() == square[i][j]->getID() && doneright){//si il rencontre un bonbon similaire en avançant horizontalement (droite)
                    move[1]+=1;
                }
            }

            if((i+forward) <= 8) {
                if (square[i + forward][j]->getID() != square[i][j]->getID()) {
                    doneright = false;
                }
            }
            if((j+forward) <= 8) {
                if (square[i][j + forward]->getID() != square[i][j]->getID()) {
                    donedown = false;
                }
            }


            forward++;
        }
        else{
            done1 = false;
        }
        if(((i+backward) >=0  or (j+backward) >=0) and done2){
            if((j+backward) >=  0){
                if(square[i][j+backward]->getID() == square[i][j]->getID() && doneup){//si il rencontre un bonbon similaire en avançant verticalement (haut)
                    move[2]+=1;
                }
            }
            if((i+backward) >= 0){
                if(square[i+backward][j]->getID() == square[i][j]->getID() && doneleft){//si il rencontre un bonbon similaire en avançant horizontalement (gauche)
                    move[0]+=1;
                }
            }
            if((i+backward) >= 0) {
                if (square[i+backward][j]->getID() != square[i][j]->getID()) {
                    doneleft = false;
                }
            }
            if((j+backward) >= 0) {
                if (square[i][j+backward]->getID() != square[i][j]->getID()) {
                    doneup = false;
                }
            }
            backward-=1;
        }
        else{
            done2 = false;
        }
    }

    return move;
}

int Bonbon::glacageV(std::vector<std::vector<Bonbon *>> square){
    int res = 0;
    if(idY > 0){
        if(square[idX][idY-1]->getID() > 10){
            res += square[idX][idY-1]->destroy(square,-1,-1);
        }
    }
    if(idY < 8){
        if(square[idX][idY+1]->getID() > 10){
            res += square[idX][idY+1]->destroy(square,-1,-1);
        }
    }
    return res;
}

int Bonbon::glacageH(std::vector<std::vector<Bonbon *>> square){
    int res = 0;
    if(idX > 0){
        if(square[idX-1][idY]->getID() > 10){
            res += square[idX-1][idY]->destroy(square,-1,-1);
        }
    }
    if(idX < 8){
        if(square[idX+1][idY]->getID() > 10){
            res += square[idX+1][idY]->destroy(square,-1,-1);
        }
    }
    return res;
}

int Bonbon::destroy(std::vector<std::vector<Bonbon *>> square,int i, int j) {
    //square[j][i]->setID(8); // met l'image blanche
    int res = 1;
    this->setID(8);
    res += glacageV(square);
    res += glacageH(square);
    return res;
}

int Bonbon::getNumBonbon() {
    return numBonbon;
}

void Bonbon::setNumBonbon(int a) {
    numBonbon = a;
}





