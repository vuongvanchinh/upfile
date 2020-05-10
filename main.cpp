
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string>
#include<vector>
#include<iostream>
#include<cmath>
#include<ctime>
#include<cstdlib>

using  namespace  std;

const int SCREEN_WIDTH = 1400;
const int SCREEN_HEIGHT = 550;

enum status {
	lefttoright,
	righttoleft
};

SDL_Window* g_window = NULL;
SDL_Renderer* g_render = NULL;
SDL_Texture* g_texture = NULL;
SDL_Rect sprite[2];

bool init();
bool loadmedia();
void close();

class bulletobject
{
public:
	void handle();

	void free();

private:
	int posx;
	int posy;
	status trangthai;
};
class doituong // anh nen anh nhan vat
{
public:
	doituong();//khoi tao
	~doituong();// huy doi tuong
	void free();// giai phong

	bool loadimage(std::string  path);

	void render( SDL_Rect* clip);

	int getwidth();
	int getheight();
	int posx, posy;// vitri in ra man hinh
	//ranhf rieng cho dan va co ro na
	status trangthai;
private:
	int mwidth;
	int mheight;
	SDL_Texture* mtexture;
};
//=================================================================================

doituong::doituong()
{
	mwidth = 0;
	mheight = 0;
	mtexture = NULL;
}

doituong::~doituong()
{
	free();
}
int doituong::getheight() { return mheight; }
int doituong::getwidth() { return mwidth; }
//===============================================
bool doituong::loadimage(std::string path)
{
	SDL_Texture* newtexture = NULL;
	SDL_Surface* loadedimage = IMG_Load(path.c_str());
	if (loadedimage == NULL)
	{
		cout << "loadedimage= NULL" << IMG_GetError() << "\n";
	}
	else
	{
		SDL_SetColorKey(loadedimage, SDL_TRUE, SDL_MapRGB(loadedimage->format, 0, 255, 255));


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
void doituong::free()
{
	if (mtexture != NULL)
	{
		SDL_DestroyTexture(mtexture);
		mtexture = NULL;
		mwidth = 0;
		mheight = 0;
	}
}

void doituong::render( SDL_Rect* clip)
{
	SDL_Rect pos = {posx,posy, mwidth, mheight };// vi tri va kick thuoc in ra
	//ham inra 
	if (clip != NULL)
	{
		pos.w = clip->w;
		pos.h = clip->h;

	}
	SDL_RenderCopy(g_render, mtexture, clip, &pos);
}
//===============================================================================Doituong background;
doituong background, nhanvat;

vector<doituong> nhomcorona;
vector<doituong*> bangdan;
vector<doituong*> corona;
//==========================================================cac ham khoi tao===============
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
		g_window = SDL_CreateWindow("Ban Ga", SDL_WINDOWPOS_CENTERED,
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
			}
		}
	}
	return thanhcong;
}

bool loadmedia()
{
	bool thanhcong = true;
	if (background.loadimage("hinh_anh/background.png") == false)
	{
		cout << "load anh nen that bai:";
		thanhcong = false;
	}

	if (nhanvat.loadimage("hinh_anh/nhanvat.png") == false)
	{
		cout << "load anh nhan vat that bai:";
		thanhcong = false;
	}
	else
	{
		sprite[0].x = 0;
		sprite[0].y = 0;
		sprite[0].w = 146;
		sprite[0].h = 146;

		sprite[1].x = 146;
		sprite[1].y = 0;
		sprite[1].w = 146;
		sprite[1].h = 146;

	}

	return thanhcong;
}
void close()
{
	nhanvat.free();
	background.free();
	SDL_DestroyWindow(g_window);
	SDL_DestroyRenderer(g_render);
	SDL_DestroyTexture(g_texture);
	g_window = NULL;
	g_render = NULL;

	SDL_Quit();
	IMG_Quit();

}

int main(int agrv, char* agrs[])
{
	if (init() == false)
	{
		cout << "khoi tao that bai";
	}
	else
	{
		if (loadmedia() == false)
		{
			cout << "load media that bai";
		}
		else
		{
			
			int khunghinh = 0;
			bool quit = false;
			SDL_Event e;

			int sovirut = 10;

			int seed;
			for (int i = 0; i < 10; i++)
			{
				doituong* corona_element = new doituong();
				corona_element->loadimage("hinh_anh/chimbay.png");
				seed = time(NULL);
				srand(seed);
				corona_element->posx = SCREEN_WIDTH - i*50;
				
				corona_element->posy = rand()%720 +50+i*60;
				corona.push_back(corona_element);
			}


			while (quit == false)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					if (e.type == SDL_QUIT) { quit = true; }
					else
					{
						if (e.type == SDL_MOUSEMOTION)
						{
							SDL_GetMouseState(&nhanvat.posx, &nhanvat.posy);

							if (nhanvat.posx > SCREEN_WIDTH - 146)
							{
								nhanvat.posx = SCREEN_WIDTH - 146;
							}
							if (nhanvat.posy > SCREEN_HEIGHT - 146)
							{
								nhanvat.posy = SCREEN_HEIGHT - 146;
							}
						}
						else
						{
							if (e.type == SDL_MOUSEBUTTONDOWN)
							{
								doituong* bullet=new doituong();
								bullet ->loadimage("hinh_anh/bullet.png");
								
								if (nhanvat.posx > (SCREEN_WIDTH / 2) - 73)
								{
									bullet->posx = nhanvat.posx;
									bullet->posy = nhanvat.posy + 100;
									bullet->trangthai = righttoleft;
								}
								else
								{
									bullet->posx = nhanvat.posx + 146;
									bullet->posy = nhanvat.posy + 100;
									bullet->trangthai = lefttoright;
								}
								bangdan.push_back(bullet);
								 
							}
						}
						
					}
				}
				SDL_SetRenderDrawColor(g_render, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(g_render);
				//currently = &sprite[lap / 4];

				background.render(NULL);

				if (nhanvat.posx > (SCREEN_WIDTH / 2)-73)
				{
					khunghinh = 1;
				}
				else {
					khunghinh = 0;
				}
				nhanvat.render(&sprite[khunghinh]);
				for (int i = 0; i < bangdan.size(); i++)
				{
					bangdan[i]->render(NULL);
					if (bangdan[i]->trangthai == righttoleft)
					{
						bangdan[i]->posx-=5;
					}
					else
					{//left to right
						bangdan[i]->posx+=5;
					}
					// khi bay ra ngoai man hinh
					if (bangdan[i]->posx > SCREEN_WIDTH || bangdan[i]->posx < 0)
					{
						bangdan[i]->free();
						bangdan.erase(bangdan.begin() + i);
					}
				}
				for (int i = 0; i < 10; i++)
				{
					corona[i]->render(NULL);

					corona[i]->posx--;
					///hhhhhhhhhhhhhhhhhhhhh
					for (int j = 0; j < bangdan.size(); j++)
					{
						if (bangdan[i]->posx >= corona[i]->posx && bangdan[i]->posx <= corona[i]->posx + 50)
						{
							corona[i]->posx = SCREEN_WIDTH;
							break;
						}
					}

					if (corona[i]->posx < -100  )
					{
						corona[i]->posx = SCREEN_WIDTH;
					}
				}

				//int sovirut =10 + rand() % +1;
				
				//corona.render(NULL);

				SDL_RenderPresent(g_render);
			}
		}
	}
	close();
	return 0;
}




