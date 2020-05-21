
#include"Text.h"
bool Text::loadFromRenderedText(SDL_Renderer* &g_render , TTF_Font* &g_font)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(g_font, textureText.c_str(), textColor);

	if (textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
		mtexture = SDL_CreateTextureFromSurface(g_render, textSurface);
		if (mtexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mwidth = textSurface->w;
			mheight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	//Return success
	return mtexture != NULL;
}
//ket xuat
void Text:: render(SDL_Renderer* &g_render, int x, int y,SDL_Rect* clip)

{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mwidth, mheight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	
	//Render to screen
	SDL_RenderCopyEx(g_render, mtexture, clip, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

Text::Text()
{
	mwidth = 0;
	mheight = 0;
	mtexture = NULL;
	textColor = { 0,0,0 };
	size_text = 20;
	textureText = "NULL";

}

Text ::~Text()
{
	free();
}
void Text::free()
{
	if (mtexture != NULL)
	{
		SDL_DestroyTexture(mtexture);
		mwidth = 0;
		mheight = 0;
	}
}