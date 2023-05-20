#include <game/pacman.h>
#include <common/random.h>
#include <drivers/timer.h>
#include <gui/menu.h>

using namespace myos;
using namespace myos::gui;
using namespace myos::game;
using namespace myos::common;
using namespace myos::drivers;


extern uint64_t tick;

PacmanGame::PacmanGame(Widget* parent,
                int32_t x, int32_t y, int32_t w, int32_t h,
                uint8_t r, uint8_t g, uint8_t b)
:  CompositeWidget(parent, x, y, w, h, r, g, b){

    // Инициализация генератора случайных чисел
    //srand(time(0));
    for (int i = 0; i < MAP_HEIGHT; i++) {
    for (int j = 0; j < MAP_WIDTH; j++) {
        map[i][j] = ' ';
    }
}

// Инициализация карты
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == 0 || i == MAP_HEIGHT - 1 || j == 0 || j == MAP_WIDTH -1 || (i % 2 == 0 && j % 2 == 0)) {
                map[i][j] = WALL;
            }
            else {
                map[i][j] = COIN;
                coinCount++;
            }
        }
        map[i][MAP_WIDTH] = '\0';  // Добавляем нуль в конец строки
    }


    // Инициализация координат Пакмана
    pacmanX = 1;
    pacmanY = 1;
    map[pacmanY][pacmanX] = PACMAN;

    // Инициализация координат монстра
    monsterX = MAP_WIDTH - 2;
    monsterY = MAP_HEIGHT - 2;
    map[monsterY][monsterX] = MONSTER;

    // Начальное направление движения Пакмана
    dx = 1;
    dy = 0;

    prevMonsterItem = '.';
};

void PacmanGame::drawMap(){
    for (int i = 0; i < MAP_HEIGHT; i++) {
    		gc->DrawString(map[i], 0, i*8, 0xFF, 0xFF, 0xFF);
	}	
}

PacmanGame::~PacmanGame(){};

void PacmanGame::Draw(common::GraphicsContext* gc){
    CompositeWidget::Draw(gc);
    this->gc = gc;
    drawMap();
    movePacman();
    moveMonster();
    checkCollision();
};

void PacmanGame::OnKeyDown(char c) {	
    switch (c) {
            case 'w':
                dx = 0;
                dy = -1;  // Вверх
                break;
            case 's':
                dx = 0;
                dy = 1;  // Вниз
                break;
            case 'a':
                dx = -1;
                dy = 0;  // Влево
                break;
            case 'd':
                dx = 1;
                dy = 0;  // Вправо
                break;
            }
};

void PacmanGame::GetBackgroudColor(common::uint8_t& r, common::uint8_t& g, common::uint8_t& b){};

void PacmanGame::movePacman() {
    // Проверяем, можно ли переместить Пакмана в новое положение
    int newPacmanX = pacmanX + dx;
    int newPacmanY = pacmanY + dy;
    if (newPacmanX >= 0 && newPacmanX < MAP_WIDTH && newPacmanY >= 0 && newPacmanY < MAP_HEIGHT &&
        map[newPacmanY][newPacmanX] != WALL) {
        // Обновляем координаты Пакмана
        map[pacmanY][pacmanX] = ' ';
        pacmanX = newPacmanX;
        pacmanY = newPacmanY;
        if (map[pacmanY][pacmanX] == COIN) {
            coinCount--;
        }
        map[pacmanY][pacmanX] = PACMAN;
    }
}

int PacmanGame::abs(int num) {
    return (num >= 0) ? num : -num;
}

void PacmanGame::moveMonster() {
    RandomGenerator rand(abs(pacmanX - monsterX));
    // Вычисляем разницу между координатами монстра и Пакмана по каждой оси
    int randomFactor = rand.Generate();
    int randomOffset = (randomFactor % 4 == 2) ? rand.Generate() : 0;

    int dx = pacmanX - monsterX + randomOffset;
    int dy = pacmanY - monsterY;

    // Выбираем направление, куда нужно двигаться монстру
    int newMonsterX = monsterX;
    int newMonsterY = monsterY;

    // Проверяем разницу по горизонтали и вертикали
    if (abs(dx) > abs(dy) && map[newMonsterY][monsterX + (dx > 0 ? 1 : -1)] != WALL) {
        // Движение по горизонтали
        newMonsterX = monsterX + (dx > 0 ? 1 : -1);
    } else {
        // Движение по вертикали
        newMonsterY = monsterY + (dy > 0 ? 1 : -1);
    }

    // Проверяем, можно ли переместить монстра в новое положение
    if (newMonsterX >= 0 && newMonsterX < MAP_WIDTH && newMonsterY >= 0 && newMonsterY < MAP_HEIGHT &&
        map[newMonsterY][newMonsterX] != WALL) {
        // Обновляем координаты монстра
        map[monsterY][monsterX] = prevMonsterItem;
        monsterX = newMonsterX;
        monsterY = newMonsterY;
    }

    // Обновляем координаты монстра на карте
    if (map[monsterY][monsterX] != MONSTER) {
        prevMonsterItem = map[monsterY][monsterX];
    }
    map[monsterY][monsterX] = MONSTER;
}

void PacmanGame::checkCollision() {
    // Проверяем столкновение с монстром
    if (pacmanX == monsterX && pacmanY == monsterY) {
            ShowLooseScreen();
    }
}

void PacmanGame::checkWin() {
    // Проверяем, остались ли еще монеты на карте
    if (coinCount == 0) {
        ShowWinScreen();
    }
}

void PacmanGame::run() {
}

void PacmanGame::ShowWinScreen()
{
    ((CompositeWidget*)this->parent)->DeleteChild(this);

    Widget* win = new WinScreen(this->parent, 0, 0, w, h, 0x00, 0xA8, 0x00);
    ((CompositeWidget*)this->parent)->AddChild(win);
    ((CompositeWidget*)this->parent)->GetFocus(win);
}

WinScreen::WinScreen(gui::Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b)
: Widget(parent, x, y, w, h, r, g, b)
{

}

WinScreen::~WinScreen()
{
}

void WinScreen::Draw(common::GraphicsContext* gc)
{
    Widget::Draw(gc);

    gc->DrawString("You win!", w/2 - 30, h/2, 0xFF, 0xFF, 0xFF);
}

void WinScreen::OnKeyDown(char c)
{
}



void PacmanGame::ShowLooseScreen()
{
    ((CompositeWidget*)this->parent)->DeleteChild(this);

    Widget* Loose = new LooseScreen(this->parent, 0, 0, w, h, 0xA8, 0x00, 0x00);
    ((CompositeWidget*)this->parent)->AddChild(Loose);
    ((CompositeWidget*)this->parent)->GetFocus(Loose);
}

LooseScreen::LooseScreen(gui::Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b)
: Widget(parent, x, y, w, h, r, g, b)
{

}

LooseScreen::~LooseScreen()
{
}

void LooseScreen::Draw(common::GraphicsContext* gc)
{
    Widget::Draw(gc);

    gc->DrawString("You Loose!", w/2 - 30, h/2, 0xFF, 0xFF, 0xFF);
}

void LooseScreen::OnKeyDown(char c)
{
}