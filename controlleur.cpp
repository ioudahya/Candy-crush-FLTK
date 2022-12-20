#include "controlleur.hpp"

controlleur::controlleur() {
    joueur->init();
}

void controlleur::initialise(){
    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){

            if(square[y][x]->getNumBonbon() == 0 ) {
                auto item = map1.find(square[y][x]->getID());
                square[y][x]->setFontImage(item->second);
            }
            if(square[y][x]->getNumBonbon() == 1 ) {
                auto item = map2.find(square[y][x]->getID());
                square[y][x]->setFontImage(item->second);
            }
            if(square[y][x]->getNumBonbon() == 2){
                auto item = map3.find(square[y][x]->getID());
                square[y][x]->setFontImage(item->second);
            }
            if(square[y][x]->getNumBonbon() == 3){
                auto item = map4.find(square[y][x]->getID());
                square[y][x]->setFontImage(item->second);
            }
            if(square[y][x]->getNumBonbon() == 4){
                auto item = map5.find(square[y][x]->getID());
                square[y][x]->setFontImage(item->second);
            }
        }
    }
    joueur->draw();
}


void controlleur::cleanAll(){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(square[j][i]->getNumBonbon()!=0){//on supprime tous les bonbons bonus et on les change en bonbons normaux alléatoirs
                delete square[j][i];
                square[j][i] = new Bonbon((std::rand()%6)+1,90*j,90*i,94,93);
            }
            else{//on change alléatoirement la couleur des bonbos normaux
                square[j][i]->setID((std::rand()%6)+1);
            }
        }
    }
}

void controlleur::changeToStrip(int color){
    bool direction = true;
    for (int i = 0; i < 9; i++) {//on parcourt le plateau
        for (int j = 0; j < 9; j++) {

            if(square[j][i]->getID() == color){

                if(direction) this->change(j, i, 2, color);//on verifie direction pour changer la direction des rayures
                else this->change(j, i, 3, color);
            }
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if(square[j][i]->getID() == color and square[j][i]->getNumBonbon() != 0){
                joueur->addScore(square[j][i]->destroy(square,i,j));

            }
        }
    }
}

void controlleur::doubleStrip(int i, int j){
    for (int k = 0; k < 9; k++) {
        if(square[k][i]->getID() != 10)	joueur->addScore(square[k][i]->destroy(square,i,k));
        if(square[j][k]->getID() != 10)	joueur->addScore(square[j][k]->destroy(square,k,j));
    }
}

void controlleur::triStrip(int i, int j){
    for (int k = 0; k < 9; k++) {
        if(square[k][i]->getID() != 10)	joueur->addScore(square[k][i]->destroy(square,i,k));
        if(square[j][k]->getID() != 10)	joueur->addScore(square[j][k]->destroy(square,k,j));

        if(i+1 <= 8){
            if(square[k][i+1]->getID() != 10) joueur->addScore(square[k][i+1]->destroy(square,i+1,k));
        }
        if(k+1 <= 8){
            if(square[j+1][k]->getID() != 10) joueur->addScore(square[j+1][k]->destroy(square,k,j+1));
        }

        if(i-1 >= 0){
            if(square[k][i-1]->getID() != 10) joueur->addScore(square[k][i-1]->destroy(square,i-1,k));
        }
        if(k-1 >= 0){
            if(square[j-1][k]->getID() != 10) joueur->addScore(square[j-1][k]->destroy(square,k,j-1));
        }
    }
}

void controlleur::run(int oldX,int oldY,int newX,int newY) {//voir la methode possible() pour des détails sur les conditions
    swap(oldX,oldY,newX,newY);
    int colornew = square[newX][newY]->getID();
    int colorold = square[oldX][oldY]->getID();
    int numnew = square[newX][newY]->getNumBonbon();
    int numold = square[oldX][oldY]->getNumBonbon();
    if(colorold == 9 && colornew == 9){
        cleanAll();
    }
    else if(colorold == 9 || colornew == 9){//ici on gére le cas où un des bonbons est un chocolat
        if(numnew == 2 || numnew == 3) changeToStrip(colornew);
        else if(numold == 2 || numold == 3) changeToStrip(colorold);
        else if(numnew == 0 && colornew <= 6) joueur->addScore(square[oldX][oldY]->destroy(square,newY,newX));
        else if(numold == 0 && colorold <= 6) joueur->addScore(square[newX][newY]->destroy(square,oldY,oldX));

    }
    else if((numnew == 2 || numnew == 3) && (numold == 2 || numold == 3)){
        square[newX][newY]->setID(8);
        square[oldX][oldY]->setID(8);
        this->doubleStrip(oldY, oldX);
    }
    else if(((numnew == 2 || numnew == 3) || (numold == 2 || numold == 3)) && (numnew == 1 || numold == 1)){
        square[newX][newY]->setID(8);
        square[oldX][oldY]->setID(8);
        this->triStrip(oldY, oldX);
    }

    else if(colornew <= 6 and colorold <= 6){
        std::vector<int> y1 = square[newX][newY]->verif(square,newX,newY);
        std::vector<int> y2 = square[oldX][oldY]->verif(square,oldX,oldY);
        //left 0 , right 1 , up 2 , down 3

        bool solve1 = solve(y1[0],y1[1],y1[2],y1[3],newX,newY);
        bool solve2 = solve(y2[0],y2[1],y2[2],y2[3],oldX,oldY);

        //bool solve2 = solve(y1[0],y1[1],y1[2],y1[3],oldY,oldX);
        if(!(solve1 || solve2)){
            swap(oldX,oldY,newX,newY); // si le mouvement est pas bon , swap
        };
    }
    else{
        swap(oldX,oldY,newX,newY); // si le mouvement est pas bon , swap
    }
}

bool controlleur::solve(int left,int right,int up,int down,int idX,int idY){
    bool bombe = false;
    bool emballage = false;
    bool rayerV = false;
    bool rayerH = false;
    bool result = false;
    int color = square[idX][idY]->getID();
    if( ((left+right) >= 4) or ((up+down) >= 4) ){
        //Faire apparaitre le bonus(chocolat) sur square[idY][idX]
        //Supprimer le reste des bonbons
        bombe = true;
    }
    else if((left+right) == 3){
        //Faire apparaitre le bonus rayé vérticalement sur square[idY][idX]
        //Supprimer le reste des bonbons
        rayerV = true;
    }
    else if((up+down) == 3){
        //Faire apparaitre le bonus rayé horizontalement sur square[idY][idX]
        //Supprimer le reste des bonbons
        rayerH = true;
    }
    else if((left+right) >= 2 and (up+down) >= 2){
        //Faire apparaitre le bonbon dans l'embalage sur square[idY][idX]
        //Supprimer le reste des bonbons
        emballage = true;
    }
    if((left + right) >= 2){//on détruit les bonbons horizontaux et on récupére le score
        for(int l=1;l<=left;l++){
            joueur->addScore(square[idX-l][idY]->destroy(square,idY,idX-l));
        }
        for(int k=1;k<=right;k++){//on détruit les bonbon verticaux et on récupére le score
            joueur->addScore(square[idX+k][idY]->destroy(square,idY,idX+k));
        }
        joueur->addScore(square[idX][idY]->destroy(square,idY,idX));
        result = true;
        //Supprimer les bonbons
    }

    if((up+down) >= 2){
        for(int l=1;l<=up;l++){
            joueur->addScore(square[idX][idY-l]->destroy(square,idY-l,idX));
        }
        for(int k=1;k<=down;k++){
            joueur->addScore(square[idX][idY+k]->destroy(square,idY+k,idX));
        }
        result = true;
        joueur->addScore(square[idX][idY]->destroy(square,idY,idX));
        //Supprimer les bonbons
    }
    //si un bonus à été crée on supprime le bonbon et on le remplace par un bonus
    if(bombe){
        delete square[idX][idY];
        square[idX][idY] = new Bonbon_bombe(9,90*idX,90*idY,94,93);
        square[idX][idY]->setNumBonbon(0);
    }
    else if(emballage){
        delete square[idX][idY];
        square[idX][idY] = new Bonbon_emballer(color,90*idX,90*idY,94,93);
        square[idX][idY]->setNumBonbon(1);
    }
    else if(rayerV){
        delete square[idX][idY];
        square[idX][idY] = new Bonbon_rayerV(color,90*idX,90*idY,94,93);
        square[idX][idY]->setNumBonbon(3);
    }
    else if(rayerH){
        delete square[idX][idY];
        square[idX][idY] = new Bonbon_rayerH(color,90*idX,90*idY,94,93);
        square[idX][idY]->setNumBonbon(2);
    }

    return result;
}


void controlleur::draw() {
    for (auto &v: square) {
        for (auto &c: v) {
            joueur->draw();
            c->draw();
        }
    }
}

void controlleur::swap(int oldX, int oldY, int newX, int newY) {

    int colorold = square[oldX][oldY]->getID();
    int colornew = square[newX][newY]->getID();

    int numold = square[oldX][oldY]->getNumBonbon();
    int numnew = square[newX][newY]->getNumBonbon();

    if(numnew == numold) {//si les bonbons ne sont pas du même type alors on appele change()
        if(colornew == 9 or colorold == 9){//Bombon_bombe
            change(newX,newY,numold,colorold);
            change(oldX,oldY,numnew,colornew);
        }
        else{
            square[newX][newY]->setID(colorold);
            square[oldX][oldY]->setID(colornew);
        }
    }
    else{
        change(newX,newY,numold,colorold);
        change(oldX,oldY,numnew,colornew);
    }
}
void controlleur::change(int x, int y, int num, int color){
    delete square[x][y];
    if(num == 0){
        if(color == 9){//Bombon_bombe
            square[x][y] = new Bonbon_bombe(color,90*x,90*y,93,94);
        }
        else{
            square[x][y] = new Bonbon(color,90*x,90*y,93,94);
        }
    }
    else if(num == 1){//Bonbon
        square[x][y] = new Bonbon_emballer(color,90*x,90*y,93,94);
    }
    else if(num == 2){//rayé
        square[x][y] = new Bonbon_rayerH(color,90*x,90*y,93,94);
    }
    else if(num == 3){//rayé
        square[x][y] = new Bonbon_rayerV(color,90*x,90*y,93,94);
    }
    else if(num == 4){//paquet
        square[x][y] = new Bonbon_glace(color,90*x,90*y,93,94);
    }
}

std::vector<int> controlleur::getupper(int i, int j){
    std::vector<int> position{-1,-1};
    int choice = -1;
    bool left = false;
    bool right = false;
    bool done = false;
    while(i>0 && not done){//tant que on est pas arrivé à ligne 1 ou que l'on n'as pas de solution
        if(square[j][i-1]->getID() == 8 || square[j][i-1]->getID() >= 10){//si c'est vide, un mur ou un glaçage
            if(square[j][i-1]->getID() >= 10){//si c'est un mur ou un glaçage
                if(j-1 >= 0){
                    if(square[j-1][i-1]->getID() < 10 && square[j-1][i]->getID() < 10){//si on peut faire tomber de la gauche du mur
                        left = true;
                    }
                }
                if(j+1 <= 8){
                    if(square[j+1][i-1]->getID() < 10 && square[j+1][i]->getID() < 10){//si on peut faire tomber de la droite du mur
                        right = true;

                    }
                }
                if(left && right) choice = (std::rand()%2);//si les deux otions valables alors choisir au hasard
                else if(left) choice = 0;
                else if(right) choice = 1;
                else done = true;
                if(choice == 0){
                    j--;
                }
                else if(choice == 1){
                    j++;
                }
            }
            else{
                i--;
            }
        }
        else{
            done = true;
            position[0] = i;
            position[1] = j;
        }
    }
    if(i == 0)position[0] = i;position[1] = j;//si on est arriver à la première ligne alors on prends la ligne 0
    return position;
}

bool controlleur::drop(){

    int color,num,k,l;
    bool repeat = false;
    std::vector<int> replacement;
    bool pass = false;

    for(int i=8;i>=0;i--){//parcours le plateau
        for(int j=8;j>=0;j--){

            if(square[j][i]->getID() == 8){//si on trouve une case vide

            	repeat = true;
                l = j;
            	if(i == 0){//si la case ne posséde pas de case supérieure on fait tomber un bombon au hasard
            		num=0;
                   	color = (std::rand()%6)+1;
                   	change(j,i,num,color);
            	}
            	else{
	            	k = i;
                    replacement = getupper(k,l);//on appelle une méthode qui nous renvoit la dernière case vide trouvé vérticalement
                    k = replacement[0];
                    l = replacement[1];
                    if(k == -1 || l == -1){//si on ne peut rien faire tomber
                        if(not pass) repeat = false;continue;
                    }
	                if(k == 0){//plafond
	                    num=0;
	                    color = (std::rand()%6)+1;
	                }
	                else{//il y a un élément audessus
	                    color = square[l][k-1]->getID();
	                    num = square[l][k-1]->getNumBonbon();
	                }
	                if(k == 0){//on met un nouveau bonbon
	                    change(j,i,num,color);
	                }
	                else if(square[l][k-1]->getNumBonbon() == square[j][i]->getNumBonbon()){//si le bonbon qui doit tomber est un objet du
	                    swap(l,k-1,j,i);                                                    //même type que celui vide alors on remplace simplement la couleur
	                    square[l][k-1]->setID(8);
	                }
	                else{//si le bonbon qui doit tomber n'est pas un objet du mêm type que celui vide
	                    change(j,i,num,color);
	                    square[l][k-1]->setID(8);
	                }
	            }
                pass = true;
            }
        }
    }
    return repeat;
}

void controlleur::plateauverif(){
	std::vector<int> temp;
	for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
        	if(square[j][i]->getNumBonbon() == 0 and square[j][i]->getID() != 8){
        		temp = square[j][i]->verif(square,j,i);
        		if(vectsum(temp) > 0) bestchoice(temp,i,j);
        	}

        }
    }
}

void controlleur::bestchoice(std::vector<int> moves,int a,int b){
	// left 0 , right 1 , up 2 , down 3
	int bestscore = vectsum(moves);
	std::vector<int> bestmoves = moves;
	int x = b;
	int y = a;
	for(int i=0;i<4;i++){//parcours la liste pour les 4 diréctions
        for(int j=1;j<=moves[i];j++){//parcourt le nombre de bonbons dans cette direction
        	if(i == 0){
        		if(b-j >= 0){
	        		if(vectsum(square[b-j][a]->verif(square,b-j,a)) > bestscore) {//verifie si les mouvements de ce bonbon rapporte plus de points
	        			bestmoves = square[b-j][a]->verif(square,b-j,a);//on remplace le mouvement actuel par un meilleur mouvement 
	        			x = b-j;
	        		}
	        	}
        	}
        	else if(i == 1){
        		if(b+j <= 8){
	        		if(vectsum(square[b+j][a]->verif(square,b+j,a)) > bestscore){
	        			bestmoves = square[b+j][a]->verif(square,b+j,a);
	        			x = b+j;
	        		}
	        	}
        	}
        	else if(i == 2){
        		if(a-j >= 0){
	        		if(vectsum(square[b][a-j]->verif(square,b,a-j)) > bestscore){
	        			bestmoves = square[b][a-j]->verif(square,b,a-j);
	        			y = a-j;
	        		}
	        	}
        	}
        	else{
        		if(a+j <= 8){
	        		if(vectsum(square[b][a+j]->verif(square,b,a+j)) > bestscore){
	        			bestmoves = square[b][a+j]->verif(square,b,a+j);
	        			y = a+j;
	        		}
	        	}
        	}
        }
   	}
   	solve(bestmoves[0],bestmoves[1],bestmoves[2],bestmoves[3],x,y);//résoud le meilleur mouvement trouvé
}

int controlleur::vectsum(std::vector<int> moves){
	int res = 0;
	if(moves[0]+moves[1]>=2) res+=(moves[0]+moves[1]);//somme le nombre de bonbons de même couleurs adjassents
	if(moves[2]+moves[3]>=2) res+=(moves[2]+moves[3]);//verticalement et horizontalement ssi la somme est supérieure à 2
	return res;
}

int controlleur::gameOver() {
    int checking = niveau->draw();
    if(checking == 0) {
        if ((level == 2 || level == 3)) {
            if( niveau->isGlacage(square) && (joueur->getScore() >= niveau->getScore())){
                shutdown = true;
                joueur->setbestScore();
                return 1; // true
            }
            else{
                shutdown = true;
                joueur->setbestScore();
                return 0; // false
            }
        }
        if (level == 1 ) {
            if(joueur->getScore() >= niveau->getScore() ){
                shutdown = true;
                joueur->setbestScore();
                return 1; // true
            }
            else{
                shutdown = false;
                joueur->setbestScore();
                return 0; //false
            }
        }

    }
    return 2;
}



void controlleur::loadNiveau() {
    std::string name = "niveau/";
    std::string s = std::to_string(level);
    name.append(s);

    const char * pchar = name.c_str();

    char buf[12];
    snprintf(buf,12,"%d",level);
    std::string myText;
    std::ifstream MyReadFile(pchar);

    int n=0;
    int r=-1;
    while(getline(MyReadFile,myText,',')){
        if(n %9 == 0) {
            r++;
            num.push_back({});
        }
        num[r].push_back(std::stoi(myText));
        n++;
    }

}

void controlleur::clearVector(){
    num.clear();
    square.clear();
}

void controlleur::setNiveau(int nv){
    level = nv;
    niveau->setNiveau(level);
}

void controlleur::init(){
    shutdown = false;
    for(int x=0; x <9;x++) {//on initialise les différents bonbons sans le tableau
        square.push_back({});
        for (int y = 0; y < 9; y++) {
            if(num[y][x] > 10){//glaçages
                square[x].push_back(new Bonbon_glace(num[y][x],90*x,90*y,94,93));
            }
            else if(num[y][x] == 10){//murs
                square[x].push_back(new Bonbon_mur(num[y][x],90*x,90*y,94,93));
            }
            else if(num[y][x] == 9){//chocolat
                square[x].push_back(new Bonbon_bombe(num[y][x],90*x,90*y,94,93));
            }
            else{//bombon normal
                square[x].push_back(new Bonbon(num[y][x],90*x,90*y,94,93));
            }
        }
    }

    for(int x=0;x<9;x++){
        for(int y=0;y<9;y++){
            for(auto &item : map1) {
                if (square[y][x]->getID() == item.first) {
                    square[y][x]->setNumBonbon(0);
                    square[y][x]->setFontImage(item.second);
                }
            }
        }
    }
    initialise();//Nous remettons les images correctes pour les bonbons
    plateauverif();//Nous vérifions si il y a des suites de bonbons à retirer
    joueur->setScore(0);
    joueur->draw();
    joueur->bestScore();
    niveau->init();
    while(drop()){      //boucle qui fait tomber les bonbons, enléve les
        initialise();   //allignement crées par la chute et redonne les bonnes images aux bonbons
        plateauverif();
        initialise();
    }
}

bool controlleur::possible(int oldX,int oldY,int newX,int newY){
    if(square[newX][newY]->getID() >= 10 || square[oldX][oldY]->getID() >= 10) return false;//si on l'in des bonbons séléctionnés 
                                                                                            //est un mur ou un glaçage on renvoit false directement
    bool result = false;
    swap(oldX,oldY,newX,newY);//on échange les deux bonbons de place au début pour faciliter les calculs
    int colornew = square[newX][newY]->getID();
    int colorold = square[oldX][oldY]->getID();
    int numnew = square[newX][newY]->getNumBonbon();
    int numold = square[oldX][oldY]->getNumBonbon();
    if(colorold == 9 && colornew == 9){//Combo Bonus chocolat
        result = true;
    }
    else if(colorold == 9 || colornew == 9){//ici on gére le cas où un des bonbons est un chocolat

        if(numnew == 2 || numnew == 3) result = true;      //et l'autre est
        else if(numold == 2 || numold == 3) result = true; //un bonbon rayé

        else if(numnew == 0 && colornew <= 6) result = true;//et l'autre est
        else if(numold == 0 && colorold <= 6) result = true;//un bonbon normal

    }
    else if((numnew == 2 || numnew == 3) && (numold == 2 || numold == 3)){//ici on gére le cas où les deux bonbons sont rayes
        result = true;
    }
    else if(((numnew == 2 || numnew == 3) || (numold == 2 || numold == 3)) && (numnew == 1 || numold == 1)){//ici on gére le cas où l'un des deux
        result = true;                                                                                      //bonbons est rayé et l'autre est normal
    }
    else if(colornew <= 6 and colorold <= 6){//ici on gére le cas où les deux bonbons sont normaux
        std::vector<int> y1 = square[newX][newY]->verif(square,newX,newY);
        //left 0 , right 1 , up 2 , down 3

        if(vectsum(y1)>0){//on vérifie que les vecteur contien assez de bonbons pour former un mouvement
            result = true;
        }

    }
    swap(oldX,oldY,newX,newY);
    return(result);
}

Bonbon* controlleur::moveLeft(){
    Bonbon *temp;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(i>0){
                if(possible(j,i,j,i-1)) return square[j][i];
            }
            if(j>0){
                if(possible(j,i,j-1,i)) return square[j][i];
            }
            if(i<8){
                if(possible(j,i,j,i+1)) return square[j][i];
            }
            if(j<8){
                if(possible(j,i,j+1,i)) return square[j][i];
            }
        }
    }
    return nullptr;
}

void controlleur::shuffle(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(square[j][i]->getNumBonbon()==0){//on vérifie que
                if(square[j][i]->getID()<=6){   //c'est un bonbon normal
                    square[j][i]->setID((std::rand()%6)+1);//modifie la couleur du bonbon au hasard
                    initialise();//on met les bonnes imahes aux bonbons
                }
            }
        }
    }
}

bool controlleur::getshutdown() {
    return shutdown;
}

