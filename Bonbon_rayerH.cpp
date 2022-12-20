#include "Bonbon_rayerH.hpp"

Bonbon_rayerH::Bonbon_rayerH(int id, int x, int y, int h, int w) : Bonbon(id, x, y, h, w) {
    numBonbon = 2;
}

int Bonbon_rayerH::destroy(std::vector<std::vector<Bonbon *>> square,int i,int j){
    int result = 0;
	if(this->getID() != 8){
		result++;
    	this->setID(8);
	    for(int k=0;k<9;k++){
	        if(k != idX) {
	            result += square[k][idY]->destroy(square,idY, k);
	        }
	    }
	    result += glacageV(square);
    }
    return result;
}