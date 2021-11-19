#include <iostream>
#include "Juego.h"
#include "Juego_facil.h"
#include "Juego_dificil.h"
#include "SFML\Audio.hpp"
#include "SFML\Graphics.hpp"
#include "MainMenu.h"
#include <sstream>
#include <cstring>


using namespace sf;
using namespace std;

int acumulador =0;

void mostrarjuego1();
void mostrarjuego2();
void mostrarjuego3();

void showHighScore(int x, int y, string word, sf::RenderWindow& window2, sf::Font* font);
void score();



int main() {


    RenderWindow MENU(VideoMode(1024, 600), "SPACE CUBE", Style::Default);
    MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);

    //FONDO DEL MENU
    RectangleShape background;
    background.setSize(Vector2f(1024,600));
    Texture Maintexture;
    Maintexture.loadFromFile("MENu.png");
    background.setTexture(&Maintexture);





    //TODO ESTO ES MUSICA!

                                                            // SONIDO DE LAS FECHAS!//
    sf::SoundBuffer buffer;
    // Cargamos un archivo en el buffer
    if (!buffer.loadFromFile("disparo.wav"))
    {
        return EXIT_FAILURE;
    }
    // Creamos un sonido
    sf::Sound sonido;
    // Le asignamos el buffer cargado
    sonido.setBuffer(buffer);
    // establecemos el volumen
    sonido.setVolume(20);

                                                            //SONIDO DEL ENTER!//

    sf::SoundBuffer buffer2;
    // Cargamos un archivo en el buffer
    if (!buffer2.loadFromFile("sonidoenter.wav"))
    {
        return EXIT_FAILURE;
    }
    // Creamos un sonido
    sf::Sound sonido2;
    // Le asignamos el buffer cargado
    sonido2.setBuffer(buffer2);
    // establecemos el volumen
    sonido2.setVolume(20);



                                                            //SONIDO DE SPACE CUBE!//

    sf::SoundBuffer bafereano;
    // Cargamos un archivo en el buffer
    if (!bafereano.loadFromFile("intro2.wav"))
    {
        return EXIT_FAILURE;
    }
    // Creamos un sonido
    sf::Sound sonedeano;
    // Le asignamos el buffer cargado
    sonedeano.setBuffer(bafereano);
    // establecemos el volumen
    sonedeano.setVolume(500.f);
    sonedeano.play();


                                                            //MUSICA DE FONDO!//
    sf::Music musica;
    // Abrimos el fichero de música que queremos reproducir
    musica.openFromFile("David Fesliyan.ogg");
    // Activamos el loop cuando acabe empezará de nuevo
    musica.setLoop(true);
    // Empezamos a reproducir nuesta música
    musica.setVolume(20.f);
    musica.play();

    while (MENU.isOpen())
    {
        void pantalla_final();

        Event event;
        while (MENU.pollEvent(event))
        {



            if (event.type == Event::Closed)
            {

                MENU.close();
            }
            if (event.type == Event::KeyReleased)
            {
                if (event.key.code == Keyboard::Up)
                {
                    sonido.play();
                    mainMenu.MoveUp();
                    break;

                }
                if (event.key.code == Keyboard::Down)
                {
                    sonido.play();
                    mainMenu.MoveDown();
                    break;

                }
                if (event.key.code == Keyboard::Return)
                {


                    int x = mainMenu.MainMenuPressed();
                    if (x == 0)
                    {

                        sonido2.play();
                        mostrarjuego2();

                    }
                    if (x == 1)
                    {
                        sonido2.play();
                        mostrarjuego1();
                    }

                    if (x == 2)
                    {
                        sonido2.play();
                        mostrarjuego3();
                    }
                    if (x == 3)
                    {
                        score();
                    }
                    if (x == 4)
                    MENU.close();
                    break;
                }
            }
        }
        MENU.clear();
        MENU.draw(background);
        mainMenu.draw(MENU);
        MENU.display();

    }

    return 0;
}


void mostrarjuego1()
{
    //srand
    srand(static_cast<unsigned>(time(NULL)));
    //MOTOR DE JUEGO
    Juego juego;

    ///BUCLE DEL JUEGO

    while(juego.running() && !juego.getendGame()){

        //CARGAR
        juego.update();

        //RENDERIZAR
        juego.render();
    }


    //FIN DE LA APLICACION//
}

void mostrarjuego2()
{
    //srand
    srand(static_cast<unsigned>(time(NULL)));
    //MOTOR DE JUEGO
    Juego_facil Juego_facil;

    ///BUCLE DEL JUEGO

    while(Juego_facil.running() && !Juego_facil.getendGame()){

        //CARGAR
        Juego_facil.update();

        //RENDERIZAR
        Juego_facil.render();
    }

    //FIN DE LA APLICACION//
}

void mostrarjuego3()
{
    //srand
    srand(static_cast<unsigned>(time(NULL)));
    //MOTOR DE JUEGO
    Juego_dificil Juego_dificil;

    ///BUCLE DEL JUEGO

    while(Juego_dificil.running() && !Juego_dificil.getendGame()){

        //CARGAR
        Juego_dificil.update();

        //RENDERIZAR
        Juego_dificil.render();
    }

    //FIN DE LA APLICACION//
}


void score() {
    Juego juego;

    sf::Font font;
    font.loadFromFile("fuente_menu.ttf");
    sf::RenderWindow window(sf::VideoMode(1024, 600), "HighScore");
    RectangleShape background3;
    background3.setSize(Vector2f(1024, 600));
    Texture Maintexture3;
    Maintexture3.loadFromFile("highscore.png");
    background3.setTexture(&Maintexture3);

    acumulador+=juego.points;


    FILE *fp;
    char temp[255];
    int score[10];
    string name[10];
    vector<pair<int, string>> userScore;
    fp = fopen("./Score.txt", "r");
    for (int i = 0; i < 5; i++) {
        fscanf(fp, "%s", &temp);
        name[i] = temp;
        fscanf(fp, "%d", &score[i]);
        userScore.push_back(make_pair(score[i], name[i]));
        //cout << temp << " " << score;
    }
    name[5] = "Player";
    score[5];
    userScore.push_back(make_pair(score[5], name[5]));
    sort(userScore.begin(), userScore.end());
    fclose(fp);
    fopen("./Score.txt", "w");
    for (int i = 5; i >= 1; i--) {
        strcpy(temp, userScore[i].second.c_str());
        fprintf(fp, "%s %d\n", temp, userScore[i].first);
    }
    fclose(fp);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background3);
        showHighScore(512,10,"",window,&font);
        showHighScore(300, 365, userScore[5].second, window, &font);
        showHighScore(512, 365, to_string(userScore[5].first), window, &font);
        window.display();
    }

}
void showHighScore(int x,int y,string word,sf::RenderWindow& window,sf::Font* font)
{


    sf::Text text;
    text.setFont(*font);
    text.setPosition(x, y);
    text.setString(word);
    text.setCharacterSize(65);
    window.draw(text);

}