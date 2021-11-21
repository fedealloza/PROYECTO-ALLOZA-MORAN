#include "Juego_dificil.h"


//FUNCIONES PRIVADAS

void Juego_dificil::initVariables()
{
    this->window = nullptr;

    //Logica de juego
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->mouseHeld = false;

    if(this->buffer2.loadFromFile("disparo.wav")){
        std::cout<< "ERROR::JUEGO::INITFONTS: CARGAR LA FUENTE!" <<"\n";
    }

// Le asignamos el buffer cargado
    sonido2.setBuffer(buffer2);
// establecemos el volumen
    sonido2.setVolume(20);
}
void Juego_dificil::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 1024;

    this->window = new sf::RenderWindow(this->videoMode, "SPACE CUBE ", sf::Style::Titlebar | sf::Style::Close );

    this->window->setFramerateLimit(45);
}

void Juego_dificil::initFonts() {
    if(this->font.loadFromFile("fuente.ttf")){
        std::cout<< "ERROR::JUEGO::INITFONTS: CARGAR LA FUENTE!" <<"\n";
    }
}

void Juego_dificil::initText() {
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NINGUNO");
}

void Juego_dificil::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    this->enemy.setOutlineColor(sf::Color::Black);
    this->enemy.setOutlineThickness(10.f);
}



//CONSTRUCTOR Y DESTRUCTORES
Juego_dificil::Juego_dificil()
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
Juego_dificil::~Juego_dificil()
{
    delete this->window;
}



const bool Juego_dificil::running() const
{
    return this ->window->isOpen();
}

const bool Juego_dificil::getendGame() const {
    return this->endGame;
}

void Juego_dificil::spawnEnemy(){

    this->enemy.setPosition(
            static_cast<float>(rand()%static_cast<int>(this->window->getSize().x- this->enemy.getSize().x)),
            0.f
    );

    //Tipo de enemigo random
    int type = rand()%5;

    switch (type) {
        case 0:
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
        case 2:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Cyan);
            break;
        case 3:
            this->enemy.setSize(sf::Vector2f(70.f, 70.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 4:
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
void Juego_dificil::pollEvents()
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



void Juego_dificil::updateMousePositions(){
    this->mousePoswindows = sf::Mouse::getPosition(* this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePoswindows);

}

void Juego_dificil::updateText() {
    std::stringstream ss;

    ss << "Puntos: " << this->points << "\n" << "Vidas: " << this->health << "\n";

    this->uiText.setString(ss.str());
}

void Juego_dificil::updateEnemies() {
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
                    if(this->enemies[i].getFillColor()== sf::Color::Magenta){
                        this->points+= 10;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Blue){
                        this->points+= 7;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Cyan){
                        this->points+= 5;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Red){
                        this->points+= 3;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Green){
                        this->points+= 2;
                    } else if(this->enemies[i].getFillColor()== sf::Color::Yellow){
                        this->points+= 1;
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

void Juego_dificil::update()
{
    this->pollEvents();

    if(this->endGame == false){
        this->updateMousePositions();
        this->updateText();
        this->updateEnemies();
    }
    //fin del juego
    if(this->health <=0){
        this->endGame = true;
    }
}

void Juego_dificil::renderText(sf::RenderTarget& target) {
    target.draw(this->uiText);
}

void Juego_dificil::renderEnemies(sf::RenderTarget& target) {
    for (auto &e : this->enemies) {
        target.draw(e);
    }
}

void Juego_dificil::render()
{
    /*
     * -Limpia el objeto antiguo
     * -Renderiza objetos
     * -Visualiza en la ventana
     */
    this->window->clear();
    window->draw(*sprite1);
    //DIBUJA LOS OBJETOS DEL JUEGO
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();

}


