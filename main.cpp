#include <iostream>
#include <fstream>
#include <unordered_map>

/*
 * Variables necessaries per determinar l'ubicació de l'executable
 * del programa.
 */
#ifdef WINDOWS
#include <direct.h>
    #define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif



using namespace std;

/*
 * Mapa on s'emmagatzemen els regals amb les unitats corresponents.
 */
unordered_map<string, int> regals;


/*
 * Funció per determinar l'ubicació de l'arxiu executable del programa.
 */
 string getCurrentDir(){

    char cCurrentPath[FILENAME_MAX];

    if (!GetCurrentDir(cCurrentPath, sizeof(cCurrentPath)))
    {
        return "Error";
    }

    cCurrentPath[sizeof(cCurrentPath) - 1] = '\0';

     return cCurrentPath;
}

/*
 * Funció que afageix un regal a la llista, o incrementa les
 * unitats en el cas de que el regal ja existeixi.
 */
void afegirRegal(string nomRegal){

    if(!regals.count(nomRegal)){
        //cout << "El regal NO exixteix! Afegit!" << endl;
        regals[nomRegal] = 1;
    }else{
        //cout << "El regal EXISTEIX! Increment!" << endl;
        regals[nomRegal]= regals[nomRegal]+1;
    }
}

/*
 * Funció utilitzada per tractar una linia del fitxer "pendents.txt".
 */
void tractarLinea(string linia) {

    string nomRegal = "";

    for(int i = 0; i < linia.length(); i++){
        if(linia.at(i) != ' '){
            nomRegal += linia.at(i);
        }else{
            break;
        }
    }

    afegirRegal(nomRegal);

}

/*
 * Funció per llegir el fitxer "pendents.txt" linia a linia.
 */
void llegirFitxer() {

    string linea = "";
    bool finalFitxer = false;

    ifstream file("pendents.txt");
    string temp;

    while(getline(file, temp)){
        temp.substr(0,10);
        tractarLinea(temp);
    }

}

/*
 * Funció que genera un fitxer anomenat "regalsPendents.txt" a
 * partir del contingut del mapa.
 */
void generarLlistaRegals(){

    ofstream out("regalsPendents.txt");

    for ( const auto &clau : regals ) {
        int unitatsRegal = clau.second;

        out <<clau.first << " " << unitatsRegal << "\n";

    }
    out.close();
    cout << "Llista de regals pendents generada correctament! Ubicació: " + getCurrentDir()  << endl;
}


int main() {
    llegirFitxer();
    generarLlistaRegals();
}