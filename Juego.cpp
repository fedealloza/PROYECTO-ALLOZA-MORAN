#include "Juego.h"
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <windows.h>



//FUNCIONES PRIVADAS

void Juego::initVariables()
{
    this->window = nullptr;

    //Logica de juego
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 5;
    this->mouseHeld = false;

    if(this->buffer2.loadFromFile("disparo.wav")){
        std::cout<< "ERROR::JUEGO::INITFONTS: CARGAR LA FUENTE!" <<"\n";
    }

// Le asignamos el buffer cargado
    sonido2.setBuffer(buffer2);
// establecemos el volumen
    sonido2.setVolume(20);
}
void Juego::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 1024;

    this->window = new sf::RenderWindow(this->videoMode, "SPACE CUBE ", sf::Style::Titlebar | sf::Style::Close );
    this->window->setFramerateLimit(60);
}

void Juego::initFonts() {
    if(this->font.loadFromFile("fuente.ttf")){
        //std::cout<< "ERROR::JUEGO::INITFONTS: CARGAR LA FUENTE!" <<"\n";
    }
}

void Juego::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NINGUNO");
}

void Juego::initScore() {
    this->uiScore.setFont(this->font);
    this->uiScore.setCharacterSize(24);
    this->uiScore.setFillColor(sf::Color::White);
    this->uiScore.setString("NINGUNO");
}

void Juego::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Black);
    this->enemy.setOutlineThickness(10.f);
}



//CONSTRUCTOR Y DESTRUCTORES
Juego::Juego()
{

    //TEXTURA DEL FONDO

    textura1 = new sf::Texture;
    sprite1 = new sf::Sprite;
    textura1->loadFromFile("fondo.png");
    sprite1->setTexture(*textura1);

    txt_mira = new sf::Texture;
    spr_mira = new sf::Sprite;
    txt_mira->loadFromFile("mira.png");
    spr_mira->setTexture(*txt_mira);

    this->initVariables();
    this->initWindow();
    this->initText();
    this->initFonts();
    this->initEnemies();
this->initScore();

}
Juego::~Juego()
{
    delete this->window;
}



const bool Juego::running() const
{
    return this ->window->isOpen();
}

const bool Juego::getendGame() const {
    return this->endGame;
}


void Juego::spawnEnemy(){

    this->enemy.setPosition(
            static_cast<float>(rand()%static_cast<int>(this->window->getSize().x- this->enemy.getSize().x)),
            0.f
    );

    //Tipo de enemigo random
    int type = rand()%3;

    switch (type) {
        case 0:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
        case 1:
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 2:
            this->enemy.setSize(sf::Vector2f(90.f, 90.f));
            this->enemy.setFillColor(sf::Color::Green);
            break;
        default:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::Yellow);
            break;
    }

    //spawn
    this->enemies.push_back(this->enemy);
}

//ACCESORIOS
void Juego::pollEvents()
{


    //Evento polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type) {

            case sf::Event::Closed:

                this->window->close();
                break;

            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;

        }
    }


}



void Juego::updateMousePositions(){
    this->mousePoswindows = sf::Mouse::getPosition(* this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePoswindows);

}

void Juego::updateText() {
    std::stringstream ss;

    ss << "Puntos: " << this->points << "\n" << "Vidas: " << this->health << "\n";

    this->uiText.setString(ss.str());
}


void Juego::updateEnemies() {
    //acutalizando el timer para el spawn de enemigos
    if(this->enemies.size()< this->maxEnemies){
        if(this->enemySpawnTimer>=this->enemySpawnTimerMax){
            //spawnea y resetea el timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }else{
            this->enemySpawnTimer += 1.f;
        }
    }

    //mover los enemigos

    for (int i = 0; i < this->enemies.size(); ++i) {
        bool deleted = false;
        this->enemies[i].move(0.f, 5.f);
        if(this->enemies[i].getPosition().y > this->window->getSize().y){
            this->enemies.erase(this->enemies.begin() + i);
            this->health -=1;
            std::cout<<"Vidas: " <<this->health << "\n";
        }

    }


    //checkear si clickea arriba

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){

        if(this->mouseHeld == false){

            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; ++i) {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)){
                    //ganar puntos
                    if(this->enemies[i].getFillColor()== sf::Color::Cyan){
                        this->points+= 10;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Red){
                        this->points+= 7;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Green){
                        this->points+= 5;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Yellow){
                        this->points+= 3;
                    }

                    this->sonido2.play();
                    std::cout<<"Puntos: " <<this->points << "\n";
                    deleted=true;
                    this->enemies.erase(this->enemies.begin() + i);

                }
            }
        }


    }else{
        this->mouseHeld= false;
    }
}

void Juego::update()
{

    this->pollEvents();

    if(this->endGame == false){
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }
    //fin del juego
    if(this->health <=0){

        //ACA SE PONE LA PANTALLA CON PUNTAJE!


        this->endGame = true;



    }

}

void Juego::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Juego::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}


void Juego::render()
{

    this->window->clear();
    window->draw(*sprite1);

    this->renderEnemies(*this->window);
    this->renderText(*this->window);

    this->window->display();
};