#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <locale.h> //do obslugi polskich znakow
#include <string>
#include <fstream>

using namespace std;

class User
{
public:
    string userName;
    string userPass;
    int points = 0;

    void save()
    {
        string temp;
        std::fstream file;
        file.open("konta.dat", std::ios::in);
        if (file.is_open()) {
            std::cout << "File was correctly opened!" << std::endl;
            std::string line;
            while(std::getline(file, line)) {
            //process a single line
                int pos;                                    // temporary variable for storing separator position

                pos = line.find(';');                       // find position of first spearator
                std::string fileUser = line.substr(0, pos);     // copy of a substring from position 0 to pos
                line = line.substr(pos+1, line.length());   // assign line with a substring without first element

                pos = line.find(';');
                std::string filePassword = line.substr(0, pos);

                std::string filePoints = line.substr(pos+1); // remaining, last element
                if(fileUser != userName)
                {
                    temp = temp + fileUser + ';' + filePassword + ';' + filePoints + '\n';
                }
                else
                {
                    temp = temp + userName + ';' + userPass + ';' + to_string(points) + '\n';
                }

            }
        }
        file.close();

        file.open("konta.dat", std::ios::out);
        if (file.is_open()) {
            std::cout << "File was correctly opened!" << std::endl;
            file << temp;
        }
        file.close();
    }
};

string szyfruj(string text)
{
	for(int i=0; i<text.length(); i++)
	{
	    if(text[i] + 5 == ';') text[i] = '-';
        else text[i] = text[i] + 5;
	}
	return text;
}

string deszyfruj(string text)
{
	for(int i=0; i<text.length(); i++)
	{

		if(text[i] == '-') text[i] = 54;
        else text[i] = text[i] - 5;
	}
	return text;
}

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
    string textString = "";

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
    Text login;
    Text password;
    Button button1; //powrót
    Button button2; //zaloguj sie
    TextBox textBox1;
    TextBox textBox2;
    bool active = false;


    ScreenLogin() : button1(200, 75, 540, 550, sf::Color::White), button2(200, 75, 540, 400, sf::Color::White), textBox1(500,200), textBox2(500,300)
    {
        title.setText("Zaloguj sie");
        title.setPosition(550, 5);

        login.setText("Login:");
        login.setPosition(550,150);

        password.setText("Haslo:");
        password.setPosition(550,260);

        button1.text.setString("Powrot");
        button1.text.setOrigin(button1.text.getGlobalBounds().width/2, button1.text.getGlobalBounds().height/2);
        button1.text.setFillColor(sf::Color::Black);
        button1.text.setPosition(button1.body.getPosition().x + button1.body.getGlobalBounds().width/2, button1.body.getPosition().y + button1.body.getGlobalBounds().height/2 - 15);

        button2.text.setString("Zaloguj sie");
        button2.text.setOrigin(button1.text.getGlobalBounds().width/2, button1.text.getGlobalBounds().height/2);
        button2.text.setFillColor(sf::Color::Black);
        button2.text.setPosition(button2.body.getPosition().x + button2.body.getGlobalBounds().width/2, button2.body.getPosition().y + button2.body.getGlobalBounds().height/2 - 15);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        title.draw(window);
        login.draw(window);
        password.draw(window);
        button1.draw(window);
        button2.draw(window);
        textBox1.drawTextBox(window);
        textBox2.drawTextBox(window);
    }
};

class ScreenRegistration
{
public:
    Text title;
    Text login;
    Text password;
    Button button1; //powrót
    Button button2; //zarejestruj sie
    TextBox textBox1;
    TextBox textBox2;
    bool active = false;


    ScreenRegistration() : button1(200, 75, 540, 550, sf::Color::White), button2(200, 75, 540, 400, sf::Color::White), textBox1(500,200), textBox2(500,300)
    {
        title.setText("Zarejestruj sie");
        title.setPosition(550, 5);

        login.setText("Login:");
        login.setPosition(550,150);

        password.setText("Haslo:");
        password.setPosition(550,260);

        button1.text.setString("Powrot");
        button1.text.setOrigin(button1.text.getGlobalBounds().width/2, button1.text.getGlobalBounds().height/2);
        button1.text.setFillColor(sf::Color::Black);
        button1.text.setPosition(button1.body.getPosition().x + button1.body.getGlobalBounds().width/2, button1.body.getPosition().y + button1.body.getGlobalBounds().height/2 - 15);

        button2.text.setString("Zarejestruj sie");
        button2.text.setOrigin(button1.text.getGlobalBounds().width/2, button1.text.getGlobalBounds().height/2);
        button2.text.setFillColor(sf::Color::Black);
        button2.text.setPosition(button2.body.getPosition().x + button2.body.getGlobalBounds().width/2, button2.body.getPosition().y + button2.body.getGlobalBounds().height/2 - 15);
    }

    void drawScreen(sf::RenderWindow &window)
    {
        title.draw(window);
        login.draw(window);
        password.draw(window);
        button1.draw(window);
        button2.draw(window);
        textBox1.drawTextBox(window);
        textBox2.drawTextBox(window);
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
    ScreenRegistration registration;
    ScreenMainMenu mainMenu;
    ScreenAplikacji oAplikacji;
    User user;

    //logOrReg.active = true;
    //login.active = true;
    registration.active = true;
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

                if (event.type == sf::Event::MouseButtonPressed && login.textBox2.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    login.textBox2.isTyping = true;

                }
                else if (event.type == sf::Event::MouseButtonPressed && !login.textBox2.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    login.textBox2.isTyping = false;
                }

                if (event.type == sf::Event::TextEntered && login.textBox2.isTyping == true)
                {
                    login.textBox2.asciiCheck(static_cast<char>(event.text.unicode));
                }

                if(event.type == sf::Event::MouseButtonPressed && login.button2.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    std::fstream file;
                    file.open("konta.dat", std::ios::in);
                    if (file.is_open()) {
                        std::cout << "File was correctly opened!" << std::endl;
                        std::string line;
                        while(std::getline(file, line)) {
                        //process a single line
                            int pos;                                    // temporary variable for storing separator position

                            pos = line.find(';');                       // find position of first spearator
                            std::string fileUser = line.substr(0, pos);     // copy of a substring from position 0 to pos
                            line = line.substr(pos+1, line.length());   // assign line with a substring without first element

                            pos = line.find(';');
                            std::string filePassword = line.substr(0, pos);
                            std::string filePoints = line.substr(pos+1); // remaining, last element

                            if(login.textBox1.textString == fileUser && login.textBox2.textString == filePassword)
                            {
                                user.userName = fileUser;
                                user.userPass = filePassword;
                                user.points = stoi(filePoints);
                                login.active = false;
                                mainMenu.active = true;
                            }
                        }
                    }
                    file.close();
                }

                if(event.type == sf::Event::MouseButtonPressed && login.button1.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    registration.active = true;
                    login.active = false;
                }
            }
            else if (registration.active == true)
            {
                if (event.type == sf::Event::MouseButtonPressed && registration.textBox1.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    registration.textBox1.isTyping = true;

                }
                else if (event.type == sf::Event::MouseButtonPressed && !registration.textBox1.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    registration.textBox1.isTyping = false;
                }

                if (event.type == sf::Event::TextEntered && registration.textBox1.isTyping == true)
                {
                    registration.textBox1.asciiCheck(static_cast<char>(event.text.unicode));
                }

                if (event.type == sf::Event::MouseButtonPressed && registration.textBox2.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    registration.textBox2.isTyping = true;

                }
                else if (event.type == sf::Event::MouseButtonPressed && !registration.textBox2.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    registration.textBox2.isTyping = false;
                }

                if (event.type == sf::Event::TextEntered && registration.textBox2.isTyping == true)
                {
                    registration.textBox2.asciiCheck(static_cast<char>(event.text.unicode));
                }

                if(event.type == sf::Event::MouseButtonPressed && registration.button2.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    bool czyIstnieje = false;
                    std::fstream file;
                    file.open("konta.dat", std::ios::in);
                    if (file.is_open()) {
                        std::cout << "File was correctly opened!" << std::endl;
                        std::string line;
                        while(std::getline(file, line)) {
                        //process a single line
                            int pos;                                    // temporary variable for storing separator position

                            pos = line.find(';');                       // find position of first spearator
                            std::string fileUser = line.substr(0, pos);     // copy of a substring from position 0 to pos
                            line = line.substr(pos+1, line.length());   // assign line with a substring without first element

                            pos = line.find(';');
                            std::string filePassword = line.substr(0, pos);

                            std::string filePoints = line.substr(pos+1); // remaining, last element

                            if(registration.textBox1.textString == fileUser)
                            {
                                std::cout << "Taki login juz istnieje." << std::endl;
                                czyIstnieje = true;
                                break;
                            }
                        }
                    }
                    file.close();

                    if(!czyIstnieje)
                    {
                        file.open("konta.dat", std::ios::app);
                        if (file.is_open()) {
                            std::cout << "File was correctly opened!" << std::endl;
                            file << registration.textBox1.textString << ";" << registration.textBox2.textString << ";0" << std::endl;
                            user.userName = registration.textBox1.textString;
                            user.userPass = registration.textBox2.textString;
                            user.points = 0;
                            registration.active = false;
                            mainMenu.active = true;
                        }
                        file.close();
                    }

                }

                if(event.type == sf::Event::MouseButtonPressed && registration.button1.body.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y))
                {
                    registration.active = false;
                    login.active = true;
                }
            }


        }
        // clear the window with black color
        window.clear(sf::Color::Black);

        //rysowanie
        if (logOrReg.active == true) logOrReg.drawScreen(window);
        else if (login.active == true) login.drawScreen(window);
        else if (registration.active == true) registration.drawScreen(window);
        else if (mainMenu.active == true) mainMenu.drawScreen(window);
        else if (oAplikacji.active == true) oAplikacji.drawScreen(window);

        window.display();
    }
    return 0;
}
