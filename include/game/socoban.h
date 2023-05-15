#ifndef __MYOS__GAME__SOKOBAN_H
#define __MYOS__GAME__SOKOBAN_H

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
        
        class WelcomeScreen;
        class Field;
        class Box;
        class Finish;
        class Character;
        class SocobanGame;




        class ObjectOnMap {
        protected:
            int p_x;
            int p_y;
        public:
            ObjectOnMap();
            ObjectOnMap(const int x, const int y);
            ~ObjectOnMap();
            void StartPos(const int x, const int y);
            int ShowPosX();
            int ShowPosY();
            bool ChangePos(const int ofs_x, const int ofs_y);
            void InitPos(const int x, const int y);
            void MoveInDir(const char mode);
        };

        class Character :public ObjectOnMap {
        private:
        public:
            Character(const int x, const int y);
            Character();
            ~Character();
            void Move(const unsigned char mode, Field* field, Box* box_array, const int box_amount);
            void MoveBox(const int pos_x, const int pos_y, Box* box_array, const unsigned box_amount,const unsigned char mode);

        };
        class Box:public ObjectOnMap {
        private:
        public:
            Box();
            Box(const int x, const int y);
            ~Box();
            bool CmpPos(const int x, const int y);
            void Move(const unsigned char mode);

        };
        class Finish :public ObjectOnMap {
        private:
        public:
            Finish();
            Finish(const int x, const int y);
            ~Finish();
        };
        class Field {
        private:
            unsigned char points;
            char lvlf [lvlfile_l][lvlfile_h];
            char map [Field_h][Field_l] = {
	"****************************************",
	"*                                      *",
	"*                                      *",
	"*                 ###                  *",
	"*                 #o#                  *",
	"*                 # ####               *",
	"*               ###B Bo#               *",
	"*               #o BH###               *",
	"*               ####B#                 *",
	"*                  #o#                 *",
	"*                  ###                 *",
	"*                                      *",
	"*                                      *",
	"*                                      *",
	"****************************************"
	};
	char savMap[Field_h][Field_l] = {
"****************************************",
"*                                      *",
"*                                      *",
"*                 ###                  *",
"*                 #o#                  *",
"*                 # ####               *",
"*               ###B Bo#               *",
"*               #o BH###               *",
"*               ####B#                 *",
"*                  #o#                 *",
"*                  ###                 *",
"*                                      *",
"*                                      *",
"*                                      *",
"****************************************"
	};

            int box_amount;
            unsigned int total_lvl;
            Character character;
            Box* box_array;
            Finish* finish_array;
            unsigned int lvl;
            void ShowScreen(const unsigned int i);
            SocobanGame* curGame;
        public:
            Field();
            Field(SocobanGame* game);
            ~Field();
            void handleClick(char key);
            void LoadLevel(const int lvl);
            unsigned char WinCheck();
            void Show();
            void Game();
            bool SetC(const unsigned char dir);
        };

                class SocobanGame : public gui::CompositeWidget
        {
        public:
            SocobanGame(gui::Widget* parent,
                   common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h,
                   common::uint8_t r, common::uint8_t g, common::uint8_t b);
            ~SocobanGame();

            void Draw(common::GraphicsContext* gc);

            void GetBackgroudColor(common::uint8_t& r, common::uint8_t& g, common::uint8_t& b);

            void changeMap(char (*myArray)[Field_l]);

            void OnKeyDown(char c);

            char map [Field_h][Field_l] = {
            "****************************************",
            "*                                      *",
            "*                                      *",
            "*                 ###                  *",
            "*                 #o#                  *",
            "*                 # ####               *",
            "*               ###B Bo#               *",
            "*               #o BH###               *",
            "*               ####B#                 *",
            "*                  #o#                 *",
            "*                  ###                 *",
            "*                                      *",
            "*                                      *",
            "*                                      *",
            "****************************************"
            };

        private:
        common::GraphicsContext* gc;
            bool CheckWin();
            void ShowWinScreen();
        Field field;
        };
    };
};
#endif