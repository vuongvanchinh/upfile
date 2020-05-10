#include"quai_object.h"
///============================classs quai_object ====================================
quai_object::quai_object()
{
	mwidth = 0;
	mheight = 0;
	mtexture = NULL;
	trangthai = right_to_left;
	posy = 50;
	posx = 1000;
	khunghinh = 0;
	solantrungdan = 0;
	BULLET.setposy(DOCAOSAN - 200);
	
}

quai_object::~quai_object()
{
	free();
}
// load anh
bool  quai_object::loadimage(std::string path, SDL_Renderer* &g_render)
{
	//free();
	SDL_Texture* newtexture = NULL;
	SDL_Surface* loadedimage = IMG_Load(path.c_str());
	if (loadedimage == NULL)
	{
		cout << "loadedimage= NULL" << IMG_GetError() << "\n";
	}
	else
	{
		SDL_SetColorKey(loadedimage, SDL_TRUE, SDL_MapRGB(loadedimage->format, 255, 255, 255));
		newtexture = SDL_CreateTextureFromSurface(g_render, loadedimage);
		if (newtexture == NULL)
		{
			cout << "newtexture= NULL" << SDL_GetError() << "\n";
		}
		else
		{
			mwidth = loadedimage->w;
			mheight = loadedimage->h;
		}
		SDL_FreeSurface(loadedimage);
	}
	mtexture = newtexture;
	return mtexture != NULL;
}
// ham huy
void  quai_object::free()
{
	if (mtexture != NULL)
	{
		SDL_DestroyTexture(mtexture);
		mtexture = NULL;
		mwidth = 0;
		mheight = 0;
		posx = 0;
		posy = 0;
		khunghinh = 0;
		BULLET.free();
	}
}
/// ket xuat ra man hinh;
void quai_object::render(SDL_Rect* clip, SDL_Renderer* &g_render)
{
	SDL_Rect pos = { posx,posy, mwidth, mheight };// vi tri va kick thuoc in ra
	//ham inra
	if (clip != NULL)
	{
		pos.w = clip->w;
		pos.h = clip->h;
	}
	SDL_RenderCopy(g_render, mtexture, clip, &pos);
}

