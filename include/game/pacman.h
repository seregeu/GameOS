#ifndef __MYOS__GAME__PACMAN_H
#define __MYOS__GAME__PACMAN_H

#include <gui/widget.h>
#include <common/graphicscontext.h>

#define COIN '.'
#define PACMAN 'P'
#define WALL '#'
#define MONSTER 'M'




namespace myos
{
    namespace game
    {

        class PacmanGame : public gui::CompositeWidget
        {
        public:
            PacmanGame(gui::Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b);
            ~PacmanGame();

            void Draw(common::GraphicsContext* gc);

            void GetBackgroudColor(common::uint8_t& r, common::uint8_t& g, common::uint8_t& b);

            void OnKeyDown(char c);

            PacmanGame();  // Конструктор класса

            void run();  // Метод для запуска игры
        private:
            common::GraphicsContext* gc;
            static const int MAP_WIDTH = 19;
            static const int MAP_HEIGHT = 15;
            char prevMonsterItem = '.';

            char map[MAP_HEIGHT][MAP_WIDTH+1];
            int pacmanX, pacmanY;
            int monsterX, monsterY;
            int coinCount;
            int dx, dy;  // Направление движения Пакмана
            int abs(int num);

            void drawMap();
            void movePacman();
            void moveMonster();
            void checkCollision();
            void checkWin();
            void ShowWinScreen();
            void ShowLooseScreen();
        };

        class WinScreen : public gui::Widget
        {
        public:
            WinScreen(gui::Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b);

            ~WinScreen();

            void Draw(common::GraphicsContext* gc);

            void OnKeyDown(char c);
        };

        class LooseScreen : public gui::Widget
        {
        public:
            LooseScreen(gui::Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b);

            ~LooseScreen();

            void Draw(common::GraphicsContext* gc);

            void OnKeyDown(char c);
        };
    }
}
#endif