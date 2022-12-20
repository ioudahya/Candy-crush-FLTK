#include "Bonbon_rayerV.hpp"

Bonbon_rayerV::Bonbon_rayerV(int id, int x, int y, int h, int w) : Bonbon(id, x, y, h, w) {
    numBonbon = 3;
}

int Bonbon_rayerV::destroy(std::vector<std::vector<Bonbon *>> square,int i,int j){
    int result = 0;
    if(this->getID() != 8){
    	result++;
    	this->setID(8);
	    for(int k=0;k<9;k++){
	        if(k != idY) {
	            result += square[idX][k]->destroy(square,k, idX);
	        }
	    }
	    result += glacageH(square);
	}
    return result;
}
