#ifndef MENU_HPP
#define MENU_HPP

#include <FL/Fl_Box.H>

#include <vector>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>

#include <FL/Fl_Window.H>

#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <functional>
#include <fstream>


template<typename T>
class Menu : public T{
private:
    std::function<void(Fl_Widget *)> bouton = nullptr;
public:
    Menu(int x,int y,int w,int h,const char *title = nullptr) : T(x,y,w,h,title){}
    /*
     * Cette méthode permet de parcourir un dossier et de faire en sorte qu'il recupère tout les fichiers
     * qu'on a dans le dossier niveau pour vérifier le nombre de niveau que l'on a
     */
    int visit_directory() {
        std::vector<char*> niv;
        DIR *dir;
        struct dirent *ent;
        if ((dir = opendir ("/home/ismail/PROJET/niveau")) != nullptr) {
            while ((ent = readdir (dir)) != nullptr) {
                if(!strcmp(ent->d_name, ".") == 0 && !strcmp(ent->d_name,"..") ==0) {
                    niv.push_back(ent->d_name);
                }
            }
            closedir (dir);
        }
        return niv.size();
    }
    /*
     * on recupère le pointeur du widget et on vérifie si il a été cliquer
     * //https://en.cppreference.com/w/cpp/language/lambda
        /   /https://fltk.easysw.narkive.com/Zo9c6C5f/lambda-function-in-how-to-use-c-1x
     */
    void getclickable(std::function<void(Fl_Widget *)> &&widget){
        bouton = widget;
        auto a=[](Fl_Widget *widg,void *data){ // lambda expression
            auto click = *static_cast<std::function<void(Fl_Widget *)>*>(data);
            click(widg);
        };
        this->callback(a,&bouton);
    }
    /*
     * cette méthode permet de remettre le score max à 0
     */
    void visit_score(){
        std::ofstream text;
        text.open("score/bestScore");
        text << "0" <<std::endl;
        text.close();
    }

};



#endif //OOPNEW_MENU_HPP
