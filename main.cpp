#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "Menu.hpp"
#include "Acceuil.hpp"
#include "game.hpp"
int main(int argc,char *argv[]){
    Acceuil acceuil;
    acceuil.make_window();

    if((acceuil.isClose()) == true){
        return Fl::run();
    }
    while(!acceuil.isClose()) Fl::wait(2);
    int WIDTH = 600;
    int HEIGHT = 400;
    //succession de fenêtre crée pour le menu
    auto window = new Fl_Window(WIDTH,HEIGHT,"MENU ");
    auto txt = new Menu<Fl_Box>(180,250,100,40,"NIVEAU : ");
    auto count = new Menu<Fl_Box>(txt->x(),txt->y()+40,100,40,"1");
    auto NEXT = new Menu<Fl_Button>(WIDTH-100,HEIGHT-100,60,60,"NEXT");
    auto PREVIOUS = new Menu<Fl_Button>(WIDTH-170,HEIGHT-100,60,60,"PREVIOUS");
    auto launch = new Menu<Fl_Button>(WIDTH-100,HEIGHT-200,60,60,"JOUER");
    auto quit = new Menu<Fl_Button>(WIDTH-100,HEIGHT-300,60,60,"QUITTER");
    auto setScore = new Menu<Fl_Button>(WIDTH-100,HEIGHT-400,60,60,"RESET MAX SCORE");

    window->end();
    window->show();
    //NEXT->visit_directory();
    int maxl =  3;
    setScore->getclickable([=](Fl_Widget *b){
        setScore->visit_score();
    });
    /*
     * Permet d'afficher le prochain niveau quand on clique sur NEXT
     */
    NEXT->getclickable([=](Fl_Widget * b){
        auto label = atoi(count->label());
        if(label < maxl)
            label++;
        char buf[12];
        snprintf(buf,12,"%d",label);
        count->copy_label(buf);
    });

    /*
     * Permet d'afficher le niveau précédent quand on clique sur PREVIOUS
     */
    PREVIOUS->getclickable([=](Fl_Widget * b){
        auto label = atoi(count->label());
        if(label > 1)
            label--;
        char buf[12];
        snprintf(buf,12,"%d",label);
        count->copy_label(buf);
    });

    /*
     * Quand on clique sur QUIT on quitte complètement le jeu
     */
    quit->getclickable([=](Fl_Widget *){
        exit(0);
    });


    /*
     * Quand on clique sur LAUNCH le jeu se lance et fait appel au constructeur de la classe game
     */
    launch->getclickable([=](Fl_Widget *){
        auto label = atoi(count->label());
        game window(label);
        window.show(argc, argv);
        return Fl::run();
    });

    return Fl::run();
}
