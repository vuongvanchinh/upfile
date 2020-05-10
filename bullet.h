#ifndef BULLET_H
#define BULLET_H
#include"GENERAL.h"

class bullet
{
public:
	bullet();
	~bullet();
	void render(SDL_Rect* clip, SDL_Renderer* &g_render);
	bool loadimage(std::string path, SDL_Renderer* &g_render);
	void free();

	void setposx(int posx_) { posx = posx_; }
	int getposx() { return posx;}

	void setposy(int posy_) { posy = posy_; }
	int getposy() { return posy;}
	
	void settrangthai(status trangthai_) { trangthai = trangthai_; }

	status gettrangthai() { return trangthai; }

	void setkhunghinh(int khunghinh_) { khunghinh = khunghinh_; }
	int getkhunghinh() { return khunghinh; }

private:
	int posx, posy;
	int mwidth, mheight;
	int khunghinh;
	SDL_Texture* mtexture;
	status trangthai;

};
#endif // !BULLET_H

