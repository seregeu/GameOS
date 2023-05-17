#ifndef __MYOS__GAME__PACMAN_H
#define __MYOS__GAME__PACMAN_H

#define Field_h 15
#define Field_l 41
#define scrLink_am 3
#define scrLink_len 30
#define lvlfile_h 99
#define lvlfile_l 12

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

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

    }
}
#endif