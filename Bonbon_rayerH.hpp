#include "Bonbon.hpp"
#ifndef BONBON_RAYERH_HPP
#define BONBON_RAYER_HPP


class Bonbon_rayerH : public Bonbon{
public:
    Bonbon_rayerH(int id,int x,int y,int h,int w); // Initialise le bonbon , donne une valeur différente à numBonbon.
    int destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) override;
	//Détruit tous les bonbons se trouvant sur la même ligne que le bonbon actuel, nous lançons glacageV() pour vérifier si il  y a des glaçages, puis on renvoi le score de tous les bonbons détruits.
};


#endif //OOPNEW_BONBON_RAYERH_HPP
