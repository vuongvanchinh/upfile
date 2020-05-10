#include"object.h"

//======================= classs object=================
object::object()
{
	mwidth = 0;
	mheight = 0;
	mtexture = NULL;
	trangthai = left_to_right;
	posx = 0;
	posy = 0;
	khunghinh = 0;
	mang_song = MANG_SONG_MAX;
	money = 0;
	for (int i = 0; i < MANG_SONG_MAX; i++)
	{
		bullet* heart = new bullet();
		//heart->loadimage("hinh_anh/traitim.png");
		heart->setposx(i * 27);
		heart->setposy(0);
		traitim.push_back(heart);
	}
}

object::~object()
{
	free();
}
int object::getheight() { return mheight; }
int object::getwidth() { return mwidth; }
//===============================================
bool object::loadimage(std::string path, SDL_Renderer* &g_render)
{
	free();
	SDL_Texture* newtexture = NULL;
	SDL_Surface* loadedimage = IMG_Load(path.c_str());
	if (loadedimage == NULL)
	{
		cout << "loadedimage = NULL" << IMG_GetError() << "\n";
	}
	else
	{

		SDL_SetColorKey(loadedimage, SDL_TRUE, SDL_MapRGB(loadedimage->format, 255, 255, 255));


		newtexture = SDL_CreateTextureFromSurface(g_render, loadedimage);
		if (newtexture == NULL)
		{
			cout << "newtexture = NULL" << SDL_GetError() << "\n";
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
void object::free()
{
	if (mtexture != NULL)
	{
		SDL_DestroyTexture(mtexture);
		mtexture = NULL;
		mwidth = 0;
		mheight = 0;
		for (int i = 0; i < traitim.size(); i++)
		{
			delete	traitim[i];
		}
	}
}
/// ket xuat ra man hinh;
void object::render(SDL_Rect* clip, SDL_Renderer* &g_render)
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

