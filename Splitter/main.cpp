#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <locale.h> //do obslugi polskich znakow
#include <string>

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

class TextBox
{
public:
    sf::RectangleShape body;
    Text tekst;
    bool isTyping = false;
    string textString = "tetete";

    TextBox(int x, int y)
    {
        body.setPosition(x,y);
        body.setSize({300,50});
        tekst.setPosition(x+5,y+5);
        tekst.setText(textString);
        tekst.text.setFillColor(sf::Color::Black);
    }

    void drawTextBox(sf::RenderWindow &window)
    {
        window.draw(body);
        tekst.draw(window);
    }

    void asciiCheck(char litera)
    {
        if(litera != 8)
        {
            if (litera >= 48 && litera <= 57 || litera >= 65 && litera <= 90 || litera >= 97 && litera <= 122)
            {
                textString += litera;
            }
        }
        else
        {
            if (textString.length() > 0)
            {
                textString = textString.substr(0, textString.length() - 1);
            }
        }

        tekst.setText(textString);
    }
};

class ScreenLogOrReg    //Login Or Registration
{
public:
    Button button1; //Zaloguj się
    Button button2; //Zarejestruj
    bool active = false;

    ScreenLogOrReg() : button1(500, 75, 380, 250, sf::Color::White), button2(500, 75, 380, 370, sf::Color::White)
    {
        button1.text.setString(L"Zaloguj się");
        button1.text.setOrigin(button1.text.getGlobalBounds().width/2, button1.text.getGlobalBounds().height/2);
        button1.text.setFillColor(sf::Color::Black);
        button1.text.setPosition(button1.body.getPosition().x + button1.body.getGlobalBounds().width/2, button1.body.getPosition().y + button1.body.getGlobalBounds().height/2 - 15);

        button2.text.setString(L"Zarejestruj się");
        button2.text.setOrigin(button2.text.getGlobalBounds().width/2, button2.text.getGlobalBounds().height/2);
        button2.text.setFillColor(sf::Color::Black);
        button2.text.setPosition(button2.body.getPosition().x + button2.body.getGlobalBounds().width/2, button2.body.getPosition().y + button2.body.getGlobalBounds().height/2 - 15);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        button1.draw(window);
        button2.draw(window);
    }
};

class ScreenLogin
{
public:
    Text title;
    Button button1; //powrót
    TextBox textBox1;
    bool active = false;


    ScreenLogin() : button1(200, 75, 100, 100, sf::Color::White), textBox1(300,300)
    {
        title.setText("Zaloguj się");
        title.setPosition(550, 5);

        button1.text.setString("Powrót");
        button1.text.setOrigin(button1.text.getGlobalBounds().width/2, button1.text.getGlobalBounds().height/2);
        button1.text.setFillColor(sf::Color::Black);
        button1.text.setPosition(button1.body.getPosition().x + button1.body.getGlobalBounds().width/2, button1.body.getPosition().y + button1.body.getGlobalBounds().height/2 - 15);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        title.draw(window);
        button1.draw(window);
        textBox1.drawTextBox(window);
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

        info.text.setString({"\„Splitter\" to aplikacja służąca do równomiernego podzia³u obowi¹zków\nwœród wspó³lokatorów. Pozwala na dodawanie domowychobowiązków\nwykonywanych przez u¿ytkowników. Posiada system punktowy motywuj¹cy\ndo systematycznej pracy. U¿ytkownik dostaje punkty \ ostosowane\ndo trudnoœci oraz poœwiêconego czasu na dane zadanie (np. za wyrzucenie\nœmieci czy rozwieszenie prania) . W ka¿dym miesi¹cu wspó³lokatorzy\npowinni otrzymaæ podobn¹ sumê punktów. Aktualny stan punktów mo¿na\nœledziæ w oknie „Ranking” jako tabelê oraz w formiewykresu."});
        info.setPosition(150, 200);

        button1.text.setString(L"Powrót");
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
    //setlocale(LC_ALL, "" );

    //zmienne
    ScreenLogOrReg logOrReg;
    ScreenLogin login;
    ScreenMainMenu mainMenu;
    ScreenAplikacji oAplikacji;

    //logOrReg.active = true;
    login.active = true;
    //mainMenu.active = true;


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
            else if (login.active == true)
            {
                if (event.type == sf::Event::MouseButtonPressed && login.textBox1.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    login.textBox1.isTyping = true;

                }
                else if (event.type == sf::Event::MouseButtonPressed && !login.textBox1.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    login.textBox1.isTyping = false;
                }

                if (event.type == sf::Event::TextEntered && login.textBox1.isTyping == true)
                {
                    login.textBox1.asciiCheck(static_cast<char>(event.text.unicode));
                }
            }

        }
        // clear the window with black color
        window.clear(sf::Color::Black);

        //rysowanie
        if (logOrReg.active == true) logOrReg.drawScreen(window);
        else if (login.active == true) login.drawScreen(window);
        else if (mainMenu.active == true) mainMenu.drawScreen(window);
        else if (oAplikacji.active == true) oAplikacji.drawScreen(window);

        window.display();
    }
    return 0;
}
