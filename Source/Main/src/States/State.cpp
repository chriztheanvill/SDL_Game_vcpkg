#include "State.h"
#include "./GameStateManager.h"

// State::State(GameStateManager& gsm, const std::string& name)
State::State(GameStateManager& gsm, std::string_view name)
	: mGameStateManager(gsm)
	, Node(nullptr, name)
{
	Logger::Debug(LogType::Log, "### State::Constructor :", GetName( ));
}

State::~State( )
{
	Logger::Debug(LogType::Log, "### ~State::Destructor :", GetName( ));
}

// State* State::Update(const float& deltaTime) { return nullptr; }
std::unique_ptr<State> State::Update(const float& deltaTime) { return nullptr; }
// std::shared_ptr<State> State::Update(const float& deltaTime) { return
// nullptr; }

void State::Render( ) {}
void State::Load( ) {}
void State::Events(SDL_Event& event) {}

void State::EnterState( ) {}
void State::ExitState( ) {}