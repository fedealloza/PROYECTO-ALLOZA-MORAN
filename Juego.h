#ifndef PROYECTO_FINAL_JUEGO_H
#define PROYECTO_FINAL_JUEGO_H
#include <iostream>
#include <vector>
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include <SFML\Window.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <ctime>
#include <sstream>


class Juego {

private:
    //VARIABLES
    //VENTANA
    sf::RenderWindow* window;
    sf::VideoMode videoMode;
    sf::Event ev;

    //POSICION DEL MOUSE
    sf::Vector2i mousePoswindows;
    sf::Vector2f mousePosView;

    //RECURSOS
    sf::Font font;

    //TEXTO
    sf::Text uiText;
    sf::Text uiScore;

    sf::Sound sonido2;
    sf::SoundBuffer buffer2;

    //LOGICA DEL JUEGO
    bool endGame;

    int health;
    float enemySpawnTimer;
    float enemySpawnTimerMax;
    int maxEnemies;
    bool mouseHeld;

    //FUNCIONES PRIVADAS
    void initVariables();
    void initWindow();
    void initEnemies();
    void initFonts();
    void initText();
    void initScore();

    void mostrarjuego1();



    //OBJETOS DEL JUEGO
    std::vector<sf::RectangleShape> enemies;
    sf::RectangleShape enemy;

    //TEXTURA FONDO
    sf::Texture * textura1;//FONDO
    sf::Sprite * sprite1;

    //MIRA WACHO
    sf::Texture * txt_mira;
    sf::Sprite  * spr_mira;




public:



    unsigned points;
    //CONSTRUCTORES Y DESTRUCTORES
    Juego();
    virtual ~Juego();

    //ACCESORIOS

    const bool running() const;
    const bool getendGame() const;

    //FUNCIONES

    void spawnEnemy();

    void pollEvents();
    void updateMousePositions();
    void updateText();
    void updateScore();
    void updateEnemies();
    void update();


    void renderText(sf::RenderTarget& target);
    void renderEnemies(sf::RenderTarget& target);
    void render();

    //MIRA WACHO
    void cargar_graficos();



};


#endif //PROYECTO_FINAL_JUEGO_H
