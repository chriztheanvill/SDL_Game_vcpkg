#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL2/SDL_image.h>

#include "../Core/Node.h"

class Engine;

class TextureManager : public Node
{
  public:
	TextureManager(Node* parent = nullptr);
	// TextureManager(Engine& engine);
	~TextureManager( );

	SDL_Texture* Load(std::string_view name = "", std::string_view path = "");
	// SDL_Texture* Load(const std::string& name = "",
	// 					  const std::string& path = "");

	SDL_Texture* GetTexture(std::string_view name = "");
	// SDL_Texture* GetTexture(const std::string& name = "");

	void SetRender(SDL_Renderer& render) { mRender = &render; }
	// void SetEngine(Engine& engine) { mEngine = &engine; }

  private:
	std::map<std::string_view, SDL_Texture*> mTextures;
	// std::map<const std::string, SDL_Texture*> mTextures;
	SDL_Renderer* mRender;
	// Engine* mEngine;
	// Engine& mEngine;
};

#endif	 // TEXTUREMANAGER_H
