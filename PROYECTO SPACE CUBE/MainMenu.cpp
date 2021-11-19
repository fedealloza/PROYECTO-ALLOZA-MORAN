#include "MainMenu.h"


MainMenu::MainMenu(float widht, float height){

    if (!font.loadFromFile("fuente_menu.ttf")){
        cout<<"No font is here";
    }

    //BOTON DE JUGAR
    mainMenu[0].setFont(font);
    mainMenu[0].setFillColor(Color::White);
    mainMenu[0].setString("Facil");
    mainMenu[0].setCharacterSize(70);
    mainMenu[0].setPosition(135 , 200);

    //BOTON OPCIONES
    mainMenu[1].setFont(font);
    mainMenu[1].setFillColor(Color::White);
    mainMenu[1].setString("Normal");
    mainMenu[1].setCharacterSize(70);
    mainMenu[1].setPosition(380 , 200);

    //BOTON ABOUT
    mainMenu[2].setFont(font);
    mainMenu[2].setFillColor(Color::White);
    mainMenu[2].setString("Dificil");
    mainMenu[2].setCharacterSize(70);
    mainMenu[2].setPosition(684 , 200);

    //BOTON ABOUT
    mainMenu[3].setFont(font);
    mainMenu[3].setFillColor(Color::White);
    mainMenu[3].setString("highScore");
    mainMenu[3].setCharacterSize(70);
    mainMenu[3].setPosition(200 , 320);

    //BOTON SALIR
    mainMenu[4].setFont(font);
    mainMenu[4].setFillColor(Color::White);
    mainMenu[4].setString("Salir");
    mainMenu[4].setCharacterSize(70);
    mainMenu[4].setPosition(600 , 320);
    MainMenuSelected = -1;

}

MainMenu::MainMenu() {

}
MainMenu::~MainMenu() {

}

//DIBUJAR  BOTONES EN PÄNTALLA

void MainMenu::draw(RenderWindow &window) {
    for (int i = 0; i < Max_main_menu; ++i) {
        window.draw(mainMenu[i]);
    }

}


//MOVIMIENTO ARRIBA

void MainMenu::MoveUp() {

    if(MainMenuSelected -1 >=0){
        mainMenu[MainMenuSelected].setFillColor(Color::White);

        MainMenuSelected--;
        if(MainMenuSelected == -1){
            MainMenuSelected = 2;
        }
        mainMenu[MainMenuSelected].setFillColor(Color::Blue);
    }

}

//MOVIMIENTO ABAJO

void MainMenu::MoveDown() {
    mainMenu[MainMenuSelected].setFillColor(Color::White);
    MainMenuSelected++;
    if(MainMenuSelected==5){

        MainMenuSelected = 0;
    }
    mainMenu[MainMenuSelected].setFillColor(Color::Blue);
}