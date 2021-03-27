#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int score_player_1 = 0; //gracz 1 po lewej
int score_player_2 = 0; //gracz 2 po prawej

bool intersects(sf::CircleShape& cir, sf::RectangleShape& rect) //circleshape, kształt koła, kształt prostokąta
{
    sf::FloatRect circle = cir.getGlobalBounds(); //koło ograniczające obiekt // floatrect ustawia na 0,0(wysokość, szerokość)
    sf::FloatRect rectangle = rect.getGlobalBounds(); //prostokąt ograniczający obiekt

    return circle.intersects(rectangle); //krzyżowanie się piłki ze stołem // piłka może przechodzić przez prostokąt
}

int main()
{

    sf::VideoMode video_mode(600, 500); //określanie rozmiaru nowego okna wideo (width, height, bpp -> bits per pixel)
    sf::RenderWindow window(video_mode, "PONG"); //dzięki funkcji możemy rysować 2d po planszy //tworzenie okna

    sf::CircleShape Ball;
    Ball.setFillColor(sf::Color::White);
    Ball.setOutlineColor(sf::Color::Black); //red, green, blue, alpha
    Ball.setRadius(10);
    Ball.setPosition(300, 265); //(width,height) //ustawienie wstępnej pozycji obu graczy 

    sf::RectangleShape firstPlayer;
    firstPlayer.setFillColor(sf::Color(139, 49, 225));
    firstPlayer.setSize(sf::Vector2f(10, 50)); //vector2f do zapisywania pozycji / prędkości / przyspieszenia -> float
    firstPlayer.setPosition(30, 250);

    sf::RectangleShape secondPlayer;
    secondPlayer.setFillColor(sf::Color::Blue);
    secondPlayer.setSize(sf::Vector2f(10, 50));
    secondPlayer.setPosition(570, 250);

    sf::RectangleShape outleft;
    outleft.setFillColor(sf::Color::Cyan);
    outleft.setSize(sf::Vector2f(10, 500));
    outleft.setPosition(0, 0);

    sf::RectangleShape outright;
    outright.setFillColor(sf::Color::Cyan);
    outright.setSize(sf::Vector2f(10, 500));
    outright.setPosition(590, 0);

    sf::RectangleShape mid;
    mid.setFillColor(sf::Color(0, 255, 255, 30));
    mid.setSize(sf::Vector2f(20, 480));
    mid.setPosition(300, 0);

    sf::RectangleShape kreska;
    kreska.setFillColor(sf::Color(0, 255, 255, 30));
    kreska.setSize(sf::Vector2f(20, 600));
    kreska.setPosition(600, 80);
    kreska.rotate(90);

    sf::RectangleShape up;
    up.setFillColor(sf::Color::Black);
    up.setSize(sf::Vector2f(100, 600));
    up.setPosition(600, 0);
    up.rotate(90); //zakres(pierwszy,ostatni)

    sf::RectangleShape down;
    down.setFillColor(sf::Color(0, 255, 255, 30));
    down.setSize(sf::Vector2f(20, 600));
    down.setPosition(600, 480);
    down.rotate(90);

    

    sf::Font font;
    if (!font.loadFromFile("slkscr.ttf"))
    {
        return EXIT_FAILURE;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Koles jeden \n points: " + std::to_string(score_player_1));
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::Cyan);
    text.setStyle(sf::Text::Bold);
    text.setPosition(75, 15);

    sf::Text text2;
    text2.setFont(font);
    text2.setString("Koles dwa \n points: " + std::to_string(score_player_2));
    text2.setCharacterSize(25);
    text2.setFillColor(sf::Color::Cyan);
    text2.setStyle(sf::Text::Bold);
    text2.setPosition(365, 15);

    sf::Font font2;
    if (!font2.loadFromFile("ka1.ttf"))
    {
        return EXIT_FAILURE;
    }

    sf::Text wygranko;
    wygranko.setFont(font2);
    wygranko.setCharacterSize(50);
    wygranko.setPosition(70, 200);
    wygranko.setFillColor(sf::Color::White);

    sf::Text pauza;
    pauza.setFont(font2);
    pauza.setCharacterSize(50);
    pauza.setPosition(70, 200);
    pauza.setFillColor(sf::Color::White);

    sf::Music music;
    if (!music.openFromFile("03-Pink-Plant-Woods-Area-1.ogg"))
        return -1;
    music.setVolume(50);
    music.play();
    music.setLoop(true);

    sf::Vector2<float>ballSpeed(0.05, 0.05); //określenie szybkości piłki


    while (window.isOpen()) {
        window.clear(sf::Color::Black); //red,green,blue //wypełni resztę obszaru(tego bez kwadratów)
        window.draw(mid); //wyrysowywanie wszystkich obiektów w otwartym oknie
        window.draw(Ball);
        window.draw(secondPlayer);
        window.draw(down);
        window.draw(up);
        window.draw(kreska);
        window.draw(firstPlayer);
        window.draw(outleft);
        window.draw(outright);
        window.draw(text);
        window.draw(text2);
        window.draw(wygranko);
        window.draw(pauza);



        window.display(); //do inicjalizacji obiektów powyżej

        sf::Event event; //poruszenia zdarzenia
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) { //pierwszy gracz
            firstPlayer.move(0, -0.1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            firstPlayer.move(0, 0.1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { //drugi gracz
            secondPlayer.move(0, -0.1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            secondPlayer.move(0, 0.1);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        {
            music.stop();
            window.close();
            score_player_1 = 0; 
            score_player_2 = 0;
            main();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            window.waitEvent(event);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        if (intersects(Ball, outright)) { //liczenie punktów gracz pierwszy
            score_player_1++;
            if (score_player_1 == 10)
            {
                wygranko.setString("Koles jeden \n ma wygranko");
                ballSpeed.x = 0;
                ballSpeed.y = 0;
                Ball.setFillColor(sf::Color(0, 0, 0, 0));
                
            }
            Ball.setPosition(300, 250);
            text.setString("Koles jeden \n points: " + std::to_string(score_player_1));
        }
        if (intersects(Ball, outleft)) { //liczenie punktów gracz drugi
            score_player_2++;
            if (score_player_2 == 10)
            {
                wygranko.setString("Koles dwa \n ma wygranko");
                ballSpeed.x = 0;
                ballSpeed.y = 0;
                Ball.setFillColor(sf::Color(0, 0, 0, 0));
                
            }
            Ball.setPosition(300, 265);
            text2.setString("Koles dwa \n points: " + std::to_string(score_player_2));
        }
        if (intersects(Ball, up) || (intersects(Ball, down))) {
            ballSpeed.y = -ballSpeed.y; //na odwrót się odbija
        }
        if (intersects(Ball, firstPlayer) || (intersects(Ball, secondPlayer))) {
            ballSpeed.x = -ballSpeed.x; //zmiana kierunku prawo lewo
        }
        Ball.move(ballSpeed.x, ballSpeed.y); // ustawianie początkowego wektora kierunku

    }

}