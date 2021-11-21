#pragma once
#ifndef PROYECTO_FINAL_MAINMENU_H
#define PROYECTO_FINAL_MAINMENU_H
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

#define Max_main_menu 5
class MainMenu {

public:
    MainMenu(float width,float height);

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int MainMenuPressed(){
        return MainMenuSelected;
    }
    ~MainMenu();

    MainMenu();

private:
    int MainMenuSelected;
    Font font;
    Text mainMenu[Max_main_menu];


};


#endif //PROYECTO_FINAL_MAINMENU_H
