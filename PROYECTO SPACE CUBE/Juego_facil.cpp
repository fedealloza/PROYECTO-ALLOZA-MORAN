#include "Juego_facil.h"
#include "SFML\Audio.hpp"

//FUNCIONES PRIVADAS

void Juego_facil::initVariables()
{
    this->window = nullptr;

    //Logica de juego
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 2;
    this->mouseHeld = false;

    if(this->buffer2.loadFromFile("disparo.wav")){
        std::cout<< "ERROR::JUEGO::INITFONTS: CARGAR LA FUENTE!" <<"\n";
    }

// Le asignamos el buffer cargado
    sonido2.setBuffer(buffer2);
// establecemos el volumen
    sonido2.setVolume(20);
}
void Juego_facil::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 1024;

    this->window = new sf::RenderWindow(this->videoMode, "SPACE CUBE ", sf::Style::Titlebar | sf::Style::Close );

    this->window->setFramerateLimit(60);
}

void Juego_facil::initFonts() {
    if(this->font.loadFromFile("fuente.ttf")){
        std::cout<< "ERROR::JUEGO::INITFONTS: CARGAR LA FUENTE!" <<"\n";
    }
}

void Juego_facil::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NINGUNO");
}

void Juego_facil::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Black);
    this->enemy.setOutlineThickness(10.f);
}



//CONSTRUCTOR Y DESTRUCTORES
Juego_facil::Juego_facil()
{

    //TEXTURA DEL FONDO
    textura1 = new sf::Texture;
    sprite1 = new sf::Sprite;
    textura1->loadFromFile("fondo.png");
    sprite1->setTexture(*textura1);

    this->initVariables();
    this->initWindow();
    this->initText();
    this->initFonts();
    this->initEnemies();

}
Juego_facil::~Juego_facil()
{
    delete this->window;
}



const bool Juego_facil::running() const
{
    return this ->window->isOpen();
}

const bool Juego_facil::getendGame() const {
    return this->endGame;
}

void Juego_facil::spawnEnemy(){

    this->enemy.setPosition(
            static_cast<float>(rand()%static_cast<int>(this->window->getSize().x- this->enemy.getSize().x)),
            0.f
    );

    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Green);

    //spawn
    this->enemies.push_back(this->enemy);
}

//ACCESORIOS
void Juego_facil::pollEvents()
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



void Juego_facil::updateMousePositions(){
    this->mousePoswindows = sf::Mouse::getPosition(* this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePoswindows);

}

void Juego_facil::updateText() {
    std::stringstream ss;

    ss << "Puntos: " << this->points << "\n" << "Vidas: " << this->health << "\n";

    this->uiText.setString(ss.str());
}



void Juego_facil::updateEnemies() {


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
                    if(this->enemies[i].getFillColor()== sf::Color::Green){
                        this->points+= 10;
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

void Juego_facil::update()
{
    this->pollEvents();

    if(this->endGame == false){
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }
    //fin del Juego_facil
    if(this->health <=0){
        this->endGame = true;
    }
}

void Juego_facil::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Juego_facil::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

void Juego_facil::render()
{
    /*
     * -Limpia el objeto antiguo
     * -Renderiza objetos
     * -Visualiza en la ventana
     */
    this->window->clear();
    window->draw(*sprite1);
    //DIBUJA LOS OBJETOS DEL Juego_facil
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();

}


