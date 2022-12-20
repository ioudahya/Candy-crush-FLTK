//
// Created by ismail on 27/12/21.
//

#include "Bonbon_glace.hpp"

Bonbon_glace::Bonbon_glace(int id, int x, int y, int h, int w) : Bonbon(id, x, y, h, w) {
    numBonbon = 4;
    if(id == 12) life++;
}

std::vector<int> Bonbon_glace::verif(std::vector<std::vector<Bonbon *>> square,int i,int j){
	std::vector<int> move{0,0,0,0};
	return move;
}

int Bonbon_glace::destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) {
    int result = 0;
    this->life--;//retire un point de vie
    if(this->life < 1){//si il à encore un point de vie
        result = 1;
    	this->setID(8);
    }
    else{
    	this->id--;//si il à pris des dégats mais n'est pas détruit alors il passe en glaçages fragilisé
    }
    return result;
}



