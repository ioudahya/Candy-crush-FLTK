//
// Created by ismail on 27/12/21.
//

#ifndef BONBON_MUR_HPP
#define BONBON_MUR_HPP
#include "Bonbon.hpp"

class Bonbon_mur : public Bonbon{
public:
    Bonbon_mur(int id,int x,int y,int h,int w); // Initialise le mur.
    int destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) override;
	//Ne fait rien car les murs ne sont pas destructibles et donc renvoi 0 car il ne donne pas de points.
    std::vector<int> verif(std::vector<std::vector<Bonbon *>> square,int i,int j) override;
	// Renvoi simplement un vecteur de taille 4 contenant des 0, pour représenter qu’aucun mouvement n’as été trouvé.
};


#endif //OOPNEW_BONBON_RAYERV_HPP
