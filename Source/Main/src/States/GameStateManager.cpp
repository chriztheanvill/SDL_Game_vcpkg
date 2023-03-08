#include "GameStateManager.h"

#include "../States/State.h"
#include "./GameState.h"
#include "./MenuState.h"
#include "../Core/Engine.h"
#include "../Core/TextureManager.h"

#include <iostream>

GameStateManager::GameStateManager(SDL_Renderer& render)
	:	//
	// Shared
	// : mGameState(std::make_shared<GameState>(*this))
	mRender(render)
	// mRender(&render)
	, mTextureManager(std::make_unique<TextureManager>( ))
{
	Logger::Debug(LogType::Log, "--- GameStateManager::Constructor ---");
	Load( );
}

GameStateManager::~GameStateManager( )
{
	if (mCurrent) mCurrent->ExitState( );

	// delete mCurrent;
	// delete mPrev;
	// delete mTextureManager;
	mCurrent = nullptr;
	mPrev = nullptr;
	mTextureManager = nullptr;
	Logger::Debug(LogType::Log, "--- ~GameStateManager ---");
}

void GameStateManager::Load( )
{
	mGameState = std::make_unique<MenuState>(*this);
	mGameState->SetName("MenuState");
	mTextureManager->SetName("Texture Manager MenuState");
	mTextureManager->SetRender(mRender);
	// mTextureManager->SetParent(mGameState.get( ));

	mIsRunning = true;

	if (mGameState) { SetState(mGameState); }
	else
	{
		Logger::Debug(LogType::Error,
					  "GameStateManager::Constructor ERROR!!! No state ---");
		exit(1);
	}
}

std::unique_ptr<State> GameStateManager::GetGameState( )
{
	// std::unique_ptr<GameState> tmp = std::make_unique<GameState>(*this);
	// return tmp;
	return std::make_unique<GameState>(*this);
}

TextureManager& GameStateManager::GetTextureManager( )
{
	return *mTextureManager;
}

void GameStateManager::Update(const float& deltaTime)
{
	Logger::Debug(LogType::Log, "DeltaTime: ", deltaTime);

	if (mCurrent && mIsRunning)
	{
		Events( );
		// Switching between Game modes: (Main menu, Game, Pause)
		std::unique_ptr<State> tmp = mCurrent->Update(deltaTime);
		// std::shared_ptr<State> tmp = mCurrent->Update(deltaTime);
		Render( );
		if (tmp)
		{
			Logger::Debug(LogType::Debug,
						  "GameStateManager::Update Updating +++ tmp: ",
						  &tmp,
						  " - ",
						  tmp->GetName( ));

			SetState(tmp);
		}
	}
}

void GameStateManager::Render( )
{
	// System
	// Paint color
	SDL_SetRenderDrawColor(&mRender, 60, 60, 60, 255);
	SDL_RenderClear(&mRender);

	/* ################################################# */
	// Game

	mCurrent->Render( );

	/* ################################################# */

	// System
	// Clean the screen
	SDL_RenderPresent(&mRender);
}

void GameStateManager::Events( )
{
	SDL_Event event { };
	while (SDL_PollEvent(&event))
	{
		/* ======== SYSTEM ======== */
		switch (event.type)
		{
			case SDL_QUIT: mIsRunning = false; break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_q ||
					event.key.keysym.sym == SDLK_ESCAPE)
				{
					mIsRunning = false;
					Logger::Debug(LogType::Log, "Quitting game by Q.");
				}
		}
		/* ======== ~SYSTEM ======== */

		/* ======== Game ======== */
		mCurrent->Events(event);
		/* ======== ~Game ======== */
	}
	//
}

// void GameStateManager::SetState(std::shared_ptr<State>& state)
void GameStateManager::SetState(std::unique_ptr<State>& state)
{
	mPrev = std::move(mCurrent);
	mCurrent = std::move(state);

	// mPrev = mCurrent;
	// mCurrent = state;
	// // mCurrent = std::move(state);

	Logger::Debug(LogType::Log, "GameStateManager::SetState");

	if (mPrev)
	{
		Logger::Debug(LogType::Debug,
					  "GameStateManager::SetState mPrev: ",
					  &mPrev,
					  " - "s,
					  mPrev->GetName( ));
		// std::cout << "\nmPrev: " << &mPrev << " - " << mPrev->GetName( )
		// 		  << "\n";
		mPrev->ExitState( );
	}
	if (mCurrent)
	{
		Logger::Debug(LogType::Debug,
					  "GameStateManager::SetState mCurrent: ",
					  &mCurrent,
					  " - "s,
					  mCurrent->GetName( ));
		// std::cout << "\nmCurrent: " << &mCurrent << " - "
		// 		  << mCurrent->GetName( ) << "\n";
		mCurrent->EnterState( );
	}
}