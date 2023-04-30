#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

int main() {
  setlocale(LC_ALL, "");  // Поддержка кириллицы в консоли Windows
  IpAddress ip = IpAddress::getLocalAddress();  // Локальный ip Адресс
  TcpSocket socket;  // программный интерфейс для обеспечения обмена данными
                     // между процессами
  Packet packet;  // Для осуществления пакетной передачи дынных
  char type;
  char mode = ' ';  // Мод s- сервер, с - клиент
  int x = 0;        // координаты шара
  int y = 0;
  char buffer[2000];
  size_t received;  //??
  string text = "connect to: ";

  //***********Подключение***************//
  cout << ip << endl;
  cout << "Введите тип подключения:  c -клиент, s -сервер" << endl;
  cin >> type;
  if (type == 's') {
    TcpListener listener;
    listener.listen(2000);
    listener.accept(socket);  // который будет содержать новое соединение
    text += "Serwer";
    mode = 's';

  } else if (type == 'c') {
    cout << "new ip:";
    cin >> ip;

    socket.connect(ip, 2000);  // ip и Порт
    text += "client";
    mode = 'r';
  }
  socket.send(text.c_str(), text.length() + 1);
  socket.receive(buffer, sizeof(buffer), received);
  cout << buffer << endl;

  //**********Отрисовка Формы***********************//
  RenderWindow window(sf::VideoMode(800, 600),
                      "Network");  // Создаем размер Главного окна
  //*******Элементы********************//
  CircleShape shape(10);  // создаем шар с радиусом 50

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    if (mode == 's') {
      socket.receive(packet);  // Команда которая ожидает данных в виде пакета
                               // от клиентской части
      if (packet >> x >> y) {  // вытаскиваем значение из пакета в переменную x
                               // и у (действие уже происходит)
        cout << x << ":" << y
             << endl;  //..и если все прошло успешно то выводим её координаты
      }
    }

    if (mode == 'r') {
      if (Keyboard::isKeyPressed(
              Keyboard::Right)) {  // первая координата Х отрицательна =>идём
                                   // влево
        x++;
      }
      if (Keyboard::isKeyPressed(
              Keyboard::Left)) {  // первая координата Х отрицательна =>идём
                                  // влево
        x--;
      }

      if (Keyboard::isKeyPressed(
              Keyboard::Down)) {  // первая координата Х отрицательна =>идём
                                  // влево
        y++;
      }
      if (Keyboard::isKeyPressed(
              Keyboard::Up)) {  // первая координата Х отрицательна =>идём влево
        y--;
      }

      packet << x << y;  // Пакуем значения координат в Пакет
      socket.send(packet);  // Отправка данных
      packet.clear();       // Чистим пакет
    }
    window.clear();
    shape.setPosition(x, y);  // выставляем шар на координаты
    window.draw(shape);  // отрисовываем шар
    window.display();
    sleep(sf::milliseconds(10));  // Задержка
  }                               // END

  return 0;
}
