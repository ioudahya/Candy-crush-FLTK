#include "Bonbon_mur.hpp"

Bonbon_mur::Bonbon_mur(int id, int x, int y, int h, int w) : Bonbon(id, x, y, h, w) {
    numBonbon = 0;
}


int Bonbon_mur::destroy(std::vector<std::vector<Bonbon *>> square,int i,int j){
	this->setID(10);
    return 0;
}

std::vector<int> Bonbon_mur::verif(std::vector<std::vector<Bonbon *>> square,int i,int j){
	std::vector<int> move{0,0,0,0};
	return move;
}
