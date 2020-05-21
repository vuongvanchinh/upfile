#ifndef TEXT_H
#define TEXT_H
#include"GENERAL.h"

class Text
{
public:
	//khoi tao bien 
	Text();

	//huy
	~Text();

	//Creates image from font string
	bool loadFromRenderedText(SDL_Renderer* &g_render, TTF_Font * &g_font);

	//giai phong
	void free();

	void set_textureText(string textureText_) { textureText = textureText_; }
	void set_color(SDL_Color& color) { textColor = color; }

	void set_size_text(int size_text_) { size_text = size_text_; }
	//ket xuat ra man hinh
	void render(SDL_Renderer* &g_render, int x, int y, SDL_Rect* clip);
	int get_size_text() { return size_text; }
	//kichs thuowcs
	int getWidth() { return mwidth; }
	int getHeight() { return mheight; }
	SDL_Texture* get_mtexture() { return mtexture; }
private:

	SDL_Texture* mtexture;
	string textureText;
	SDL_Color textColor;
	int mwidth;
	int mheight;
	int size_text;
};

#endif // !TEXT_H

