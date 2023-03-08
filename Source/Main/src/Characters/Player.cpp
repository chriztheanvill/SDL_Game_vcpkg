#include "Player.h"
// #include <fmt/color.h>
#include "../States/GameStateManager.h"
#include "../Core/Engine.h"

Player::Player(Node* node, GameStateManager& gsm)
	: mGameStateManager(gsm)
	, mRigidBody(this)
	, Node(node, "Player")
{
	Logger::Debug(LogType::Log, "--- Player::Constructor ---");

	SetName("Player");

	mPosition.SetVector(Vector2D::Zero( ));
	// mPosition.SetVector({ 50, 10 });

	mCollision = { static_cast<int>(mPosition.GetX( )),
				   static_cast<int>(mPosition.GetX( )),
				   20,
				   20 };
}

Player::~Player( )
{
	Logger::Debug(LogType::Log, "~GameState::Player::Destructor");
	// NodeLogComplete( );
}

// void Player::SetSprite(const std::string& name, const std::string& path)
void Player::SetSprite(const std::string& name, std::string_view path)
{
	// mPlayerTexture = mGameStateManager.GetTextureManager( )->Load(name,
	// path);
	mPlayerTexture = mGameStateManager.GetTextureManager( ).Load(name, path);
}

void Player::Update(const float& deltaTime)
{
	mRigidBody.Update(deltaTime);
	// mPosition.Transform(mRigidBody.Pos( ));
	mPosition.Transform(mRigidBody.Velocity( ));

	Logger::Debug(LogType::Debug,
				  "Player::mPlayer:",
				  " x: "sv,
				  Position( ).GetX( ),
				  " - y: "sv,
				  Position( ).GetY( ));

	mCollision = SDL_Rect { static_cast<int>(mPosition.GetX( )),
							static_cast<int>(mPosition.GetY( )),
							100,
							150 };
}

void Player::Render( )
{
	// SDL_SetRenderDrawColor(mGameStateManager.GetEngine( ).GetRender( ),
	SDL_SetRenderDrawColor(&mGameStateManager.GetRender( ), 255, 255, 255, 255);

	// SDL_RenderFillRect(mGameStateManager.GetEngine( ).GetRender( ),
	SDL_RenderFillRect(&mGameStateManager.GetRender( ), &mCollision);

	// SDL_RenderCopy(mGameStateManager.GetEngine( ).GetRender( ),
	SDL_RenderCopy(&mGameStateManager.GetRender( ),
				   mPlayerTexture,
				   nullptr,
				   &mCollision);
}

void Player::Events(SDL_Event& event)
{
	Logger::Debug(LogType::Debug, "GameState::Events::Player");
	switch (event.type)
	{
		// case SDL_PRESSED:
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_d)
			{
				Logger::Debug(LogType::Log,
							  "GameState::Events::Player::Input::KeyDown::d");
				mRigidBody.ApplyForceX(50);
			}
			else if (event.key.keysym.sym == SDLK_a)
			{
				Logger::Debug(LogType::Log,
							  "GameState::Events::Player::Input::KeyDown::a");
				mRigidBody.ApplyForceX(-50);
			}
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_d ||
				event.key.keysym.sym == SDLK_a)
			{
				Logger::Debug(
					LogType::Log,
					"++++++++++++++++GameState::Events::Player::UnsetX");
				mRigidBody.UnsetForceX( );
			}
			break;

			//
			// if (event.key.keysym.sym == SDLK_w)
			// {
			// 	std::cout << "\nGameState::Events::Input::w";
			// }
			// else if (event.key.keysym.sym == SDLK_s)
			// {
			// 	std::cout << "\nGameState::Events::Input::s";
			// }
			// else
			// {
			// 	std::cout << "\nGameState::Events::UnsetY";
			// 	velocity.UnsetForceY( );
			// }
	}
}
