#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <ctime>

class Button {
public:
    sf::RectangleShape shape;
    sf::Text text;
    bool isVisible;
    sf::Vector2f size;
    sf::Vector2f windowSize;

    Button(const sf::Font& font, const std::string& btnText,
           const sf::Vector2f& position, const sf::Vector2f& btnSize,
           const sf::Vector2f& winSize) {
        size = btnSize;
        windowSize = winSize;

        shape.setSize(size);
        shape.setFillColor(sf::Color(100, 150, 200));
        shape.setOutlineColor(sf::Color::White);
        shape.setOutlineThickness(2);

        // origin смещается в центр для удобного позиционирования
        shape.setOrigin(size.x / 2, size.y / 2);
        shape.setPosition(position);

        text.setFont(font);
        text.setString(btnText);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);

        //
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.left + textBounds.width / 2,
                      textBounds.top + textBounds.height / 2);
        text.setPosition(position);

        isVisible = true;
    }

    bool cover(const sf::Vector2f& mousePos) {
        if (!isVisible) return false;
        return shape.getGlobalBounds().contains(mousePos);
    }

    bool click(const sf::Vector2f& mousePos) {
        if (!isVisible) return false;
        return shape.getGlobalBounds().contains(mousePos);
    }

    void move_random() {
        if (!isVisible) return;
        //static для однократной инициализации генератора
        static std::mt19937 rng(static_cast<unsigned>(std::time(nullptr)));
        // границы с учётом half-size чтобы кнопка не выходила за края
        std::uniform_real_distribution<float> distX(size.x / 2, windowSize.x - size.x / 2);
        std::uniform_real_distribution<float> distY(size.y / 2, windowSize.y - size.y / 2);

        float newX = distX(rng);
        float newY = distY(rng);

        shape.setPosition(newX, newY);
        text.setPosition(newX, newY);
    }

    void draw(sf::RenderWindow& window) {
        if (isVisible) {
            window.draw(shape);
            window.draw(text);
        }
    }
};

int main() {
    const unsigned int WINDOW_WIDTH = 800;
    const unsigned int WINDOW_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Убегающая кнопка");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
            std::cerr << "шрифт ааоаоаоаоаоаоаоао" << std::endl;
            return -1;
        }
    }

    sf::Vector2f buttonSize(120, 60);
    Button button(font, "START",
                  sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2),
                  buttonSize,
                  sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));

    sf::Text winText;
    winText.setFont(font);
    winText.setString("!Z YOU WON Z!");
    winText.setCharacterSize(48);
    winText.setFillColor(sf::Color::Green);
    winText.setStyle(sf::Text::Bold);

    sf::FloatRect winTextBounds = winText.getLocalBounds();
    winText.setOrigin(winTextBounds.left + winTextBounds.width / 2,
                      winTextBounds.top + winTextBounds.height / 2);
    winText.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    bool wasHovered = false;

    while (window.isOpen()) {
        sf::Event event;

        //mapPixelToCoords для корректного преобразования при измененном view
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        bool isHovered = button.cover(mousePos);

        // реагируем только на момент начала наведения, а не постоянное нахождение
        if (isHovered && !wasHovered) {
            button.move_random();
            // добавил задержку тк были баги при резких движениях мыши
            sf::sleep(sf::milliseconds(50));
        }

        wasHovered = isHovered;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // используем координаты из события для точности
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        sf::Vector2i(event.mouseButton.x, event.mouseButton.y));

                    if (button.click(mousePos)) {
                        button.isVisible = false;
                        std::cout << "!Z YOU WON Z!" << std::endl;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        window.clear(sf::Color(40, 40, 50));

        button.draw(window);

        if (!button.isVisible) {
            window.draw(winText);
        }

        window.display();
    }

    return 0;
}