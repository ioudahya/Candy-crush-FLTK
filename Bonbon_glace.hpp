
#ifndef GLACE_HPP
#define GLACE_HPP
#include "Bonbon.hpp"

class Bonbon_glace : public Bonbon{
private:
	int life = 1;
public:
    Bonbon_glace(int id,int x,int y,int h,int w); // Initialise le bonbon , donne une valeur différente à numBonbon et lui rajoute des points de vie dépendant de son id.
    int destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) override;
	//Retire un point de vie au glaçage et si celui-ci atteint 0 points de vie alors il est détruit et le score de 1 point est renvoyé.
    std::vector<int> verif(std::vector<std::vector<Bonbon *>> square,int i,int j) override;
	// Renvoi simplement un vecteur de taille 4 contenant des 0, pour représenter qu’aucun mouvement n’as été trouvé.

};


#endif //OOPNEW_BONBON_GLACE_HPP
