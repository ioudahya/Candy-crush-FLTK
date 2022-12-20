
#ifndef BONBON_RAYERV_HPP
#define BONBON_RAYERV_HPP
#include "Bonbon.hpp"

class Bonbon_rayerV : public Bonbon{
public:
    Bonbon_rayerV(int id,int x,int y,int h,int w); // Initialise le bonbon , donne une valeur différente à numBonbon.
    int destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) override;
	//Détruit tous les bonbons se trouvant sur la même colonne que le bonbon actuel, nous lançons glacageH() pour vérifier si il  y a des glaçages, puis on renvoi le score de tous les bonbons détruits.
};


#endif //OOPNEW_BONBON_RAYERV_HPP
