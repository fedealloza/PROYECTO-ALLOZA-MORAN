#include "Score.h"
#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include<stdio.h>
#include<utility>
#include<algorithm>
#include<string>
#include<vector>
#include<iostream>
#include "Juego.h"
#include <cstring>
#include <windows.h>
using namespace std;
void showHighScore(int x, int y, string word, sf::RenderWindow& window, sf::Font* font);

void Score::score()
{
    sf::Font font;
    font.loadFromFile("AlexandriaFLF.ttf");
    sf::RenderWindow window(sf::VideoMode(1080, 720), "HighScore");
    FILE* fp;
    char temp[255];
    int score[6];
    string name[6];
    vector <pair<int, string>> userScore;
    fp = fopen("./Score.txt", "r");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fp, "%s", &temp);
        name[i] = temp;
        fscanf(fp,"%d",&score[i]);
        userScore.push_back(make_pair(score[i], name[i]));
        //cout << temp << " " << score;
    }
    name[5] = "HAHA";
    score[5] = 1234;
    userScore.push_back(make_pair(score[5], name[5]));
    sort(userScore.begin(),userScore.end());
    fclose(fp);
    fopen("./Score.txt", "w");
    for (int i = 5; i >= 1; i--)
    {
        strcpy(temp, userScore[i].second.c_str());
        fprintf(fp,"%s %d\n",temp,userScore[i].first);
    }
    fclose(fp);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        showHighScore(10,10,"HIGHSCORE",window,&font);
        showHighScore(10, 40, userScore[5].second, window, &font);
        showHighScore(100, 40, to_string(userScore[5].first), window, &font);
        window.display();
    }

}
void showHighScore(int x,int y,string word,sf::RenderWindow& window,sf::Font* font)
{
    sf::Text text;
    text.setFont(*font);
    text.setPosition(x, y);
    text.setString(word);
    text.setCharacterSize(32);
    window.draw(text);
}
