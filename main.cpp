#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <iostream>;
#include <string>;
#include <vector>;
#include <fstream>
#include <sstream>
#include <iomanip>
#include <nlohmann/json.hpp>
using json = nlohmann::json;


void displayJSON(const json& jsonData) {
    for (auto it = jsonData.begin(); it != jsonData.end(); ++it) {
        std::cout << "Key: " << it.key() << std::endl;

        if (it.value().is_object() || it.value().is_array()) {
            displayJSON(it.value());
        }
        else {
            std::cout << "Value: " << it.value() << std::endl;
        }
    }
}

void displayJSONData(sf::RenderWindow& window, const json& jsonData)
{
    sf::Font font;

    if (!font.loadFromFile("Condensed.ttf"))
    {
        std::cout << "Failed to load font" << std::endl;
        return;
    }

    sf::Text jsonText("", font, 16);
    jsonText.setPosition(10, 10);
    jsonText.setFillColor(sf::Color::White);

    std::stringstream ss;
    ss << std::setw(4) << jsonData.dump();

    std::string jsonString = "JSON Data :\n" + ss.str();

    jsonText.setString(jsonString);

    window.draw(jsonText);
}


class BaseEntityDatabase {
protected:


public:
    std::string filename;
    BaseEntityDatabase(const std::string& filename) : filename(filename) {}


    virtual void loadFromJSON() = 0;
    virtual void saveToJSON() = 0;
};
class ProductDatabase : public BaseEntityDatabase {
private:
    json jsonData; // Для хранения загруженных данных

public:
    ProductDatabase(const std::string& filename) : BaseEntityDatabase(filename) {}


    void loadFromJSON() override {
        std::ifstream file(filename);
        if (file.is_open()) {
            try {
                file >> jsonData; // Загружаем JSON из файла в переменную jsonData
                file.close();

                // Проход по массиву "products" в JSON и обработка данных
                for (const auto& product : jsonData["products"]) {
                    // Проверка наличия массива "hooks" в текущем элементе "product"
                    if (product["classification"].contains("hooks")) {
                        // Проход по элементам массива "hooks"
                        for (const auto& hook : product["classification"]["hooks"]) {
                            std::string productCode = hook["product_code"];
                            std::string productName = hook["name"];
                            // Дополнительная обработка данных из массива "hooks"
                        }
                    }
                }
                std::cout << "JSON data loaded successfully!" << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error while parsing JSON: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Unable to open file!" << std::endl;
        }
    }

    void saveToJSON() override {
        // Логика сохранения данных обычно подобна, но здесь нужно преобразовать ваши объекты обратно в JSON и записать их в файл.
        // Но этот код зависит от структуры ваших данных и того, как вы хотите сохранять данные в JSON.
        // Вам придется реализовать эту часть самостоятельно в зависимости от ваших требований.
        // Если нужно, могу помочь с конкретной логикой сохранения.
    }
};



struct Button
{
	std::string btnName;
	float widthBtn;
	float heightBtn;
	float xPosFrame;
	float yPosFrame;
	std::string imgPath;
	int xPosIcon;
	int yPosIcon;
};


class Application
{

private:
    std::vector<Button> btns;
    bool isLoggedIn = false;
    std::string login = "";
    std::string password = "";

public:
    Application()
    {
        initBtns();
    }

    void initBtns()
    {
        btns = {
          { "DB Products", 300.0f, 100.0f, 1.0f, 1.0f, "icons/products.png", 50, 30 },
          { "DB Clients", 300.0f, 100.0f, 1.0f, 100.0f, "icons/clients.png", 50, 130 },
          { "DB Employees", 300.0f, 100.0f, 1.0f, 200.0f, "icons/employees.png", 50, 230 },
          { "Sales Analysis", 300.0f, 100.0f, 1.0f, 300.0f, "icons/salesAnalysis.png", 50, 330 },
          { "Sending Email", 300.0f, 100.0f, 1.0f, 400.0f, "icons/mail.png", 50, 430 },
          { "Sales Manage", 300.0f, 100.0f, 1.0f, 500.0f, "icons/salesManagement.png", 50, 530 },
          { "Employee KPI", 300.0f, 100.0f, 1.0f, 600.0f, "icons/kpi.png", 50, 630 },
          { "Client Archive", 300.0f, 100.0f, 1.0f, 700.0f, "icons/workHistory.png", 50, 730 },
          { "Website", 300.0f, 100.0f, 1.0f, 800.0f, "icons/www.png", 50, 830 }
        };
    }


    void handleBtnClick(const sf::Vector2f& mousePos)
    {
        for (const auto& btn : btns)
        {
            sf::FloatRect btnBounds(btn.xPosFrame, btn.yPosFrame, btn.widthBtn, btn.heightBtn);
            if (btnBounds.contains(mousePos)) 
            {
                if (mousePos.x >= btn.xPosFrame && mousePos.x <= btn.xPosFrame + btn.widthBtn && mousePos.y >= btn.yPosFrame && mousePos.y <= btn.yPosFrame + btn.heightBtn && btn.btnName == "Website")
                {
                    std::system("start https://anfishka.github.io/management_system/web/index.html");
                    //break;
                }

                     sf::RenderWindow btnWindow(sf::VideoMode(400, 200), "Btn Clicked");
                sf::Text txt;
                sf::Font font;
                if (!font.loadFromFile("Condensed.ttf")) {
                    std::cout << "Failed to load font" << std::endl;
                    continue;
                }

                txt.setFont(font);
                txt.setString("Hello!\nClicked Btn: " + btn.btnName);
                txt.setCharacterSize(24);
                txt.setFillColor(sf::Color::Black);
                txt.setPosition(50, 50);

                while (btnWindow.isOpen())
                {
                    sf::Event event;
                    while (btnWindow.pollEvent(event))
                    {
                        if (event.type == sf::Event::Closed)
                        {
                            btnWindow.close();
                        }
                    }
                    btnWindow.clear(sf::Color::White);
                    btnWindow.draw(txt);
                    btnWindow.display();
                }

            }
        }
    }







    void renderBtns(sf::RenderWindow& window)
    {

        float blueHeight = window.getSize().x * 0.25f;

        sf::RectangleShape blueBg(sf::Vector2f(blueHeight, window.getSize().y));
        blueBg.setFillColor(sf::Color(116, 182, 255));

        window.draw(blueBg);


        sf::Texture texture;

        if (!texture.loadFromFile("bgFish.jpg"))
        {
            std::cout << "Failed" << std::endl;
            return;
        }

        sf::Sprite sprite(texture);



        sprite.setScale(0.6, 0.6);
        sprite.setPosition(300, 1);
        sprite.setScale(0.6, 0.6);
        window.draw(sprite);

        for (const auto& btn : btns)
        {
            sf::RectangleShape btnFrame(sf::Vector2f(btn.widthBtn, btn.heightBtn));
            btnFrame.setPosition(btn.xPosFrame, btn.yPosFrame);
            btnFrame.setFillColor(sf::Color(55, 125, 255));
            btnFrame.setOutlineColor(sf::Color::White);
            btnFrame.setOutlineThickness(2.f);
            window.draw(btnFrame);

            sf::Texture texture;
            if (!texture.loadFromFile(btn.imgPath)) {
                std::cout << "Failed to load button image" << std::endl;
                continue;
            }

            sf::Sprite sprite(texture);
            sprite.setScale(0.6, 0.6);
            sprite.setPosition(btn.xPosIcon, btn.yPosIcon);
            window.draw(sprite);

            sf::Font font;
            if (!font.loadFromFile("Condensed.ttf")) {
                std::cout << "Failed to load font" << std::endl;
                continue;
            }

            sf::Text btnTxt;
            btnTxt.setFont(font);
            btnTxt.setString(btn.btnName);
            btnTxt.setCharacterSize(24);
            btnTxt.setFillColor(sf::Color::Black);
            sf::FloatRect textRect = btnTxt.getLocalBounds();
            btnTxt.setOrigin(textRect.left + textRect.width / 2.0f,
                textRect.top + textRect.height / 2.0f);
            btnTxt.setPosition(btn.xPosFrame + btn.widthBtn / 2.0f, btn.yPosFrame + btn.heightBtn / 2.0f);
            window.draw(btnTxt);
        }
    };



    bool authenticateUser(const std::string& username, const std::string& pass)
    {
        return (username == "admin" && pass == "admin");
    }

    void renderAuthenticationWindow(sf::RenderWindow& window)
    {
        sf::Texture texture;

        if (!texture.loadFromFile("bg5.jpg"))
        {
            std::cout << "Failed to load img" << std::endl;
            return;
        }
        sf::Sprite sprite(texture);
        sprite.setPosition(1, 1);
        sprite.setScale(0.25, 0.25);

        sf::Font font;
        if (!font.loadFromFile("Condensed.ttf"))
        {
            std::cout << "Failed to load font";
        }

        sf::Text loginLabel("Login: ", font, 34);
        loginLabel.setPosition(900, 200);
        loginLabel.setFillColor(sf::Color::Blue);

        sf::RectangleShape loginField(sf::Vector2f(200, 30));
        loginField.setPosition(900, 250);
        loginField.setFillColor(sf::Color::White);
        loginField.setOutlineColor(sf::Color::Blue);
        loginField.setOutlineThickness(1);

        sf::Text passwordLabel("Password: ", font, 34);
        passwordLabel.setPosition(900, 350);
        passwordLabel.setFillColor(sf::Color::Blue);

        sf::RectangleShape passwordField(sf::Vector2f(200, 30));
        passwordField.setPosition(900, 400);
        passwordField.setFillColor(sf::Color::White);
        passwordField.setOutlineColor(sf::Color::Blue);
        passwordField.setOutlineThickness(1);

        sf::Text loginText("", font, 24);
        loginText.setPosition(910, 253);
        loginText.setFillColor(sf::Color::Black);

        sf::Text passwordText("", font, 24);
        passwordText.setPosition(910, 403);
        passwordText.setFillColor(sf::Color::Black);

        sf::RectangleShape btnLogIn(sf::Vector2f(200, 50));
        btnLogIn.setPosition(900, 500);
        btnLogIn.setFillColor(sf::Color(116, 182, 255));
        btnLogIn.setOutlineThickness(1);

        sf::Text btnLogInTxt("LogIn", font, 34);
        btnLogInTxt.setPosition(970, 500);
        btnLogInTxt.setFillColor(sf::Color::White);

        bool loginFieldActive = false;
        bool passwordFieldActive = false;
        bool isAuthCompleted = false;

        while (window.isOpen() && !isLoggedIn) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }

                if (event.type == sf::Event::MouseButtonPressed) {
                    int mouseX = sf::Mouse::getPosition(window).x;
                    int mouseY = sf::Mouse::getPosition(window).y;

                    if (loginField.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
                        loginFieldActive = true;
                        passwordFieldActive = false;
                    }
                    else if (passwordField.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY))) {
                        loginFieldActive = false;
                        passwordFieldActive = true;
                    }
                    else {
                        loginFieldActive = false;
                        passwordFieldActive = false;
                    }
                }

                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        if (loginFieldActive && event.text.unicode != '\b' && login.size() < 25) {
                            login += static_cast<char>(event.text.unicode);
                            loginText.setString(login);
                            std::cout << "Login entered: " << login << std::endl;
                        }
                        else if (passwordFieldActive && event.text.unicode != '\b' && password.size() < 25) {
                            password += static_cast<char>(event.text.unicode);
                            passwordText.setString(password);
                            std::cout << "Password entered: " << password << std::endl;
                        }
                        else if (event.text.unicode == '\b') {
                            if (loginFieldActive && !login.empty()) {
                                login.pop_back();
                                loginText.setString(login);
                            }
                            else if (passwordFieldActive && !password.empty()) {
                                password.pop_back();
                                passwordText.setString(password);
                            }
                        }
                    }
                }
            }

            int mouseX = sf::Mouse::getPosition(window).x;
            int mouseY = sf::Mouse::getPosition(window).y;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                if (btnLogIn.getGlobalBounds().contains(static_cast<float>(mouseX), static_cast<float>(mouseY)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                    if (authenticateUser(login, password)) {
                        isLoggedIn = true;
                        isAuthCompleted = true;
                    }
                    else {
                        std::cout << "Authentication failed. Please try again." << std::endl;
                        login.clear();
                        password.clear();
                    }
                }
            }

            window.clear(sf::Color::White);
            window.draw(sprite);
            window.draw(loginLabel);
            window.draw(loginField);
            window.draw(loginText);
            window.draw(passwordLabel);
            window.draw(passwordField);
            window.draw(passwordText);
            window.draw(btnLogIn);
            window.draw(btnLogInTxt);
            window.display();
        }
    }

  
        void run()
    {
        sf::RenderWindow window(sf::VideoMode(1400, 1000), "FishBiz Navigator");
        renderAuthenticationWindow(window);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                if (event.type == sf::Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == sf::Mouse::Left)
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::Vector2f translatedPos = window.mapPixelToCoords(mousePos);
                        handleBtnClick(translatedPos);
                    
                    }
                }
            }

            window.clear(sf::Color::White);

            if (isLoggedIn)
            {
                renderBtns(window);
            }

            window.display();
        }
    }


};





int main()
{
    Application app;
      app.run();

     // ProductDatabase productDB("products.json");
      //productDB.loadFromJSON(); 

   /*   std::ifstream file("products.json");
      if (file.is_open()) {
          try {
              json jsonData;
              file >> jsonData; 
              file.close();

              std::cout << std::setw(4) << jsonData << std::endl; 

              std::cout << "JSON data loaded successfully!" << std::endl;
          }
          catch (const std::exception& e) {
              std::cerr << "Error while parsing JSON: " << e.what() << std::endl;
          }
      }
      else {
          std::cerr << "Unable to open file!" << std::endl;
      }
      */



  //  sf::RenderWindow window(sf::VideoMode(800, 600), "json");

    json jsonData = {
          {"key1", "value1"},
          {"key2", 42}
          // ... add your JSON data here
    };
    /*
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))

        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
        }
        window.clear(sf::Color::Black);
   
        window.display();
        
    }

*/
    return 0;
}



//    displayJSONData(window, jsonData);



class ClientDatabase : public BaseEntityDatabase
{ 
private:
	
public: 
	void loadFromJSON() override
	{ 
	}
	void saveToJSON() override 
	{ 	
	} 
	
}; 
class EmployeeDatabase : public BaseEntityDatabase 
{ 
private: 
	
public: 
	void loadFromJSON() override 
	{ 
	} 
	void saveToJSON() override 
	{ 	
	} 
	
};





