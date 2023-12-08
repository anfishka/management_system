#include <SFML/Graphics.hpp>
#include <iostream>;
#include <string>;
#include <vector>;

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
	std::string login = "a";
	std::string password = "b";

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
		return (username == login && pass == this->password);
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


		while (window.isOpen() && !isAuthCompleted) {
			sf::Event event;
			sf::Vector2f mousePosFloat;
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}

				if (event.type == sf::Event::MouseButtonPressed) {

					std::cout << "sf::Mouse::getPosition(window)" << sf::Mouse::getPosition(window).x << sf::Mouse::getPosition(window).y << std::endl;

					sf::Vector2i mousePos = sf::Mouse::getPosition(window);
					mousePosFloat = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

					if (loginField.getGlobalBounds().contains(mousePosFloat)) {
						loginFieldActive = true;
						passwordFieldActive = false;
					}
					else if (passwordField.getGlobalBounds().contains(mousePosFloat)) {
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
							std::cout << "Login entered: " << login << std::endl; // Вывод введенного логина в консоль

						}
						else if (passwordFieldActive && event.text.unicode != '\b' && password.size() < 25) {
							password += static_cast<char>(event.text.unicode);
							passwordText.setString(password); // Обновление текста в поле для пароля

							std::cout << "Password entered: " << password << std::endl; // Вывод введенного пароля в консоль

						}
					}
					if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::TextEntered) {
						if (event.type == sf::Event::MouseButtonPressed) {
						
							sf::Vector2i mousePos = sf::Mouse::getPosition(window);
							mousePosFloat = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
						}

						if (btnLogIn.getGlobalBounds().contains(mousePosFloat) || event.text.unicode == 13) {
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

			window.clear(sf::Color::White);
			renderBtns(window);
			window.display();

			/*if (!isLoggedIn)
			{
				renderAuthenticationWindow(window);
			}
			else
			{
				renderBtns(window);
			}*/
			
			renderBtns(window);
		}
	}


};


int main()
{
	Application app;
	app.run();

	return 0;
}











