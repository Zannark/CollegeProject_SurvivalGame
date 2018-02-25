#include "Animator.h"

Engine::Core::Cache<Engine::Core::Animator> Engine::Core::AnimationCache::Cache = Engine::Core::Cache<Engine::Core::Animator>();

void Engine::Core::InitAnimatorCache(void)
{
	AnimationCache::Cache.Add("Assets\\TestAnimation.png", Animator("Assets\\TestAnimation.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/Background.png", Animator("Assets/Background.png", Vector2i(800, 600)));
	AnimationCache::Cache.Add("Assets/Player.png", Animator("Assets/Player.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/TestBuilding.png", Animator("Assets/TestBuilding.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/Enemy.png", Animator("Assets/Enemy.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/PlayerWeapon.png", Animator("Assets/PlayerWeapon.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/SpeedPowerUp.png", Animator("Assets/SpeedPowerUp.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/DamagePowerUp.png", Animator("Assets/DamagePowerUp.png", Vector2i(32, 32)));
}

Engine::Core::Animator::Animator(string SpriteSheetPath, Vector2i FrameSize)
{
	this->DefaultAnimation = "";
	this->AnimationFrameSize = FrameSize;

	this->Tex = make_shared<Texture>();

	if (!this->Tex->loadFromFile(SpriteSheetPath))
	{
		string ErrorMessage = string("Failed to load the sprite sheet at location: ") + SpriteSheetPath;
		throw runtime_error(ErrorMessage);
	}

	AnimationInformation DummyInfo;
	DummyInfo.FrameLength = 0;

	this->AnimationSprite = make_shared<Sprite>();
	this->AnimationSprite->setTexture(*this->Tex);
	this->FrameTime = 0;
	this->CurrentFrameNumber = 0;
	this->CurrentAnimation = DummyInfo;
}

Engine::Core::Animator::~Animator()
{
}

void Engine::Core::Animator::AddAnimation(AnimationInformation Animaiton, bool IsDefaultAnimation)
{
	if (IsDefaultAnimation)
		this->DefaultAnimation = Animaiton.AnimationName;

	this->Animations[Animaiton.AnimationName] = Animaiton;
	this->FrameTime = Animaiton.FrameLength;
}

void Engine::Core::Animator::SwitchAnimation(string AnimationName)
{
	if (this->Animations.find(AnimationName) == this->Animations.end())
		throw runtime_error(string("Unable to find animation with the name: ") + AnimationName);
	
	this->CurrentFrameNumber = 0;
	this->FrameTime = this->CurrentAnimation.FrameLength + 1;
	this->CurrentAnimation = this->Animations[AnimationName];
}

void Engine::Core::Animator::SwitchToDefault(void)
{
	if (this->DefaultAnimation.empty())
		throw runtime_error("There is no default animation assigned.");

	this->SwitchAnimation(this->DefaultAnimation);
}

void Engine::Core::Animator::PlayAnimation(float dt)
{
	///For ease
	const unsigned int AnimationLength = this->CurrentAnimation.AnimationLength - 1;

	if (this->FrameTime >= this->CurrentAnimation.FrameLength)
	{
		this->CurrentFrame = IntRect(this->CurrentFrameNumber * this->AnimationFrameSize.x, this->CurrentAnimation.YAxisPosition, this->AnimationFrameSize.x, this->AnimationFrameSize.y);
		this->AnimationSprite->setTextureRect(this->CurrentFrame);
		this->FrameTime = 0;
	
		if (this->CurrentFrameNumber == AnimationLength)
			this->CurrentFrameNumber = 0;
		else
			this->CurrentFrameNumber += 1;
	}
	else
		this->FrameTime += dt;
}

void Engine::Core::Animator::Draw(RenderWindow * Wnd)
{
	Wnd->draw(*this->AnimationSprite);
}

shared_ptr<Texture> Engine::Core::Animator::GetSFMLTexture(void) const
{
	return this->Tex;
}

shared_ptr<Sprite> Engine::Core::Animator::GetSFMLSprite(void) const
{
	return this->AnimationSprite;
}

Vector2f Engine::Core::Animator::GetPosition(void) const
{
	return this->AnimationSprite->getPosition();
}

Vector2f Engine::Core::Animator::GetSize(void) const
{
	return Vector2f(this->AnimationFrameSize);
}

void Engine::Core::Animator::SetPosition(const Vector2f & Position)
{
	this->AnimationSprite->setPosition(Position);
}

void Engine::Core::Animator::SetOrigin(const Vector2f & Origin)
{
	this->AnimationSprite->setOrigin(Origin);
}

void Engine::Core::Animator::SetRotation(const float & Angle)
{
	this->AnimationSprite->setRotation(Angle);
}

void Engine::Core::Animator::Move(const Vector2f & Offset)
{
	this->AnimationSprite->move(Offset);
}

