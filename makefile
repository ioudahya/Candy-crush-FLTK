main : controlleur player Bonbon Bonbon_bombe Bonbon_emballer Bonbon_rayerH Bonbon_rayerV Bonbon_glace Bonbon_mur Menu Acceuil Niveau game
	g++ main.cpp controlleur.o player.o Bonbon.o Bonbon_bombe.o Bonbon_emballer.o Bonbon_rayerH.o Bonbon_rayerV.o Bonbon_glace.o Bonbon_mur.o Menu.o Acceuil.o Niveau.o game.o -lfltk  -lfltk_images
	
game : game.cpp game.hpp
	g++ -c game.cpp	

controlleur : controlleur.cpp controlleur.hpp
	g++ -c controlleur.cpp

player : player.cpp player.hpp
	g++ -c player.cpp

Bonbon : Bonbon.cpp Bonbon.hpp
	g++ -c Bonbon.cpp

Bonbon_bombe : Bonbon_bombe.cpp Bonbon_bombe.hpp
	g++ -c Bonbon_bombe.cpp

Bonbon_emballer : Bonbon_emballer.cpp Bonbon_emballer.hpp
	g++ -c Bonbon_emballer.cpp

Bonbon_rayerH : Bonbon_rayerH.cpp Bonbon_rayerH.hpp
	g++ -c Bonbon_rayerH.cpp

Bonbon_rayerV : Bonbon_rayerV.cpp Bonbon_rayerV.hpp
	g++ -c Bonbon_rayerV.cpp

Bonbon_glace : Bonbon_glace.cpp Bonbon_glace.hpp
	g++ -c Bonbon_glace.cpp

Bonbon_mur : Bonbon_mur.cpp Bonbon_mur.hpp
	g++ -c Bonbon_mur.cpp

Menu : Menu.cpp Menu.hpp
	g++ -c Menu.cpp

Acceuil : Acceuil.cpp Acceuil.hpp
	g++ -c Acceuil.cpp
	
Niveau : Niveau.cpp Niveau.hpp
	g++ -c Niveau.cpp	
	
clean :
	rm controlleur.o player.o Bonbon.o Bonbon_bombe.o Bonbon_emballer.o Bonbon_rayerH.o Bonbon_rayerV.o Bonbon_glace.o Menu.o Acceuil.o  Bonbon_mur.o Niveau.o game.o a.out
