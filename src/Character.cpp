#include "Character.h"
#include "Game.h"
#include "AnimSpriteComponent.h"

Character::Character(Game* game) : Actor(game), mRightSpeed(0.0f), mState(Idle)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> textures = {
		game->GetTexture("Assets/Sprites/adventurer-idle-00.png"),
		game->GetTexture("Assets/Sprites/adventurer-idle-01.png"),
		game->GetTexture("Assets/Sprites/adventurer-idle-02.png"),
		game->GetTexture("Assets/Sprites/adventurer-run-00.png"),
		game->GetTexture("Assets/Sprites/adventurer-run-01.png"),
		game->GetTexture("Assets/Sprites/adventurer-run-02.png"),
		game->GetTexture("Assets/Sprites/adventurer-run-03.png"),
		game->GetTexture("Assets/Sprites/adventurer-run-04.png"),
		game->GetTexture("Assets/Sprites/adventurer-run-05.png")
	};
	asc->SetAnimTextures(textures);
	asc->SetAnimFPS(4.0f);
	asc->AddAnim("Idle", 0, 2);
	asc->AddAnim("Walk", 3, 8);
	asc->SetAnim("Idle");
	asc->SetFlip(SDL_FLIP_HORIZONTAL);
}

void Character::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	if (pos.x < 550.0f)
	{
		pos.x = 550.0f;
	}
	if (pos.x > 1000.0f)
	{
		pos.x = 1000.0f;
	}
	SetPosition(pos);
}

void Character::ProcessKeyboard(const uint8_t* state)
{
	// Get the AnimSpriteComponent from the Actor's components vector
	std::vector<Component*> comps = std::move(GetComponents());
	AnimSpriteComponent* asc = nullptr;
	for (auto& c : comps)
	{
		if (asc = dynamic_cast<AnimSpriteComponent*>(c)) // the condition returns true if the component under scrutiny is an AnimSpriteComponent
			break;
	}

	mRightSpeed = 0.0f;
	asc->SetAnim("Idle");
	asc->SetAnimFPS(4.0f);
	
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 200.0f;
		asc->SetFlip(SDL_FLIP_NONE);
		asc->SetAnim("Walk");
		asc->SetAnimFPS(10.0f);
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 200.0f;
		asc->SetFlip(SDL_FLIP_HORIZONTAL);
		asc->SetAnim("Walk");
		asc->SetAnimFPS(10.0f);
	}
}