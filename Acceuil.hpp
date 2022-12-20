#ifndef OOPNEW_ACCEUIL_HPP
#define OOPNEW_ACCEUIL_HPP


#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Window.H>
#include <cstdlib>
#include <unistd.h>
#include <dirent.h>

class Acceuil {
private:
    Fl_Window* win = new Fl_Window(500,500,"Ecran acceuil");
    Fl_Window* niveau = new Fl_Window(500,500,"Menu");
public:
    Acceuil();
    bool isClose(); // méthode qui renvoie un boolean pour savoir si la fenêtre est hide ou pas.
    void make_window();  // crée une fenêtre avec prénom et se met en attente de 3 secondes.
};



#endif //OOPNEW_ACCEUIL_HPP
