#ifndef OBJECT_H
#define OBJECT_H
#include"GENERAL.h"
#include"bullet.h"

class object
{
public:
	
	object();//khoi tao
	~object();// huy doi tuong
	void free();// giai phong

	bool loadimage(std::string  path, SDL_Renderer* &g_render);

	void render(SDL_Rect* clip, SDL_Renderer* &g_render);
	//void render_mangsong(SDL_Rect* clip);

	int getwidth();
	int getheight();

	int getposx() { return posx; }
	void setposx(int posx_) { posx = posx_; }

	int getposy() { return posy; }
	void setposy(int posy_) { posy = posy_; }

	int getkhunghinh() { return khunghinh; }
	void setkhunghinh(int khunghinh_) { khunghinh = khunghinh_; }

	status gettrangthai() { return trangthai; }
	void settrangthai(status trangthai_) { trangthai = trangthai_; }

	int getmang_song() { return mang_song; }
	void setmang_song(int mang_song_) { mang_song = mang_song_; }

	int get_money() { return money; }
	void set_money(int money_) { money = money_; }
	vector<bullet*> bulletnhanvat, traitim;

private:
	int posx, posy;// vitri in ra man hinh
	int khunghinh;
	status trangthai;
	int mwidth;
	int mheight;
	SDL_Texture* mtexture;
	int mang_song;
	int money;
};

#endif // !OBJECT_H
