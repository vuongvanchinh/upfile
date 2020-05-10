#ifndef QUAI_OBJECT_H
#define QUAI_OBJECT_H


#include"GENERAL.h"
#include"bullet.h"

class quai_object
{
public:
	quai_object();
	~quai_object();
	bool loadimage(std::string path, SDL_Renderer* &g_render);

	void render(SDL_Rect* clip, SDL_Renderer* &g_render);
	void free();

	void setposx(int posx_) { posx = posx_; }
	int getposx() { return posx; }

	void setposy(int posy_) { posy = posy_; }
	int getposy() { return posy; }
	
	
	void settrangthai(status trangthai_) { trangthai = trangthai_; }
	status gettrangthai() { return trangthai; }

	void setkhunghinh(int khunghinh_) { khunghinh = khunghinh_; }
	int getkhunghinh() { return khunghinh; }

	int getmwidth() { return mwidth; }
	int getmheight() { return mheight; }

	void setsolantrungdan(int solantrungan_) { solantrungdan = solantrungan_; }
	int getsolantrungdan() { return solantrungdan; }

	bullet BULLET;

private:
	int posx, posy;
	status trangthai;
	int khunghinh;
	int solantrungdan;
	int mwidth;
	int mheight;
	SDL_Texture* mtexture;
};
#endif // !QUAI_OBJECT_H
