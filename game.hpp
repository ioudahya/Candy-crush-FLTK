#ifndef GAME_HPP
#define GAME_HPP
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include "controlleur.hpp"

class game : public Fl_Window{
    controlleur control;
    int niveau;
    bool valid = false;
    int posX,posY;
    double time = 0.1;
    clock_t start,end;
public:
    /*
     * Constructeur pour lancer le jeu, on hérite de la fl_window de fltk afin de lancer le jeu avec
     * en paramètres les différents type pour une fenêtre et le niveau voulant être jouer
     *
     */
    game(int lvl) : Fl_Window(100,300,1100,850,"candy crush"),niveau(lvl){
        Fl::add_timeout(time, Timer_CB, this);
        resizable(this);
        control.setNiveau(niveau); // setter de niveau voulant être jouer
        control.loadNiveau(); // charge le niveau a partir du fichier
        control.init(); // affiche le jeu à partir des images et les places dans un vecteur * bonbon
        start = clock();

    }
    /*
     *  Permet de dessiner le jeu, avec un appel à intialise qui permet de mettre à jour
     *  les images à chaque mouvement. On fait appel à un timer ici qui permet de faire
     *  un shuffle des bonbon c'est à dire appeler une méode dans control qui permet
     *  de détecter un mouvement et de le montrer au joueur grace à une animation
     */
    void draw() override {
        Fl_Window::draw();
        control.draw();
        control.initialise();
        end = clock();


        if (!control.getshutdown()) {
            while(control.drop()){
                control.initialise();
                control.plateauverif();
                control.initialise();

            }

            double temps =( (end - start) / (double)CLOCKS_PER_SEC)*100.0;
            Bonbon *temp = control.moveLeft();
            if (temp != nullptr) {
                if (temps >= 3) {
                    try{
                        temp->startPulse();
                    }
                    catch(const std::exception&){
                        std::cout << "ACCESS DENIED" << std::endl;
                    }
                }
            } else {
                control.shuffle();
            }
        }

    }
    /*
     * Un appel à cette méthode permet grace à casting
     * de cacher la fenetre
     */
    static void callback(void * d){
        Fl_Window *instance = static_cast<Fl_Window *>(d);
        instance->hide();
    }

    /*
     * On recupère chaque position du clique de la souris et onf ait appel à la méthode
     * mouseDrag
     */
    int handle(int event) override{

        switch (event){
            case FL_PUSH:
                this->mouseDrag(Fl::event_y(),Fl::event_x());
        }

        return 0;
    }

    bool comparePoint(int x, int y, int i, int j){ // fait une simple comparaison pour voir si la souris se trouve dans le périmétre de la piéce
        i = i*90;
        j = j*90;
        return ((x >= j and y >= i) and (x <= j+94 and y <= i+93));
    };

    /*
     * Cette méthode est appelé après chaque fin de niveau, lorsqu'on perd ou gagne
     * on vide le vecteur <vectonr< bonbon*>> et on reset le nouveau niveau
     * charge le niveau et on rappel le init de nouveau pour dessiner
     */
    void resetLvl(){
        control.clearVector();
        control.setNiveau(niveau);
        control.loadNiveau();
        control.init();
    }

    /*
     * Cette méthode permet d'afficher si une fenetre lorsque le joueur perd ou gagne
     * quand il perd ou gagne la fenetre lui annoncant gagner ou perdre reste ouverte durant 3 secondes
     * ensuite elle se fait définitivement , le prochain niveau se lance directement avec la fenetre du score
     * qui reste elle toujours ouverte mais elle se réinitialise.
     */
    void isEnd(){
        int testing = control.gameOver();
        if(testing == 1){

            auto gagner = new Fl_Window(600,500,"Game-Over");
            gagner->resize(1200,500,600,500);
            gagner->show();
            gagner->begin();
            auto texte = new Menu<Fl_Box>(180,250,150,150,"WIN !!!");
            gagner->end();
            Fl::add_timeout(3.0,callback,gagner);
            this->hide();
            if (niveau < 3){ // lancer le niveau suivant si pas niveau 3
                niveau++;
                resetLvl();

            }
            else if(niveau == 3){ // si il est au niveau 3 il reste sur le niveau 3
                resetLvl();
            }
        }
        if(testing == 0){
            auto perdu = new Fl_Window(600,500,"Game-Over");
            perdu->resize(1200,500,600,500);
            perdu->show();
            perdu->begin();
            auto texte = new Menu<Fl_Box>(180,250,150,150,"LOOSE !!!");
            perdu->end();
            Fl::add_timeout(3.0,callback,perdu);
            this->hide();
            resetLvl();
        }
    };


    /*
     * Méthode qui vérifie si le clique est dans le bonbon
     * ON regarde si le mouvement est valide et on appel la méthode run
     * qui vérifie si le mouvement est faisable
     */
    void mouseDrag(int yp, int xp) {
        start = clock();
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (this->comparePoint(xp, yp, i, j)) {
                    if (not valid) {
                        posX = j;
                        posY = i;
                        valid = true;
                    }
                    else if (valid) {
                        valid = false;
                        if((i-posY <= 1 && i-posY >= -1 && j-posX == 0) || (j-posX <= 1 && j-posX >= -1 && i-posY == 0)){
                            control.run(posX, posY, j, i);
                            control.initialise();
                            //appel a une méthode qui fait le mouvement et qui regarde si c bon 1er clique : posX et posY  glisse 2e endroit : j et i
                            isEnd();
                        }
                    }
                }
            }
        }
    };

    static void Timer_CB(void *userdata){
        game *o = (game *)userdata;
        o->redraw();
        Fl::repeat_timeout(1.0/10,Timer_CB,userdata);
    }

};


#endif //GAME_HPP
