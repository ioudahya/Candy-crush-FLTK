//
// Created by ismail on 26/12/21.
//

#include "Bonbon_bombe.hpp"

Bonbon_bombe::Bonbon_bombe(int id, int x, int y, int h, int w) : Bonbon(id, x, y, h, w) {
    numBonbon = 0;
}

int Bonbon_bombe::destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) {
    int result = 1;
    int coloration = square[j][i]->getID();
    for(int k=0;k<9;k++){
        for(int l=0;l<9;l++){
            if(square[k][l]->getID() == coloration){
                result += square[k][l]->destroy(square,k,l);
            }
        }
    }
    this->setID(8);
    return result;
}



