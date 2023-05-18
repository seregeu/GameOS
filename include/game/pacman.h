#ifndef __MYOS__GAME__PACMAN_H
#define __MYOS__GAME__PACMAN_H

#define COUNT_GHOST 4
#define HEIGH 22
#define WIDTH 35
#define GHOST 234 
#define PACMAN 233 
#define COIN 157
#define TIME_SLEEP 30
#define TIME_WITHOUT_DEATH 20
#define MAX_COUNT_COIN 4
#define MAX_TIMELIFE_COIN 60
#define MIN_TIMELIFE_COIN 20
#define TIME_CHASE 60

#include <gui/widget.h>
#include <common/graphicscontext.h>



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
        private:
            common::GraphicsContext* gc;
        };

        class Position
        {
        public:
            Position(){};
            void SetPosition(common::uint32_t x, common::uint32_t y);
            common::uint32_t GetPosX() ;
            common::uint32_t GetPosY() ;
            ~Position(){};
        private:
            common::uint32_t a_pos_x_, a_pos_y_;
        };

        

    }
}
#endif