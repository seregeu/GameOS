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
    :  CompositeWidget(parent, x, y, w, h, r, g, b){};

    PacmanGame::~PacmanGame(){};

    void PacmanGame::Draw(common::GraphicsContext* gc){
		CompositeWidget::Draw(gc);
		this->gc = gc;
		//gc->DrawString("Win!", w/2 - 16, h/2, 0xFF, 0xFF, 0xFF);
	};

    void PacmanGame::OnKeyDown(char c)
	{	}

    void PacmanGame::GetBackgroudColor(common::uint8_t& r, common::uint8_t& g, common::uint8_t& b){};

    void Position::SetPosition(common::uint32_t x, common::uint32_t y)
    {
        a_pos_x_ = x;
        a_pos_y_ = y;
    }

    common::uint32_t Position::GetPosX()
    {
        return a_pos_x_;
    }

    common::uint32_t Position::GetPosY()
    {
        return a_pos_y_;
    }

    
