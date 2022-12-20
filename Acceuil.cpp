//
// Created by ismail on 4/01/22.
//

#include "Acceuil.hpp"

Acceuil::Acceuil() {
}

static void callback(void * d){
    Fl_Window *instance = static_cast<Fl_Window *>(d);
    instance->hide();
}


void Acceuil::make_window() {
    win->begin();
    Fl_Box *box = new Fl_Box(80,180,350,150,"Ismail / Naoufal");
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD+FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);

    win->end();
    win->show();
    Fl::add_timeout(1.0,callback,win);
}

bool Acceuil::isClose() {
    if(win->shown() == 0)
        return true;
    return false;
}
