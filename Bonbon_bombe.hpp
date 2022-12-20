#ifndef BONBON_BOMBE_HPP
#define BONBON_BOMBE_HPP
#include "Bonbon.hpp"

class Bonbon_bombe : public Bonbon{
public:
    Bonbon_bombe(int id,int x,int y,int h,int w); // Initialise le bonbon et donne une valeur différente à numBonbon.
    int destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) override;
	//Parcourt l’entièreté du plateau et detruit les bonbons qui ont la même couleur que le bonbon se trouvant dans la case (i, j) tout en récupérant le score de la destruction de ces bonbons.

};


#endif //OOPNEW_BONBON_BOMBE_HPP
