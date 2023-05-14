#include <game/socoban.h>
#include <common/random.h>
#include <drivers/timer.h>
#include <gui/menu.h>

using namespace myos;
using namespace myos::gui;
using namespace myos::game;
using namespace myos::common;
using namespace myos::drivers;


extern uint64_t tick;


    SocobanGame::SocobanGame(Widget* parent,
                   int32_t x, int32_t y, int32_t w, int32_t h,
                   uint8_t r, uint8_t g, uint8_t b)
: CompositeWidget(parent, x, y, w, h, r, g, b){};
    SocobanGame::~SocobanGame(){};

    void SocobanGame::Draw(common::GraphicsContext* gc){};

    void SocobanGame::GetBackgroudColor(common::uint8_t& r, common::uint8_t& g, common::uint8_t& b){};


    bool SocobanGame::CheckWin(){return false;};
    void SocobanGame::ShowWinScreen(){};


ObjectOnMap::ObjectOnMap() {
    InitPos(0,0);
}
ObjectOnMap::~ObjectOnMap() {
}
ObjectOnMap::ObjectOnMap(const int x, const int y) {
    InitPos(x,y);
}

int ObjectOnMap::ShowPosX() {
    return p_x;
}
int ObjectOnMap::ShowPosY() {
    return p_y;
}
Character::Character(const int x, const int y) {
	InitPos(x, y);
}
void ObjectOnMap::StartPos(const int x, const int y) {
    InitPos(x, y);
}
Character::Character() {
    InitPos(0,0);
}
bool ObjectOnMap::ChangePos(const int ofs_x, const int ofs_y) {
    p_x += ofs_x;
	p_y += ofs_y;
	return true;
}
void ObjectOnMap::InitPos(const int x, const int y) {
	p_x = x;
	p_y = y;
}

void ObjectOnMap::MoveInDir(const char mode) {
    switch (mode) {
	case UP://up
		ChangePos(0, -1);
		break;
	case DOWN://down
		ChangePos(0, 1);
		break;
	case LEFT://left
		ChangePos(-1, 0);
		break;
	case RIGHT://right
		ChangePos(1, 0);
		break;
	}
}

void Character::Move(const unsigned char mode,Field* field, Box* box_array,const int box_amount){
    if (field->SetC(mode) == true) {
		MoveBox(ShowPosY()-1, ShowPosX(), box_array, box_amount, mode);
		MoveInDir(mode);
	}
}

void Character::MoveBox(const int pos_x, const int pos_y, Box* box_array, const unsigned box_amount, unsigned char mode) {
    unsigned int box_num = 0;
	for (box_num = 0; box_num < box_amount; box_num++) {
		if (!(box_array[box_num].CmpPos(pos_x, pos_y))) {
			box_array[box_num].Move(mode);
		}
	}
}


Character::~Character() {}

Box::Box() {
    InitPos(0, 0);
}

Box::Box(const int x, const int y) {
    InitPos(x, y);
}

bool Box::CmpPos(const int x, const int y){
    	if (x == ShowPosX() && y == ShowPosY()) {
		return false;
	}
	return true;
}


void Box::Move(const unsigned char mode) {
    MoveInDir(mode);
}

Box::~Box() {}

Finish::Finish() {
    InitPos(0, 0);
}

Finish::Finish(const int x, const int y) {
    InitPos(x, y);
}

Finish::~Finish() {}

Field::Field() {
	box_amount = 0;
	points = 0;
	lvl = 0;
	total_lvl = 0;
	box_array=nullptr;
	finish_array=nullptr;
	int count;
	lvlf[lvlfile_h-1][lvlfile_l-1] = { 0 };
	map[Field_h-1][Field_l-1] = { 0 };
	int result=0;
	total_lvl = 10;
}

Field::~Field() {
}

void Field::LoadLevel(const int level) {
    for (int i = 0; i < Field_h; i++) {
		for (int j = 0; j < Field_l; j++) {
			map[i][j] = savMap[i][j];
		}
	}
	for (int y = 0; y < Field_h; y++) {
		for (int x = 0; x < Field_l - 1; x++) {
			if (map[y][x] == 'B') {
				box_amount++;
			}
		}
	}
	finish_array = new Finish[box_amount];
	box_array = new Box[box_amount];
	unsigned char Box_i = 0;
	unsigned char Fin_i = 0;
	for (int y = 0; y < Field_h; y++) {
		for (int x = 0; x < Field_l - 1; x++) {
			switch (map[y][x]) {
			case 'H'://персонаж
				character.StartPos(x, y);
				break;
			case 'o'://финиши
				finish_array[Fin_i++].StartPos(x, y);
				break;
			case 'B'://коробки
				box_array[Box_i++].StartPos(x, y);
				break;
			}
		}
	}
}

void Field::Show() {
	for (int y = 0; y < Field_h; y++) {
        //tyt bydem kak-to ortisovivat6
	}

}
unsigned char Field:: WinCheck() {
    	int points=0;
	for (int i = 0; i < box_amount; i++) {
		int py = finish_array[i].ShowPosY();
		int px = finish_array[i].ShowPosX();
		switch (map[py][px]) {
		case ' ':
			map[py][px] = 'o';
			break;
		case 'B':
			points++;
			break;
		}
	}
	return points;
}
void Field::Game() {
    //tyt nam nado kak-to obrabotat6 nazhatia
	ShowScreen(0);
	//тут игра
	ShowScreen(1);
	char key=0;
	while (key != 'x') {
		Show();
		switch (key) {
		case 'w':
			character.Move(UP,this, box_array,box_amount);
			break;
		case 's':
			character.Move(DOWN, this,box_array, box_amount);
			break;
		case 'a':
			character.Move(LEFT, this,box_array, box_amount);
			break;
		case 'd':
			character.Move(RIGHT, this,box_array, box_amount);
			break;
		case 'r':
			LoadLevel(lvl);
			break;
		case 'x':
			key = 'x';
			break;
		}
		if (WinCheck() == box_amount) {
			if (lvl < total_lvl) {
				lvl++;
				LoadLevel(lvl);
				ShowScreen(1);
				continue;
			}
		}
		Show();
	}
}

void Field::ShowScreen(const unsigned int mode) {

}

bool Field::SetC(const unsigned char dir) {
    return false;
}