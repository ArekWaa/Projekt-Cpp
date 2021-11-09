#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <locale.h> //do obslugi polskich znakow
using namespace std;

//klasy

class Text
{
public:
    sf::Font font;
    sf::Text text;

    Text()
    {
        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setCharacterSize(30);
    }

    void setText(string inputText)
    {
        text.setString(inputText);
    }
    void setText(int inputText)
    {
        text.setString(to_string(inputText));
    }
    void setPosition(int x, int y)
    {
        text.setPosition(x, y);
    }
    void draw(sf::RenderWindow &window)
    {
        window.draw(text);
    }
};

class Button
{
public:
    sf::RectangleShape body;
    sf::Text text;
    sf::Font font;

    Button(float sizeX, float sizeY, int posX, int posY, sf::Color color)
    {
        body.setSize({sizeX, sizeY});
        body.setFillColor(color);
        body.setPosition(posX, posY);
        body.setOutlineThickness(2);

        font.loadFromFile("arial.ttf");
        text.setFont(font);
        text.setCharacterSize(30);
        text.setString("przycisk");
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
        text.setFillColor(sf::Color::Black);
        text.setPosition(body.getPosition().x + body.getGlobalBounds().width/2, body.getPosition().y + body.getGlobalBounds().height/2 - 15);
    }

    bool isHover(sf::RenderWindow &window)
    {
        if (body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
            return true;
        else return false;
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(body);
        window.draw(text);
    }

};

class ScreenMainMenu
{
public:
    Text title;
    Button button1;
    Button button2;
    Button button3;
    Button button4;
    bool active = false;

    ScreenMainMenu() : button1(200, 75, 100, 100, sf::Color::White), button2(200, 75, 100, 200, sf::Color::White),
                       button3(200, 75, 100, 300, sf::Color::White), button4(200, 75, 100, 400, sf::Color::White)
    {
        title.setText("Menu");
        title.setPosition(5, 5);

        button3.text.setString("O aplikacji");
        button3.text.setOrigin(button3.text.getGlobalBounds().width/2, button3.text.getGlobalBounds().height/2);
        button3.text.setFillColor(sf::Color::Black);
        button3.text.setPosition(button3.body.getPosition().x + button3.body.getGlobalBounds().width/2, button3.body.getPosition().y + button3.body.getGlobalBounds().height/2 - 15);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        title.draw(window);
        button1.draw(window);
        button2.draw(window);
        button3.draw(window);
        button4.draw(window);
    }
};


class ScreenAplikacji
{
public:
    Text title;
    Text info;
    Button button1;
    bool active = false;

    ScreenAplikacji() : button1(200, 75, 400, 600, sf::Color::White)
    {
        title.setText("O aplikacji");
        title.setPosition(600, 20);

        info.setText("\„Splitter\" to aplikacja s³u¿¹ca do równomiernego podzia³u obowi¹zków\nwœród wspó³lokatorów. Pozwala na dodawanie domowych obowiązków\nwykonywanych przez u¿ytkowników. Posiada system punktowy motywuj¹cy\ndo systematycznej pracy. U¿ytkownik dostaje punkty dostosowane\ndo trudnoœci oraz poœwiêconego czasu na dane zadanie (np. za wyrzucenie\nœmieci czy rozwieszenie prania) . W ka¿dym miesi¹cu wspó³lokatorzy\npowinni otrzymaæ podobn¹ sumê punktów. Aktualny stan punktów mo¿na\nœledziæ w oknie „Ranking” jako tabelê oraz w formie wykresu.");
        info.setPosition(150, 200);

        button1.text.setString("Powrót");
        button1.text.setOrigin(button1.text.getGlobalBounds().width/2, button1.text.getGlobalBounds().height/2);
        button1.text.setPosition(button1.body.getPosition().x + button1.body.getGlobalBounds().width/2, button1.body.getPosition().y + button1.body.getGlobalBounds().height/2 - 15);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        title.draw(window);
        info.draw(window);
        button1.draw(window);

    }
};


int main()
{
    setlocale(LC_CTYPE, "Polish");  //obsluga polskich znakow w napisach

    //zmienne
    ScreenMainMenu mainMenu;
    ScreenAplikacji oAplikacji;

    mainMenu.active = true;

    sf::RenderWindow window(sf::VideoMode(1280, 720), "Splitter");
    window.setFramerateLimit(60);

    // run the program as long as the window is open
    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (mainMenu.active == true)
            {
                if (event.type == sf::Event::MouseButtonPressed && mainMenu.button3.isHover(window) == true)
                {
                    mainMenu.active = false;
                    oAplikacji.active = true;
                }
            }
            else if (oAplikacji.active == true)
            {
                if (event.type == sf::Event::MouseButtonPressed && oAplikacji.button1.isHover(window) == true)
                {
                    mainMenu.active = true;
                    oAplikacji.active = false;
                }
            }
            //guziki
        }
        // clear the window with black color
        window.clear(sf::Color::Black);

        //rysowanie
        if (mainMenu.active == true) mainMenu.drawScreen(window);
        if (oAplikacji.active == true) oAplikacji.drawScreen(window);

        window.display();
    }
    return 0;
}
