#include <map>
#include "Bonbon_emballer.hpp"

Bonbon_emballer::Bonbon_emballer(int id, int x, int y, int h, int w) : Bonbon(id, x, y, h, w) {
    numBonbon = 1;
}

/*
 * On a un mapping qui recupère l'element de la premiere boucle pour vérifier si les élements sont bon
 * On ajoute un mapping pour ne pas mettre affirmer que le mouvement est correcte
 * puisqu'on doit d'abord passer par la deuxième boucle et voir si celle ci est correcte aussi
 * puisque le mouvement requis pour avoir un bonbon emballé est en forme de T et L
 */


int Bonbon_emballer::destroy(std::vector<std::vector<Bonbon *>> square,int i,int j) {
    /*
     * position haut droite, position haut gauche, position haut, position bas, position bas gauche, position bas droite
     position gauche , position droite , position initiale
    */
    // inverser les j et i
    int result = 0;
    if(this->getID() != 8){
        result++;
        this->setID(8);
        if(j+1<=8 && i+1<=8){
            result += square[i+1][j+1]->destroy(square,i+1,j+1);
        }
        if(j<=8 && i+1<=8){
            result += square[i+1][j]->destroy(square,i+1,j);
        }
        if(j-1<=8 && i+1<=8){
            result += square[i+1][j-1]->destroy(square,i+1,j-1);
        }
        if(j+1<=8 && i<=8){
            result += square[i][j+1]->destroy(square,i,j+1);
        }
        if(j-1<=8 && i<=8){
            result += square[i][j-1]->destroy(square,i,j-1);
        }
        if(j+1<=8 && i-1<=8){
            result += square[i-1][j+1]->destroy(square,i-1,j+1);
        }
        if(j<=8 && i-1<=8){
            result += square[i-1][j]->destroy(square,i-1,j);
        }
        if(j-1<=8 && i-1<=8){
            result += square[i-1][j-1]->destroy(square,i-1,j-1);
        }
    }
    return result;
}









