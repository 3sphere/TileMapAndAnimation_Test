#include "Character.h"
#include "Game.h"
#include "AnimSpriteComponent.h"

Character::Character(Game* game) : Actor(game), mRightSpeed(0.0f), mState(Idle)
{
	mAnim = new AnimSpriteComponent(this);
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
	mAnim->SetAnimTextures(textures);
	mAnim->SetAnimFPS(4.0f);
	mAnim->AddAnim("Idle", 0, 2);
	mAnim->AddAnim("Walk", 3, 8);
	mAnim->SetAnim("Idle");
	mAnim->SetFlip(SDL_FLIP_HORIZONTAL);
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
	mRightSpeed = 0.0f;
	mAnim->SetAnim("Idle");
	mAnim->SetAnimFPS(4.0f);
	
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 200.0f;
		mAnim->SetFlip(SDL_FLIP_NONE);
		mAnim->SetAnim("Walk");
		mAnim->SetAnimFPS(10.0f);
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 200.0f;
		mAnim->SetFlip(SDL_FLIP_HORIZONTAL);
		mAnim->SetAnim("Walk");
		mAnim->SetAnimFPS(10.0f);
	}
}