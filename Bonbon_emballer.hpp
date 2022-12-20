#ifndef Bonbon_emballer_HPP
#define Bonbon_emballer_HPP
#include "Bonbon.hpp"

class Bonbon_emballer : public Bonbon {
private:
public:
    Bonbon_emballer(int id,int x,int y,int h,int w); // Initialise le bonbon et donne une valeur différente à numBonbon.
    int destroy(std::vector<std::vector<Bonbon *>> square,int i,int j);
	//Détruit les bonbons qui sont à une distance de une case tout en récupérant leur scores puis les renvois.

};


#endif //OOPNEW_Bonbon_emballer_HPP
