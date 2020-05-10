
#include"GENERAL.h"
//#include"bullet.h"
#include"object.h"
#include"quai_object.h"
#include"Text.h"


// global variables

Mix_Chunk* tieng_sung = NULL;

Mix_Chunk* tieng_qua_keu = NULL;

Mix_Chunk* tieng_qua_chet = NULL;

Mix_Chunk* tieng_nguoi_trung_dan = NULL;

Mix_Chunk* tieng_nguoi_that_bai = NULL;

Mix_Chunk* tieng_quaivat_trung_dan = NULL;

Mix_Chunk* tieng_quaivat_that_bai = NULL;

Mix_Chunk* tieng_nhat_duoc_tien = NULL;


SDL_Window* g_window = NULL;
 SDL_Renderer* g_render = NULL;
TTF_Font* g_font = NULL;
//// =========================================cac doi tuong=========================================

object background, nhanvat, background_menu;

quai_object QUAI_DOI;
vector<quai_object*>chimbay;
SDL_Rect sprite_quaidoi[2];
SDL_Rect spritechimbay[6];
SDL_Rect sprite_bullet_QUAI[7];




SDL_Rect spritenhanvat[26];
SDL_Rect sprite_bulletnhanvat[4];
vector<bullet*> money;
SDL_Rect sprite_monney[4];

SDL_Rect sprite_fire[8];
Text g_text;

bullet fire, gift_money;

float  he_so_goc_duong_dan=2.0 ;

//===================================================================================

//============================================ cac ham khoi tao vaf dong======================
void PLAY_GAME();


void show_menu();
bool init();
bool loadmedia(SDL_Renderer* &g_render);
void close();
void reset();

void XU_LY_DI_CHUYEN(object& background, object& nhanvat, SDL_Event& e);

void XU_LY_SPRITE_NHANVAT(object& nhanvat);

void XU_LY_PRITE_QUAI_DOI(quai_object& QUAI_DOI);

void XU_LY_DAN_NHAN_VAT(object &nhanvat);

void XU_LY_SPRITE_QUAI_BAY();

// cac ham khoi tao sprite 
void khoi_tao_quaibay();
void khoi_tao_sprite_bullet_QUAI(bool& thanhcong, SDL_Renderer* &g_render);
void khoi_tao_sprite_nhanvat(bool thanhcong, SDL_Renderer* &g_render);
void khoi_tao_sprite_QUAI_DOI(bool& thanhcong, SDL_Renderer* &g_render);
void khoi_tao_sprite_CHIMBAY(bool& thanhcong, SDL_Renderer* &g_render);
void khoi_tao_sprite_fire(bool& thanhcong, SDL_Renderer* &g_render);
void khoi_tao_sprite_trai_tim(bool &thanhcong, SDL_Renderer* &g_render);
void khoi_tao_sprite_monney(bool& thanhcong, SDL_Renderer* &g_render);
void khoi_tao_TTF(bool& thanhcong, SDL_Renderer* &g_render, TTF_Font* &g_font);

//khoi tao am thanh
void khoi_tao_am_thanh(bool& thanhcong);
// khoi tao bang dan va play sounds 
void khoitaobangdan(object& nhanvat, SDL_Event& e);
// ddieu chinh vi tri dan
int is_left_to_right(status trangthai);
// cac ham show
void show_money(vector<bullet*> &money);
void show_trai_tim(int traitim);
void show_fire(int vitrix, int vitriy, int khunghinh);
void show_score(int score);
void khoi_tao_money(int vitrix, int vitriy);

// xu ly ket thuc game 
void end_game(bool& quit);
/// ham xu ly va cham truyen vao 8 doi so la toa do va w, h cua hai doi tuong 
bool isVaCham(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);
int main(int agrv, char* agrs[])
{
	if (init() == false)
	{
		cout << "khoi tao that bai";
	}
	else
	{
		if (loadmedia(g_render) == false)
		{
			cout << "load media that bai";
		}
		else
		{
			show_menu();
		}
	}
	close();
	return 0;
}



//=====================================cac ham xu ly ====================================================
void XU_LY_DAN_NHAN_VAT(object &nhanvat)
{
	if (nhanvat.getmang_song() > 0)
	{
		for (int i = 0; i < nhanvat.bulletnhanvat.size(); i++)
		{
			if (nhanvat.bulletnhanvat.at(i) != NULL)
			{
				bullet* l_bullet = nhanvat.bulletnhanvat.at(i);
				///show dan
				l_bullet->render(NULL, g_render);
				// xu ly trang thai di chuyen cua dan  
				if (l_bullet->gettrangthai() == up_left_to_right ||
					l_bullet->gettrangthai() == left_to_right)
				{
					l_bullet->setposx(l_bullet->getposx() + vantocdan_nhanvat);
				}
				else {
					l_bullet->setposx(l_bullet->getposx() - vantocdan_nhanvat);
				}
				// xu ly cham bien==============================================================================================
				if (l_bullet->getposx() < -15 || l_bullet->getposx() > SCREEN_WIDTH)
				{
					//bulletnhanvat[i]->free();
					nhanvat.bulletnhanvat.erase(nhanvat.bulletnhanvat.begin() + i);
					delete l_bullet;
				}
				else
				{// xu_ly ban trung QUAI DOI
					if (isVaCham(l_bullet->getposx(), l_bullet->getposy(),24, 13, QUAI_DOI.getposx(), QUAI_DOI.getposy(), 245, 256)==true)
					{
						QUAI_DOI.setsolantrungdan(QUAI_DOI.getsolantrungdan() + 1);
						show_fire(QUAI_DOI.getposx()+10, QUAI_DOI.getposy() , 1);
						nhanvat.bulletnhanvat.erase(nhanvat.bulletnhanvat.begin() + i);

						if (QUAI_DOI.getsolantrungdan() % 5 == 0)
						{
							Mix_PlayChannel(-1, tieng_quaivat_trung_dan, 0);
						}

						delete l_bullet;
					}
					else
					{/// xu ly trung chim bay 
						for (int ichimbay = 0; ichimbay < chimbay.size(); ichimbay++)
						{
							if (isVaCham(l_bullet->getposx(), l_bullet->getposy(),24,13,chimbay[ichimbay]->getposx(),
								chimbay[ichimbay]->getposy(),70, spritechimbay[chimbay[ichimbay]->getkhunghinh() / DELAY_SPRITE_CHIMBAY].h) == true)
							{
								chimbay[ichimbay]->setsolantrungdan(chimbay[ichimbay]->getsolantrungdan() + 1);
								// xu ly chim chet
								if (chimbay[ichimbay]->getsolantrungdan() >= SO_LAN_CHIM_MAX)
								{
									show_fire(chimbay[ichimbay]->getposx() - 50, chimbay[ichimbay]->getposy() - 185, 1);

									khoi_tao_money(chimbay[ichimbay]->getposx(), chimbay[ichimbay]->getposy());
									chimbay.erase(chimbay.begin() + ichimbay);
									Mix_PlayChannel(-1, tieng_qua_chet, 0);
								}
								else
								{
									show_fire(chimbay[ichimbay]->getposx() - 50, chimbay[ichimbay]->getposy() - 185, 0);
								}
								

								nhanvat.bulletnhanvat.erase(nhanvat.bulletnhanvat.begin() + i);
								
								l_bullet;
								break;
							}
						}
						
						
					}

				}
			}
		}
	
	}
}


void XU_LY_SPRITE_QUAI_BAY()

{
	for (int i = 0; i < chimbay.size(); i++)
	{
		if (abs(nhanvat.getposx() - chimbay[i]->getposx()) < SCREEN_WIDTH-LIMIT_FRIRST)
		{
			// show chim bay 
			chimbay[i]->render(&spritechimbay[chimbay[i]->getkhunghinh() / DELAY_SPRITE_CHIMBAY], g_render);
		
			// neu chim cham nguoi
			if (isVaCham(nhanvat.getposx(), nhanvat.getposy(),spritenhanvat[nhanvat.getkhunghinh()/DELAY_SPRITE_NHANVAT].w,
				spritenhanvat[nhanvat.getkhunghinh() / DELAY_SPRITE_NHANVAT].h,
				chimbay[i]->getposx(), chimbay[i]->getposy(),spritechimbay[chimbay[i]->getkhunghinh()/DELAY_SPRITE_CHIMBAY].w,
				spritechimbay[chimbay[i]->getkhunghinh() / DELAY_SPRITE_CHIMBAY].h)==true)	
			{
				nhanvat.setmang_song(nhanvat.getmang_song()-2);
				show_fire(chimbay[i]->getposx() - 100, chimbay[i]->getposy() - 100, 1);
				Mix_PlayChannel(-1, tieng_nguoi_trung_dan, 0);
				//xoa
				chimbay.erase(chimbay.begin() + i);
			}
			else
			{// XU LY KHUNG HINH chim bay 
				if (chimbay[i]->getkhunghinh() / DELAY_SPRITE_CHIMBAY >= 5)
				{
					chimbay[i]->setkhunghinh(0);
				}
				else chimbay[i]->setkhunghinh(chimbay[i]->getkhunghinh() + 1);
				// xu ly am thanh
				if (chimbay[i]->getkhunghinh() == 4 * DELAY_SPRITE_CHIMBAY)
				{
					Mix_PlayChannel(-1, tieng_qua_keu, 0);
				}
				// update vi tri chim bay 
				if (chimbay[i]->getposx() <= -60)
				{
					chimbay[i]->setposx(nhanvat.getposx()+SCREEN_WIDTH);
				}
				else chimbay[i]->setposx(chimbay[i]->getposx() - vantocchimbay);


				// show bullet chim bay================================================
				chimbay[i]->BULLET.loadimage("hinh_anh/bullet_quai.png",g_render);
				chimbay[i]->BULLET.render(&sprite_bullet_QUAI[0], g_render);

				// xu lu dan ra khoi man hinh hoac dan cham san
				if (chimbay[i]->BULLET.getposx() < 0 || chimbay[i]->BULLET.getposy() >= DOCAOSAN)
				{
					//show_fire(chimbay[i]->BULLET.getposx(), chimbay[i]->BULLET.getposy(), 0);
					chimbay[i]->BULLET.setposx(chimbay[i]->getposx());
					chimbay[i]->BULLET.setposy(chimbay[i]->getposy());
					
				}
				else// xu ly dan trung nhanvat
				{
					if (isVaCham(nhanvat.getposx(),nhanvat.getposy(),spritenhanvat[nhanvat.getkhunghinh()/DELAY_SPRITE_NHANVAT].w, 
						spritenhanvat[nhanvat.getkhunghinh() / DELAY_SPRITE_NHANVAT].h, chimbay[i]->BULLET.getposx(), chimbay[i]->BULLET.getposy(), 22, 25) == true)
						
					{
						nhanvat.setmang_song(nhanvat.getmang_song() - 1);

						chimbay[i]->BULLET.setposx(chimbay[i]->getposx());
						chimbay[i]->BULLET.setposy(chimbay[i]->getposy());

						show_fire(nhanvat.getposx() - 70, nhanvat.getposy() - 150, 0);

						
						//amthanh
						Mix_PlayChannel(-1, tieng_nguoi_trung_dan, 0);

					}
					else
					{// xu ly update vi tri dan
						if (chimbay[i]->getkhunghinh() % 2 == 0)
						{
							chimbay[i]->BULLET.setposx(chimbay[i]->BULLET.getposx() - 5);
							chimbay[i]->BULLET.setposy(chimbay[i]->BULLET.getposy() + 3);
						}
					}
					//=======================================================================

				}
			}

		}

	}

}

void XU_LY_DI_CHUYEN(object &background, object &nhanvat,SDL_Event &e)
{
	if (e.type == SDL_KEYDOWN ||nhanvat.getmang_song()>0)
	{
		switch (e.key.keysym.sym)
		{
		
		case SDLK_LEFT: 
		{
			
			if (nhanvat.gettrangthai() !=right_to_left )
			{
				nhanvat.setkhunghinh(18*DELAY_SPRITE_NHANVAT);
				nhanvat.settrangthai (right_to_left);
			}
			else 
				if (nhanvat.gettrangthai() == right_to_left)
					nhanvat.setkhunghinh(nhanvat.getkhunghinh()+1);
				
			//XU LY DI CHUYEN 
			if (nhanvat.getposx() <= LIMIT_LAST && background.getposx() <0)
			{
				background.setposx(background.getposx()+vantocnhanvat);
				// cho chim bay di chuyen theo 
				for (int i = 0; i < chimbay.size(); i++)
				{
				
					chimbay[i]->setposx(chimbay[i]->getposx() + vantocnhanvat);
					chimbay[i]->BULLET.setposx(chimbay[i]->BULLET.getposx() + vantocnhanvat);
					
				}
				// cho money di chuyen theo 
				for (int j = 0; j < money.size(); j++)
				{
					money.at(j)->setposx(money.at(j)->getposx() + vantocnhanvat);
				}
				if (abs(QUAI_DOI.getposx() - nhanvat.getposx()) < SCREEN_WIDTH)
				{
					QUAI_DOI.BULLET.setposx(QUAI_DOI.BULLET.getposx() + vantocnhanvat);
				}
			}
			else
			{
				if (nhanvat.getposx() > 0)
					nhanvat.setposx(nhanvat.getposx()-vantocnhanvat);
			}
			break;
		}
		
		case SDLK_RIGHT:
		{
			
			if (nhanvat.gettrangthai() != left_to_right)
			{
				nhanvat.setkhunghinh(6*DELAY_SPRITE_NHANVAT);
				nhanvat.settrangthai(left_to_right);
				
			}
			else
			{
				if (nhanvat.gettrangthai() == left_to_right)
					nhanvat.setkhunghinh(nhanvat.getkhunghinh() + 1);
			}
			//xu ly di chuyen 
			if (nhanvat.getposx() >= LIMIT_FRIRST && background.getposx() > -(FULLSCREEN - SCREEN_WIDTH))
			{
				background.setposx(background.getposx()-vantocnhanvat) ;
				// cho chim bay di chuyen theo 
				for (int i = 0; i < chimbay.size(); i++)
				{
					chimbay[i]->setposx(chimbay[i]->getposx() - vantocnhanvat);
					chimbay[i]->BULLET.setposx(chimbay[i]->BULLET.getposx() - vantocnhanvat);
				}
				// cho money di chuyen theo 
				for (int j = 0; j < money.size(); j++)
				{
					money.at(j)->setposx(money.at(j)->getposx() - vantocnhanvat);
				}
				if (abs(QUAI_DOI.getposx() - nhanvat.getposx()) < SCREEN_WIDTH)
				{
					QUAI_DOI.BULLET.setposx(QUAI_DOI.BULLET.getposx() - vantocnhanvat);
				}
			}
			else
			{
				if (nhanvat.getposx() < SCREEN_WIDTH - 90)
				{
					nhanvat.setposx(nhanvat.getposx() + vantocnhanvat);
				}
			}
			break;
		}
		
		case SDLK_UP:
		{
			if (nhanvat.gettrangthai() == left_to_right)
			{
				nhanvat.settrangthai(up_left_to_right);
				nhanvat.setkhunghinh(1 * DELAY_SPRITE_NHANVAT);
				if (nhanvat.getposy() >= DOCAOSAN - spritenhanvat[nhanvat.getkhunghinh() / DELAY_SPRITE_NHANVAT].h)
				{
					nhanvat.setposy(nhanvat.getposy() - SUC_BAT);
				}
			}
			else
			{
				if (nhanvat.gettrangthai() == right_to_left)
				{
					nhanvat.settrangthai(up_right_to_left);
					nhanvat.setkhunghinh(13 * DELAY_SPRITE_NHANVAT);
					if (nhanvat.getposy() >= DOCAOSAN - spritenhanvat[nhanvat.getkhunghinh() / DELAY_SPRITE_NHANVAT].h)
					{
						nhanvat.setposy(nhanvat.getposy() - SUC_BAT);
						
					}
				}
			}
		
		}
		default:
			break;
		}
	}
}
void XU_LY_SPRITE_NHANVAT(object &nhanvat)
{
	//trong luc 
	if (nhanvat.getposy() < DOCAOSAN - spritenhanvat[nhanvat.getkhunghinh()/DELAY_SPRITE_NHANVAT].h)
	{
		nhanvat.setposy(nhanvat.getposy() + GIATOC_TRONGTRUONG);
	}	
	else
	{
		switch (nhanvat.gettrangthai())
		{
		case up_left_to_right:
			nhanvat.settrangthai(left_to_right);
			nhanvat.setkhunghinh(6 * DELAY_SPRITE_NHANVAT);

			break;
		case up_right_to_left:
			nhanvat.settrangthai(right_to_left);
			nhanvat.setkhunghinh(18 * DELAY_SPRITE_NHANVAT);
			break;
		}
	}

	if (nhanvat.gettrangthai() == left_to_right)
	{

		if (nhanvat.getkhunghinh()/DELAY_SPRITE_NHANVAT >= 11)
			nhanvat.setkhunghinh(6*DELAY_SPRITE_NHANVAT);
	}
	else
	{
		if (nhanvat.gettrangthai() == right_to_left)
		{
			if (nhanvat.getkhunghinh()/DELAY_SPRITE_NHANVAT>= 23) nhanvat.setkhunghinh(18*DELAY_SPRITE_NHANVAT);
		}
	}
}
void XU_LY_PRITE_QUAI_DOI(quai_object& QUAI_DOI )
{ 
	//Doi luon o cuoi man hinh
		QUAI_DOI.setposx(background.getposx() + FULLSCREEN - 256);
		QUAI_DOI.setposy(DOCAOSAN - 350);
		if (abs(nhanvat.getposx() - QUAI_DOI.getposx()) <= SCREEN_WIDTH - LIMIT_FRIRST)
		{
			if (QUAI_DOI.getsolantrungdan() < solanbantrungmax_QUAI_DOI)
			{
				QUAI_DOI.render(&sprite_quaidoi[QUAI_DOI.getkhunghinh() / DELAY_SPRITE_QUAI_DOI], g_render);

				// XU LY KHUNG HINH QUAI DOI
				if (QUAI_DOI.getkhunghinh() / DELAY_SPRITE_QUAI_DOI >= 2)
				{
					QUAI_DOI.setkhunghinh(0);
				}
				else QUAI_DOI.setkhunghinh(QUAI_DOI.getkhunghinh() + 1);

				//XU LY DAN QUAI DOI==================================================
				
				QUAI_DOI.BULLET.render(&sprite_bullet_QUAI[QUAI_DOI.BULLET.getkhunghinh()/DELAY_SPRITE_BULLET_QUAI_DOI], g_render);
				
				//xu ly khi dan cham san
				if (QUAI_DOI.BULLET.getposy() >= DOCAOSAN|| QUAI_DOI.BULLET.getposx()<=0)
				{
					QUAI_DOI.BULLET.setposy(QUAI_DOI.getposy() + 100);
					QUAI_DOI.BULLET.setposx(QUAI_DOI.getposx()-10);
					he_so_goc_duong_dan =(float(QUAI_DOI.getposy()  - nhanvat.getposy() ) / float(nhanvat.getposx()-QUAI_DOI.getposx() + 10 )+1);
				}
				else
				{
					// XU LY DAN TRUNG NHAN VAT
					if (isVaCham(nhanvat.getposx(), nhanvat.getposy(), spritenhanvat[nhanvat.getkhunghinh()/DELAY_SPRITE_NHANVAT].w,
						spritenhanvat[nhanvat.getkhunghinh() / DELAY_SPRITE_NHANVAT].h, QUAI_DOI.BULLET.getposx(), QUAI_DOI.BULLET.getposy(), 22, 25) == true)
					{
						nhanvat.setmang_song(nhanvat.getmang_song() - 2);
						
						show_fire(nhanvat.getposx()-50, nhanvat.getposy()-100, 0);
						QUAI_DOI.BULLET.setposy(QUAI_DOI.getposy() + 100);
						QUAI_DOI.BULLET.setposx(QUAI_DOI.getposx() - 10);

						Mix_PlayChannel(-1, tieng_nguoi_trung_dan, 0);
					
						
					}
					else
					{// CAP NHAT VI TRI DAN
						if (QUAI_DOI.getkhunghinh() % 2 == 0)
						{
							QUAI_DOI.BULLET.setposy(QUAI_DOI.BULLET.getposy() +he_so_goc_duong_dan);
							QUAI_DOI.BULLET.setposx(QUAI_DOI.BULLET.getposx() -3);
						}
						
						// xu ly khung hinh dan
						
						if (QUAI_DOI.BULLET.getkhunghinh()/DELAY_SPRITE_BULLET_QUAI_DOI > 5)
						{
							QUAI_DOI.BULLET.setkhunghinh(0);
						}else QUAI_DOI.BULLET.setkhunghinh(QUAI_DOI.BULLET.getkhunghinh() + 1);
					}
				}
			}
		}
}

bool init()
{
	bool thanhcong = true;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "Khoi tao that bai:" << SDL_GetError();
		thanhcong = false;
	}
	else {
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			cout << "Warning: Linear texture filtering not enabled!";
		}
		g_window = SDL_CreateWindow("CORONA CAMPAIGN", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (g_window == NULL) {
			cout << "Khoi tao cua so that bai:" << SDL_GetError();
			thanhcong = false;
		}
		else {
			g_render = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
			if (g_render == NULL) {
				cout << "Khoi tao render that bai" << SDL_GetError();
				thanhcong = false;
			}
			else {

				SDL_SetRenderDrawColor(g_render, 0xff, 0xff, 0xff, 0xff);
				int IMGflag = IMG_INIT_PNG;
				if (!(IMG_Init(IMGflag) & IMGflag))
				{
					cout << "SDL_image khoi tao that bai" << SDL_GetError();
					thanhcong = false;
				}

				//khoi tao  SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					cout<<"SDL_mixer could not initialize! SDL_mixer Error: %s\n"<< Mix_GetError();
					thanhcong = false;
				}
				//khoi tao SDL_ttf
				if (TTF_Init() == -1)
				{
					cout<< "SDL_ttf could not initialize! SDL_ttf Error: %s\n"<< TTF_GetError();
					thanhcong = false;
				}
			}
		}
	}
	return thanhcong;
}
bool loadmedia(SDL_Renderer* &g_render)
{
	bool thanhcong = true;
	if (background.loadimage("hinh_anh/background.png",g_render) == false)
	{
		cout << "load anh nen that bai:";
		thanhcong = false;
	}
	if (background_menu.loadimage("hinh_anh/menu.png",g_render) == false)
	{
		cout << "load anh nen that bai:";
		thanhcong = false;
	}
	// tao sprite nhan vat 
	khoi_tao_sprite_nhanvat(thanhcong,g_render);

	/// load anh va tao sprite cho quai roi
	khoi_tao_sprite_QUAI_DOI(thanhcong,g_render);
	// load anh chimbay

	khoi_tao_sprite_CHIMBAY(thanhcong,g_render);
	// khoi tao sprite fire
	khoi_tao_sprite_fire(thanhcong,g_render);
	// khoi tao bullrt quai 
	khoi_tao_sprite_bullet_QUAI(thanhcong,g_render);
	// khoi tao sprite trai tim
	khoi_tao_sprite_trai_tim(thanhcong,g_render);
	// khoi tao sprite money
	khoi_tao_sprite_monney(thanhcong,g_render);
	//khoi tao am thanh
	khoi_tao_am_thanh(thanhcong);

	khoi_tao_TTF(thanhcong,g_render, g_font);
	return thanhcong;
}
void close()
{
	for (int i = 0; i < chimbay.size(); i++)
	{

		chimbay[i]->free();
	}
	for (int i = 0 ; i < nhanvat.bulletnhanvat.size(); i++)
	{
		nhanvat.bulletnhanvat[i]->free();
	}
	fire.free();
	//CHIM_BAY.free();
	nhanvat.free();
	background.free();
	QUAI_DOI.free();
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_render);
	
	g_window = NULL;
	g_render = NULL;
	Mix_FreeChunk(tieng_sung);
	tieng_sung = NULL;

	Mix_FreeChunk(tieng_nguoi_that_bai);
	tieng_nguoi_that_bai = NULL;
	
	Mix_FreeChunk(tieng_nguoi_trung_dan);
	tieng_nguoi_trung_dan = NULL;
	
	Mix_FreeChunk(tieng_nhat_duoc_tien);
	tieng_nhat_duoc_tien = NULL;
	
	Mix_FreeChunk(tieng_qua_chet);
	tieng_qua_chet= NULL;
	
	Mix_FreeChunk(tieng_qua_keu);
	tieng_qua_keu = NULL;

	Mix_FreeChunk(tieng_quaivat_that_bai);
	tieng_quaivat_that_bai = NULL;

	Mix_FreeChunk(tieng_quaivat_trung_dan);
	tieng_quaivat_trung_dan = NULL;

	Mix_FreeChunk(tieng_quaivat_that_bai);
	tieng_quaivat_that_bai = NULL;



	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
}
void khoi_tao_quaibay()
{
	for (int i = 0; i < SO_CHIM_BAY; i += 2)
	{
		quai_object* l_chimbay = new quai_object();
		l_chimbay->loadimage("hinh_anh/chimbay.png", g_render);
		l_chimbay->setposy(DOCAOSAN - 260);
		l_chimbay->setposx(background.getposx() + 1500 + i * 100);
		l_chimbay->setkhunghinh(0);
		l_chimbay->BULLET.setposy(DOCAOSAN - 250);

		chimbay.push_back(l_chimbay);

		quai_object* l_chimbay1 = new quai_object();
		l_chimbay1->loadimage("hinh_anh/chimbay.png", g_render);
		l_chimbay1->setposy(DOCAOSAN - 200);
		l_chimbay1->BULLET.setposy(DOCAOSAN - 190);
		l_chimbay1->setposx(background.getposx() + 1600 + i * 100);
		l_chimbay1->setkhunghinh(0);
		chimbay.push_back(l_chimbay1);
	}
}
void khoi_tao_sprite_bullet_QUAI(bool& thanhcong, SDL_Renderer* &g_render)
{
	bullet* newbullet = new bullet();
	if (newbullet->loadimage("hinh_anh/bullet.png",g_render) == false)
	{
		thanhcong = false;
	}
	else
	{
		for (int i = 0; i < 7; i++)
		{
			sprite_bullet_QUAI[i].x = 23 * i;
			sprite_bullet_QUAI[i].y = 0;
			sprite_bullet_QUAI[i].w = 23;
			sprite_bullet_QUAI[i].h = 25;
		}
	}

}
void khoi_tao_sprite_nhanvat(bool thanhcong, SDL_Renderer* &g_render)
{
	if (nhanvat.loadimage("hinh_anh/nhanvat1.png",g_render) == false)
	{
		cout << "load anh nen that bai:";
		thanhcong = false;
	}
	else
	{
		spritenhanvat[0].x = 1;
		spritenhanvat[0].y = 25;
		spritenhanvat[0].w = 96;
		spritenhanvat[0].h = 103;

		spritenhanvat[1].x = 97;
		spritenhanvat[1].y = 15;
		spritenhanvat[1].w = 96;
		spritenhanvat[1].h = 115;

		spritenhanvat[2].x = 193;
		spritenhanvat[2].y = 3;
		spritenhanvat[2].w = 96;
		spritenhanvat[2].h = 105;

		spritenhanvat[3].x = 0;
		spritenhanvat[3].y = 134;
		spritenhanvat[3].w = 90;
		spritenhanvat[3].h = 110;

		spritenhanvat[4].x = 90;
		spritenhanvat[4].y = 144;
		spritenhanvat[4].w = 90;
		spritenhanvat[4].h = 92;

		spritenhanvat[5].x = 180;
		spritenhanvat[5].y = 177;
		spritenhanvat[5].w = 90;
		spritenhanvat[5].h = 100;

		spritenhanvat[6].x = 0;
		spritenhanvat[6].y = 302;
		spritenhanvat[6].w = 90;
		spritenhanvat[6].h = 115;

		spritenhanvat[7].x = 90;
		spritenhanvat[7].y = 302;
		spritenhanvat[7].w = 98;
		spritenhanvat[7].h = 115;

		spritenhanvat[8].x = 190;
		spritenhanvat[8].y = 302;
		spritenhanvat[8].w = 99;
		spritenhanvat[8].h = 119;

		spritenhanvat[9].x = 1;
		spritenhanvat[9].y = 430;
		spritenhanvat[9].w = 90;
		spritenhanvat[9].h = 122;

		spritenhanvat[10].x = 91;
		spritenhanvat[10].y = 430;
		spritenhanvat[10].w = 100;
		spritenhanvat[10].h = 117;

		spritenhanvat[11].x = 190;
		spritenhanvat[11].y = 423;
		spritenhanvat[11].w = 99;
		spritenhanvat[11].h = 127;

		spritenhanvat[12].x = 487;
		spritenhanvat[12].y = 25;
		spritenhanvat[12].w = 90;
		spritenhanvat[12].h = 103;

		spritenhanvat[13].x = 387;
		spritenhanvat[13].y = 15;
		spritenhanvat[13].w = 100;
		spritenhanvat[13].h = 115;

		spritenhanvat[14].x = 289;
		spritenhanvat[14].y = 3;
		spritenhanvat[14].w = 98;
		spritenhanvat[14].h = 105;

		spritenhanvat[15].x = 489;
		spritenhanvat[15].y = 134;
		spritenhanvat[15].w = 88;
		spritenhanvat[15].h = 110;

		spritenhanvat[16].x = 397;
		spritenhanvat[16].y = 134;
		spritenhanvat[16].w = 90;
		spritenhanvat[16].h = 92;

		spritenhanvat[17].x = 310;
		spritenhanvat[17].y = 177;
		spritenhanvat[17].w = 87;
		spritenhanvat[17].h = 115;

		spritenhanvat[18].x = 494;
		spritenhanvat[18].y = 302;
		spritenhanvat[18].w = 83;
		spritenhanvat[18].h = 115;

		spritenhanvat[19].x = 390;
		spritenhanvat[19].y = 302;
		spritenhanvat[19].w = 94;
		spritenhanvat[19].h = 115;

		spritenhanvat[20].x = 290;
		spritenhanvat[20].y = 303;
		spritenhanvat[20].w = 100;
		spritenhanvat[20].h = 119;

		spritenhanvat[21].x = 490;
		spritenhanvat[21].y = 430;
		spritenhanvat[21].w = 87;
		spritenhanvat[21].h = 122;

		spritenhanvat[22].x = 390;
		spritenhanvat[22].y = 430;
		spritenhanvat[22].w = 100;
		spritenhanvat[22].h = 117;

		spritenhanvat[23].x = 290;
		spritenhanvat[23].y = 423;
		spritenhanvat[23].w = 100;
		spritenhanvat[23].h = 127;
	}
}
void khoi_tao_sprite_QUAI_DOI(bool& thanhcong, SDL_Renderer* &g_render)
{
	if (QUAI_DOI.loadimage("hinh_anh/quaidoi2.png",g_render) == false)
	{
		cout << "load anh quai doi that bai" << "\n";
		thanhcong = false;
	}
	else {
		sprite_quaidoi[0].x = 0;
		sprite_quaidoi[0].y = 0;
		sprite_quaidoi[0].w = 243;
		sprite_quaidoi[0].h = 256;

		sprite_quaidoi[1].x = 243;
		sprite_quaidoi[1].y = 0;
		sprite_quaidoi[1].w = 242;
		sprite_quaidoi[1].h = 256;
	}
}
void khoi_tao_sprite_CHIMBAY(bool& thanhcong, SDL_Renderer* &g_render)
{
	quai_object CHIM_BAY;
	if (CHIM_BAY.loadimage("hinh_anh/chimbay.png",g_render) == false)
	{
		cout << "load anh chim that bai:";
		thanhcong = false;
	}
	else {
		spritechimbay[0].x = 0;
		spritechimbay[0].y = 24;
		spritechimbay[0].w = 71;
		spritechimbay[0].h = 26;

		spritechimbay[1].x = 70;
		spritechimbay[1].y =22;
		spritechimbay[1].w = 71;
		spritechimbay[1].h = 31;

		spritechimbay[2].x = 140;
		spritechimbay[2].y = 0;
		spritechimbay[2].w = 71;
		spritechimbay[2].h = 53;

		spritechimbay[3].x = 0;
		spritechimbay[3].y = 67;
		spritechimbay[3].w = 71;
		spritechimbay[3].h = 43;

		spritechimbay[4].x = 70;
		spritechimbay[4].y = 65;
		spritechimbay[4].w = 71;
		spritechimbay[4].h = 57;

		spritechimbay[5].x = 140;
		spritechimbay[5].y = 64;
		spritechimbay[5].w = 71;
		spritechimbay[5].h = 48;
	}
	CHIM_BAY.free();
}
void khoi_tao_sprite_fire(bool& thanhcong, SDL_Renderer* &g_render)
{
	bullet* newbullet = new bullet();
	if (newbullet->loadimage("hinh_anh/fire.png",g_render) == false)
	{
		thanhcong = false;
	}
	else
	{
		sprite_fire[0].x = 0;
		sprite_fire[0].y = 0;
		sprite_fire[0].w = 220;
		sprite_fire[0].h = 353;

		sprite_fire[1].x = 220;
		sprite_fire[1].y = 0;
		sprite_fire[1].w = 320;
		sprite_fire[1].h = 353;

		sprite_fire[2].x = 540;
		sprite_fire[2].y = 0;
		sprite_fire[2].w = 400;
		sprite_fire[2].h = 353;

		sprite_fire[3].x = 1000;
		sprite_fire[3].y = 0;
		sprite_fire[3].w = 351;
		sprite_fire[3].h = 375;

		sprite_fire[4].x = 0;
		sprite_fire[4].y = 370;
		sprite_fire[4].w = 365;
		sprite_fire[4].h = 345;

		sprite_fire[5].x = 490;
		sprite_fire[5].y = 370;
		sprite_fire[5].w =310;
		sprite_fire[5].h = 345;

		sprite_fire[6].x = 925;
		sprite_fire[6].y = 370;
		sprite_fire[6].w = 325;
		sprite_fire[6].h = 345;

		sprite_fire[7].x = 1250;
		sprite_fire[7].y = 370;
		sprite_fire[7].w = 140;
		sprite_fire[7].h = 345;

	}
}
void khoi_tao_sprite_trai_tim(bool &thanhcong, SDL_Renderer* &g_render)
{
	bullet traitim;
	if (traitim.loadimage("hinh_anh/traitim.png",g_render)==false)
	{
		thanhcong = false;
	}
}
void khoi_tao_sprite_monney(bool& thanhcong, SDL_Renderer* &g_render)
{
	bullet money;
	if (money.loadimage("hinh_anh/money.png",g_render) == false)
	{
		thanhcong = false;
	}
	else
	{
		sprite_monney[0].x = 0;
		sprite_monney[0].y = 0;
		sprite_monney[0].w = 22;
		sprite_monney[0].h = 22;

		sprite_monney[1].x = 30;
		sprite_monney[1].y = 0;
		sprite_monney[1].w = 22;
		sprite_monney[1].h = 22;

		sprite_monney[2].x = 52;
		sprite_monney[2].y = 0;
		sprite_monney[2].w = 22;
		sprite_monney[2].h = 22;

		sprite_monney[3].x = 73;
		sprite_monney[3].y = 0;
		sprite_monney[3].w = 22;
		sprite_monney[3].h = 22;

	}
}
void khoi_tao_am_thanh(bool& thanhcong)
{
	//tieng sungs
	tieng_sung = Mix_LoadWAV("am_thanh/tieng_sung.wav");
	if (tieng_sung == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}
	// tieng chim keeu 
	tieng_qua_keu = Mix_LoadWAV("am_thanh/tieng_qua_keu.wav");
	if (tieng_qua_keu == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}
	// tieng chim bi tieu diet 
	tieng_qua_chet = Mix_LoadWAV("am_thanh/tieng_qua_chet.wav");
	if (tieng_qua_chet == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}
	// tieng nguoi bij trung dan
	tieng_nguoi_trung_dan = Mix_LoadWAV("am_thanh/tieng_nguoi_trung_dan.wav");
	if (tieng_nguoi_trung_dan == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}
	// tieng nhat tien 
	tieng_nhat_duoc_tien = Mix_LoadWAV("am_thanh/beep.wav");
	if (tieng_nhat_duoc_tien == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}
	// tieng nhan vatj thua cuoc
	tieng_nguoi_that_bai = Mix_LoadWAV("am_thanh/nhanvat_that_bai.wav");
	if (tieng_nguoi_that_bai == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}
	// tieng quai doi trung dan 
	tieng_quaivat_trung_dan = Mix_LoadWAV("am_thanh/quai_vat_trung_dan.wav");
	if (tieng_quaivat_trung_dan == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}
	//tieng quai doi that bai 
	tieng_quaivat_that_bai = Mix_LoadWAV("am_thanh/quaivat_that_bai.wav");
	if (tieng_quaivat_that_bai == NULL)
	{
		cout << Mix_GetError() << '\n';
		thanhcong = false;
	}

	
}
void khoi_tao_TTF(bool& thanhcong,  SDL_Renderer* &g_render, TTF_Font* &g_font )
{
	g_font = TTF_OpenFont("font/font_chu.ttf", 15);
	
	if (g_font == NULL)
	{
		cout<<"Failed to load lazy font! SDL_ttf Error: %s\n"<< TTF_GetError();
		thanhcong = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 255,0 };
		g_text.set_color(textColor);
		if (!g_text.loadFromRenderedText(g_render, g_font))
		{
			cout<<"Failed to render text texture!\n";
			thanhcong = false;
		}
	}
}

void khoitaobangdan(object& nhanvat, SDL_Event& e)
{
	if (( e.button.button == SDL_BUTTON_LEFT)|| e.key.keysym.sym == SDLK_KP_ENTER)
	{
		if (nhanvat.getmang_song() > 0)
		{
			/// audio
			Mix_PlayChannel(-1, tieng_sung, 0);
			// create a bullet
			bullet* newbullet = new bullet();
			newbullet->loadimage("hinh_anh/bullet.png", g_render);
			newbullet->setposx(nhanvat.getposx() + is_left_to_right(nhanvat.gettrangthai()));
			newbullet->setposy(nhanvat.getposy() + 35);
			newbullet->settrangthai(nhanvat.gettrangthai());

			nhanvat.bulletnhanvat.push_back(newbullet);
		}
	}
}
int is_left_to_right(status trangthai)
{
	if (trangthai == left_to_right || trangthai == up_left_to_right)
		return 95;
	return -5;
}
// cac ham show
void khoi_tao_money( int vitrix, int vitriy)
{
	for (int i_money = 0; i_money < 4; i_money++)
	{
		bullet* l_money = new bullet();
		l_money->loadimage("hinh_anh/money.png",g_render);
		l_money->setkhunghinh(i_money);
		l_money->setposy(vitriy);
		l_money->setposx(vitrix + i_money * 22);
		money.push_back(l_money);
	}
}
void show_money(vector<bullet*> &money)
{
	for (int i= 0; i <money.size(); i++)
	{
		money.at(i)->render(&sprite_monney[money.at(i)->getkhunghinh()], g_render);
		if (money.at(i)->getposy() < DOCAOSAN - 22)
		{
			money.at(i)->setposy(money.at(i)->getposy() + 1);
		}

		if(isVaCham(nhanvat.getposx(),nhanvat.getposy(),100,spritenhanvat[nhanvat.getkhunghinh()/DELAY_SPRITE_NHANVAT].h,
					money.at(i)->getposx(), money.at(i)->getposy(),22,22)==true)
		{
			money.at(i)->setposx(money.at(i)->getposx() + (nhanvat.gettrangthai() == left_to_right ? -1 : 1));
			money.at(i)->setposy(money.at(i)->getposy() - 2);
			if (money.at(i)->getposx() < nhanvat.getposx() + 50)
			{
				nhanvat.set_money(nhanvat.get_money() + 1);
				money.at(i)->free();
				money.erase(money.begin() + i);
				// am thanh 
				Mix_PlayChannel(-1, tieng_nhat_duoc_tien, 0);
			}
		}
	}
}
void show_fire(int vitrix, int vitriy, int khunghinh)
{
	fire.setposx(vitrix);
	fire.setposy(vitriy);
	fire.render(&sprite_fire[khunghinh], g_render);
}
void show_trai_tim(int traitim)
{
	for (int it = 0; it <traitim; it++)
	{
		nhanvat.traitim[it]->loadimage("hinh_anh/traitim.png",g_render);
		nhanvat.traitim[it]->render(NULL, g_render);
	}
}
void show_score(int score)
{
	SDL_Color textColor = { 0, 255,0 };
	g_text.set_color(textColor);
	string score_str = "Money : " + to_string(score);
	g_text.set_textureText(score_str);
	g_text.loadFromRenderedText(g_render, g_font);

	g_text.render(g_render, SCREEN_WIDTH-250,5,NULL);
}
// ham va cham truyen vao toa do va chieu dai chieu rong cuar vat the1 vaf hai
bool isVaCham(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2)
{
	// toa do x
	bool X = ((x1 + w1 >= x2 && x1<x2+w2));
	bool Y = ((y1 + h1 > y2 && y2 + h2 > y1));

	return X && Y;
}
void show_menu()
{
	Text selections[2];

	SDL_Color color = { 71,187,156 }, color2 = { 255,255,0 };
	
	selections[0].set_textureText("PLAY NOW");
	selections[0].set_color(color);
	selections[0].loadFromRenderedText(g_render, g_font);
	
	selections[1].set_textureText("EXIT");
	selections[1].set_color(color);
	selections[1].loadFromRenderedText(g_render, g_font);

	SDL_Event e_event;
	bool quit_ = false;
	int toadox , toadoy;

	int vitrix[2] = { (SCREEN_WIDTH- selections[0].getWidth()) / 2,
		(SCREEN_WIDTH -selections[1].getWidth())/2 },
		vitriy[2] = { SCREEN_HEIGHT / 2 - 30, SCREEN_HEIGHT / 2 };
	while (quit_ == false)
	{
		while (SDL_PollEvent(&e_event) != 0)
		{
			if (e_event.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&toadox, &toadoy);
				for (int i = 0; i < 2; i++)
				{
					if (isVaCham(toadox, toadoy, 1, 1, vitrix[i], vitriy[i], selections[i].getWidth(), selections[i].getHeight()) == true)
					{
						selections[i].set_color(color2);
					}
					else
					{
						selections[i].set_color(color);
					}
				}
			}
			else
			{
				if (e_event.type == SDL_MOUSEBUTTONDOWN)
				{
					if (e_event.button.button == SDL_BUTTON_LEFT)
					{
						SDL_GetMouseState(&toadox, &toadoy);
						for (int i = 0; i < 2; i++)
						{
							if (isVaCham(toadox, toadoy, 1, 1, vitrix[i], vitriy[i], selections[i].getWidth(), selections[i].getHeight()) == true)
							{
								if (i == 0)
								{
									PLAY_GAME();
								}
								else
								{
									quit_ = true;
								}

								break;
							}
						}	
					}
				}
				else 
				if (e_event.type == SDL_QUIT)
				{
					quit_ = true;
				}
			}
		}
		SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(g_render);

		background_menu.render(NULL, g_render);
		for (int i = 0; i < 2; i++)
		{
			selections[i].loadFromRenderedText(g_render, g_font);
			selections[i].render(g_render, vitrix[i], vitriy[i],NULL);
		}
		SDL_RenderPresent(g_render);
	}


}
void PLAY_GAME()
{
	reset();
	bool quit = false;
	SDL_Event e;
	
	// KHOI TAO QUAI DOI

	while (quit == false)
	{
		// XU LY EVENT
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT) { quit = true; }

			XU_LY_DI_CHUYEN(background, nhanvat, e);
			// them dan vao bang khi nhan chuot trai va am 
			khoitaobangdan(nhanvat, e);
		}

		SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(g_render);
		// SHOW BACKGROUND 
		background.render(NULL, g_render);

		// SHOW NHANVAT 
		nhanvat.render(&spritenhanvat[nhanvat.getkhunghinh() / DELAY_SPRITE_NHANVAT], g_render);

		XU_LY_SPRITE_NHANVAT(nhanvat);

		XU_LY_SPRITE_QUAI_BAY();

		XU_LY_PRITE_QUAI_DOI(QUAI_DOI);

		XU_LY_DAN_NHAN_VAT(nhanvat);

		show_trai_tim(nhanvat.getmang_song());

		show_money(money);

		show_score(nhanvat.get_money());

		//================================================================
		end_game(quit);
		SDL_RenderPresent(g_render);
	}
}
void end_game(bool &quit)
{
	if (nhanvat.getmang_song() < 0)
	{
		Mix_PlayChannel(-1, tieng_nguoi_that_bai, 0);
		
		quit = true;
	}
	if (QUAI_DOI.getsolantrungdan() > solanbantrungmax_QUAI_DOI)
	{

		
		//bom

		if (fire.getkhunghinh() / 2 < 8)
		{
			show_fire(QUAI_DOI.getposx(), QUAI_DOI.getposy(), fire.getkhunghinh() / 2);
			fire.setkhunghinh(fire.getkhunghinh() + 1);
		}
		else {
			//sau khi bom no 
			if (fire.getkhunghinh() / 2 == 8)
			{
				Mix_PlayChannel(-1, tieng_quaivat_that_bai, 0);
				fire.setkhunghinh( 20);// chi cho am tanh chay mot lan 

			}
			gift_money.setposy(DOCAOSAN - 268);
			gift_money.setposx(QUAI_DOI.getposx() - 200);
			gift_money.render(NULL, g_render);

			if (isVaCham(nhanvat.getposx()-100, nhanvat.getposy(), 120, 127, gift_money.getposx(), gift_money.getposy(), 300, 500) == true)
			{
				nhanvat.set_money(nhanvat.get_money() + 1000);
				
				quit = true;
			}
		}
	
	}
}
void reset()
{
	
	QUAI_DOI.setsolantrungdan(0);
	QUAI_DOI.BULLET.loadimage("hinh_anh/bullet_quai.png",g_render);

	fire.loadimage("hinh_anh/fire.png",g_render);
	gift_money.loadimage("hinh_anh/gift_money.png",g_render);
	
	//set up nhan vat 
	nhanvat.setposx(LIMIT_FRIRST);
	nhanvat.setposy(0);
	nhanvat.setmang_song(MANG_SONG_MAX);
	nhanvat.setkhunghinh(6 * DELAY_SPRITE_NHANVAT);
	nhanvat.settrangthai(left_to_right);
	nhanvat.set_money(0);

	background.setposx(0);

	
	// XOA CHIM BAY KHOI TAO LAI

	for (int i = 0; i < chimbay.size(); i++)
	{
		chimbay[i]->free();
		chimbay.erase(chimbay.begin() + i);
	}
	khoi_tao_quaibay();
	// xoa het tien 
	for (int j = 0; j < money.size(); j++)
	{
		money[j]->free();
		money.erase(money.begin() + j);
	}
}