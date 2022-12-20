#ifndef BONBON_HPP
#define BONBON_HPP

#include <iostream>
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <FL/Fl_PNG_Image.H>
#include <unistd.h>
#include <vector>


class Bonbon {
private:
    int h,w;
    Fl_PNG_Image *image;


protected:
    int idX;
    int idY;
    int numBonbon;
    int x,y;
    int id;
    bool pulse = false;
    bool animation = false;
    int xprime,yprime;
    std::vector<int> idX1{1, -1, 1,-1};
    std::vector<int> idX2{2, -2, -1,1};
public:

    Bonbon(int id,int x,int y,int h,int w); // initialise le bonbon

    virtual ~Bonbon() = default;

    virtual void setFontImage(Fl_PNG_Image* newImage); // change l'image du bonbon

    virtual void draw(); // dessine le bonbon et peux activer une animation

    virtual int getID(); // Récupére l’identifiant du bonbon.

    virtual int getNumBonbon(); // Récupére le numero du bonbon qui représente son type(avec l’id).

    virtual void setNumBonbon(int a); // Donne un nouveau numéro au bonbon.

    virtual void setID(int number); // Donne un nouvel identifiant au bonbon.

    virtual std::vector<int>  verif(std::vector<std::vector<Bonbon*>> square,int i,int j);
	// Cette méthode récupère le nombre de bonbons de même couleur qui se trouvent à gauche, droite, au-dessus et en dessous du bonbon actuel et renvoi un vecteur de taille 4 avec le nombre de bonbons trouvés (chaque élément du vecteur correspond à une direction).

    virtual int destroy(std::vector<std::vector<Bonbon *>> square,int i,int j);
	//Remplace l’id du bonbon par 8 qui représente une case vide puis lance glacageV et glacageH et finalement renvoi 1, la valeur renvoyé représente le score que rapporte la destruction de ce bonbon.

    virtual int glacageV(std::vector<std::vector<Bonbon *>> square);
	// Vérifie si il y a des glaçages au-dessus et en dessous du bonbon actuel et les détruits.

    virtual int glacageH(std::vector<std::vector<Bonbon *>> square);
	// Vérifie si il y a des glaçages à gauche et à droite du bonbon actuel et les détruits.

    virtual void pulsage();
	// Fait bouger légèrement le bonbon en changeant ça position.

    virtual void startPulse();
	// Met l’attribut pulse à true ce qui permet de déclencher le pulsage() quand le bonbon est dessiné.


};


#endif //OOPNEW_BONBON_HPP
