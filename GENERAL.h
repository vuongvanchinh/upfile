#ifndef GENERAL_H
#define GENERAL_H

#include<iostream>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string>
#include<cmath>
#include<vector>
#include<SDL_messagebox.h>
#include<ctime>

using namespace std;


const int SCREEN_WIDTH = 1500;
const int SCREEN_HEIGHT = 426;
const int DOCAOSAN = 348;
const int vantocnhanvat = 6;

const int vantocchimbay = 4;
const int vantocdan_nhanvat = 10;
const int MANG_SONG_MAX = 10;
const int FULLSCREEN = 3790;
const int solanbantrungmax_QUAI_DOI = 30;
const int LIMIT_FRIRST = 270;
const int LIMIT_LAST = SCREEN_WIDTH - 600;
const int SO_LAN_CHIM_MAX = 4;
const int vantoc_dan_chimbay = 2;

const int DELAY_SPRITE_NHANVAT = 2;

const int DELAY_SPRITE_CHIMBAY = 10;

const int DELAY_SPRITE_QUAI_DOI = 80;

const int DELAY_SPRITE_BULLET_QUAI_DOI = 10;
const int SO_CHIM_BAY = 20;
const int SUC_BAT = 300;
const int GIATOC_TRONGTRUONG = 1;
const int y_value = 5;

const int delta_ = 5;
const int y_value2 = 10;
enum status {
	left_to_right,
	right_to_left,
	up_left_to_right,
	up_right_to_left
};
  
#endif // !GENERRAL_H
