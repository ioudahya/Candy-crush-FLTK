#ifndef CONTROLLEUR_HPP
#define CONTROLLEUR_HPP
#include<map>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Bonbon_bombe.hpp"
#include "Bonbon_emballer.hpp"
#include "Bonbon_rayerH.hpp"
#include "Bonbon_rayerV.hpp"
#include "Bonbon_mur.hpp"
#include "Bonbon_glace.hpp"
#include "player.hpp"
#include "Niveau.hpp"

class controlleur {
private :
    std::vector<std::vector<Bonbon*>> square;
    std::vector <std::vector<int>>num;

    player *joueur = new player(0);
    Niveau *niveau = new Niveau();
    int posX = -1;
    int posY = -1;
    int valid = 1;
    bool ok = false;
    int level;
    bool shutdown= false;
public:
    controlleur(); // Nous lançons le init() pour le joueur.
    bool possible(int oldX,int oldY,int newX,int newY); // Vérifie si un mouvement est possible.
    Bonbon* moveLeft();  // Parcourt l’entièreté du plateau et vérifie les mouvements possibles pour chaque bonbon et renvois un pointeur du premier bonbon avec lequel un mouvement  est possible, si aucun mouvement est possible alors un nullptr est renvoyé.
    void shuffle(); // Change la couleur de tous les bonbons normaux se trouvant sur le plateau.
    bool getshutdown(); // Renvoie un bool lorsque le joueur a perdu ou gagner. Permettra de savoir si il faut relancer le même niveau ou le niveau prochain.
    int gameOver(); // renvoie un entier qui permet de savoir si le joueur à gagner ou perdu tout en rajoutant le score max du joueur c’est ici qu’on vérifie si les objectifs ont été réussi. 
    void clearVector(); //Efface l’entièreté du plateau.
    void loadNiveau(); //  Transforme le plateau se trouvant dans un fichier texte en une matrice d’entiers représentant les id.
    void init(); //Crée le plateau à partir de la matrice d’entiers puis leur assigne une image et ensuite enlève du plateau les combinaisons de bonbons déjà faites.
    void setNiveau(int nv); //Crée le plateau à partir de la matrice d’entiers puis leur assigne une image et ensuite enlève du plateau les combinaisons de bonbons déjà faites.
    void draw(); // Dessine tous les bonbons sur le plateau en appelant la méthode draw() du bonbon.
    bool solve(int left,int right,int up,int down,int idX,int idY);
    void run(int oldX,int oldY,int newX,int newY); // Decide quel genre de combinaison doit être faite, détruit les bonbons concernés puis fait apparaitre le bonus de la combinaison si il y en a et finalement renvoi true ou false selon que la méthode ait détruit des bonbons ou pas.
    void initialise(); // Met à jour les images des bonbons du plateau.
    void swap(int oldX,int oldY,int newX,int newY); // Echange les positions de deux bonbons il y a deux case différents quand les bonbons sont de même type ou quand ils sont d’un type différent.
    void change(int x, int y, int num, int color); // Méthode appelé quand il faut changer un bonbon vers un autre bonbon de type différent.
    bool drop(); // Cette méthode parcourt l’entièreté du plateau et fait tomber des bonbon ou crée un nouveau bonbon quand elle rencontre un case vide càd id = 8.
    void plateauverif(); // Méthode qui parcourt l’entièreté du plateau et qui detruit les combinaison de bonbons que le joueur n’as pas causé diréctement. 
    void bestchoice(std::vector<int> moves,int a,int b); // Méthode qui récupère un vecteur de taille 4 en param et le bonbon à partir du quel ce vecteur appartient, la méthode va parcourir tous les bonbon faisant partie de la combinaison ce trouvant dans le vecteur et va détruire le bonbon faisant partie de la combinaison pour lequel il existe une autre combinaison qui rapporte plus de points. 
    int vectsum(std::vector<int> moves); // Méthode qui renvoi le nombre de bonbons faisant partie de la combinaison, si il y a pas assez de bonbons pour faire une combinaison la méthode renvoi 0.
    std::vector<int> getupper(int i, int j); // Méthode qui parcours le plateau vers le haut à partir de la position (i,j) et qui renvoi un vecteur de taille 2 contenant les coordonnés du bonbon à faire tomber.
    void cleanAll(); // Détruit tous les bonbons du plateau et les remplace par un bonbon normal.
    void changeToStrip(int color); //  Change tous les bonbons de la même couleur que le bonbon à la position (i,j) en des bonbons rayés, la direction des rayures se fait dans l’ordre(si la précédente est horizontale alors la suivante est verticale et vice versa).
    void doubleStrip(int i, int j); // Détruit des bonbons formant une croix
    void triStrip(int i, int j); // Détruit les bonbons dans une forme de croix sur 3 rangés et 3 colonnes avec la position (i,j) comme centre.

    Fl_PNG_Image *image1 = new Fl_PNG_Image("image/tile000.png");
    Fl_PNG_Image *image2 = new Fl_PNG_Image("image/tile001.png");
    Fl_PNG_Image *image3 = new Fl_PNG_Image("image/tile002.png");
    Fl_PNG_Image *image4 = new Fl_PNG_Image("image/tile003.png");
    Fl_PNG_Image *image5 = new Fl_PNG_Image("image/tile004.png");
    Fl_PNG_Image *image6 = new Fl_PNG_Image("image/tile005.png");
    Fl_PNG_Image *image0 = new Fl_PNG_Image("image/blanc.jpg");
    Fl_PNG_Image * image7 = new Fl_PNG_Image("image/emballer000.png");
    Fl_PNG_Image * image8 = new Fl_PNG_Image("image/emballer001.png");
    Fl_PNG_Image * image9 = new Fl_PNG_Image("image/emballer002.png");
    Fl_PNG_Image * image10 = new Fl_PNG_Image("image/emballer003.png");
    Fl_PNG_Image * image11 = new Fl_PNG_Image("image/emballer004.png");
    Fl_PNG_Image * image12 = new Fl_PNG_Image("image/emballer005.png");
    Fl_PNG_Image * image13 = new Fl_PNG_Image("image/bonusCouleur.png");

    Fl_PNG_Image *image14 = new Fl_PNG_Image("image/rayer000.png");
    Fl_PNG_Image *image15 = new Fl_PNG_Image("image/rayer001.png");
    Fl_PNG_Image *image16 = new Fl_PNG_Image("image/rayer002.png");
    Fl_PNG_Image *image17 = new Fl_PNG_Image("image/rayer003.png");
    Fl_PNG_Image *image18 = new Fl_PNG_Image("image/rayer004.png");
    Fl_PNG_Image *image19 = new Fl_PNG_Image("image/rayer005.png");

    Fl_PNG_Image *image20 = new Fl_PNG_Image("image/tile021.png");
    Fl_PNG_Image *image21 = new Fl_PNG_Image("image/tile022.png");
    Fl_PNG_Image *image22 = new Fl_PNG_Image("image/tile023.png");
    Fl_PNG_Image *image23 = new Fl_PNG_Image("image/tile024.png");
    Fl_PNG_Image *image24 = new Fl_PNG_Image("image/tile025.png");
    Fl_PNG_Image *image25 = new Fl_PNG_Image("image/tile026.png");
    Fl_PNG_Image *image26 = new Fl_PNG_Image("image/mur.png");
    Fl_PNG_Image *image27 = new Fl_PNG_Image("image/glacage1.png");
    Fl_PNG_Image *image28 = new Fl_PNG_Image("image/glacage2.png");


    // 11 c'est bonbon bombe numBonbon = 4
    // 10 double glacage numBbonbon = 5
    // 9 simple glacage

    std::map<int,Fl_PNG_Image*> map1 {{1,image1},{2,image2},{3,image3},{4,image4},{5,image5},{6,image6},{8,image0},{9,image13},{10,image26}};// bonbon normaux
    std::map<int,Fl_PNG_Image*> map2 {{1,image7},{2,image8},{3,image9},{4,image10},{5,image11},{6,image12},{8,image0}}; // bonbon emballer
    std::map<int,Fl_PNG_Image*> map3 {{1,image14},{2,image15},{3,image16},{4,image17},{5,image18},{6,image19},{8,image0}}; // bonbon rayerH
    std::map<int,Fl_PNG_Image*> map4 {{1,image20},{2,image21},{3,image22},{4,image23},{5,image24},{6,image25},{8,image0}}; // bonbon rayerV
    std::map<int,Fl_PNG_Image*> map5 {{11,image27},{12,image28},{8,image0}};

};


#endif //CONTROLLEUR_HPP
