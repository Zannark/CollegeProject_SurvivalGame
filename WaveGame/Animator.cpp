#include "Animator.h"

Engine::Core::Cache<Engine::Core::Animator> Engine::Core::AnimationCache::Cache = Engine::Core::Cache<Engine::Core::Animator>();

///<summary>
///Loads all of the animation spritesheets into the cache, with their relative path used as the key.
///</summary>
void Engine::Core::InitAnimatorCache(void)
{	
	AnimationCache::Cache.Add("Assets/Background.png", Animator("Assets/Background.png", Vector2i(800, 600)));
	AnimationCache::Cache.Add("Assets/Player.png", Animator("Assets/Player.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/TestBuilding.png", Animator("Assets/TestBuilding.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/Enemy.png", Animator("Assets/Enemy.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/PlayerWeapon.png", Animator("Assets/PlayerWeapon.png", Vector2i(21, 74)));
	AnimationCache::Cache.Add("Assets/SpeedPowerUp.png", Animator("Assets/SpeedPowerUp.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/DamagePowerUp.png", Animator("Assets/DamagePowerUp.png", Vector2i(32, 32)));
	AnimationCache::Cache.Add("Assets/HealthBarIcon.png", Animator("Assets/HealthBarIcon.png", Vector2i(46, 45)));
}

///<summary>
///Loads a sprite sheet from the hard drive into memory.
///</summary>
///<param name = "SpriteSheerPath">The path that the sprite sheet file is located at, can be either a relative or absolute path.</param>
///<param name = "FrameSize">The size of an animation frame. The size of a frame is the size for all animations.</param>
Engine::Core::Animator::Animator(string SpriteSheetPath, Vector2i FrameSize)
{
	this->DefaultAnimation = "";
	this->AnimationFrameSize = FrameSize;

	this->Tex = make_shared<Texture>();

	if (!Collision::CreateTextureAndBitmask(*this->Tex, SpriteSheetPath))
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

///<summary>
///A copy construtor to copy data from one animation to another.
///</summary>
///<param name = "Animation">The Animator to copy information from.</param>
Engine::Core::Animator::Animator(const Animator & Animation)
{
	this->DefaultAnimation = Animation.DefaultAnimation;
	this->AnimationFrameSize = Animation.AnimationFrameSize;
	this->CurrentAnimation = Animation.CurrentAnimation;
	this->FrameTime = Animation.FrameTime;
	this->CurrentFrameNumber = Animation.CurrentFrameNumber;
	this->Tex = Animation.Tex;

	if (!Animation.AnimationSprite)
		throw runtime_error("Unable to copy a nullptr sprite!");

	this->AnimationSprite = make_shared<Sprite>(*Animation.AnimationSprite);
	this->AnimationSprite->setTexture(*this->Tex);
}

Engine::Core::Animator::~Animator()
{
}

///<summary>
///Adds an animation to the animator. 
///</summary>
///<param name = "Animation">The description of the animation to add to the animator.</param>
///<param name = "IsDefaultAnimation">Flags if the animation is the default animation to play or not, true if it is otherwise false.</param>
void Engine::Core::Animator::AddAnimation(AnimationInformation Animaiton, bool IsDefaultAnimation)
{
	if (IsDefaultAnimation)
		this->DefaultAnimation = Animaiton.AnimationName;

	this->Animations[Animaiton.AnimationName] = Animaiton;
	this->FrameTime = Animaiton.FrameLength;
}

///<summary>
///Switches animations from the current playing animation to a given animation.
///</summary>
///<param name = "AnimationName">The name of the animation to switch to.</param>
void Engine::Core::Animator::SwitchAnimation(string AnimationName)
{
	if (this->Animations.find(AnimationName) == this->Animations.end())
		throw runtime_error(string("Unable to find animation with the name: ") + AnimationName);
	
	this->CurrentFrameNumber = 0;
	this->FrameTime = this->CurrentAnimation.FrameLength + 1;
	this->CurrentAnimation = this->Animations[AnimationName];
}

///<summary>
///Switches animations from the current playing animation to the default animations.
///</summary>
void Engine::Core::Animator::SwitchToDefault(void)
{
	if (this->DefaultAnimation.empty())
		throw runtime_error("There is no default animation assigned.");

	this->SwitchAnimation(this->DefaultAnimation);
}

///<summary>
///Plays the animation, switches frames at the required intervals.
///</summary>
///<param name = "dt">Delta time</param>
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

///<summary>
///Renders the texture to the screen.
///</summary>
///<param name = "RenderWindow">The window to draw to.</param>
void Engine::Core::Animator::Draw(RenderWindow * Wnd)
{
	Wnd->draw(*this->AnimationSprite);
}

///<summary>
///Gets the sf::Texture which is used by the object.
///</summary>
///<returns>The sf::Texture used.</returns>
shared_ptr<Texture> Engine::Core::Animator::GetSFMLTexture(void) const
{
	return this->Tex;
}

///<summary>
///Gets the sf::Sprite used by the object.
///</summary>
///<returns>A shared_ptr to the sf::sprite.</returns>
shared_ptr<Sprite> Engine::Core::Animator::GetSFMLSprite(void) const
{
	return this->AnimationSprite;
}

///<summary>
///Gets the position of the Animator.
///</summary>
///<returns>The position of the GameTexture on the window.</returns>
const Vector2f& Engine::Core::Animator::GetPosition(void) const
{
	return this->AnimationSprite->getPosition();
}


///<summary>
///Gets the size of a single frame from the spritesheet.
///</summary>
///<returns>The size of the Animator.</returns>
const Vector2f& Engine::Core::Animator::GetSize(void) const
{
	return Vector2f(this->AnimationFrameSize);
}

///<summary>
///Gets the current playing animation.
///</summary>
///<returns>The current playing animation</returns>
const string& Engine::Core::Animator::GetCurrentAnimation(void) const
{
	return this->CurrentAnimation.AnimationName;
}

///<summary>
///Sets the position of the Animator, in 2D space.
///</summary>
///<param name = "Position">The position to set the Animator.</param>
void Engine::Core::Animator::SetPosition(const Vector2f & Position)
{
	this->AnimationSprite->setPosition(Position);
}

///<summary>
///Sets the origin for rotating the Animator.
///</summary>
///<param name = "Position">The position, relative to the sprite, to rotate the texture by.</param>
void Engine::Core::Animator::SetOrigin(const Vector2f & Origin)
{
	this->AnimationSprite->setOrigin(Origin);
}

///<summary>
///Sets the rotation of the Animator.
///</summary>
///<param name = "Angle">The angle to set the Animator to.</param>
void Engine::Core::Animator::SetRotation(const float & Angle)
{
	this->AnimationSprite->setRotation(Angle);
}

///<summary>
///Moves the Animator a given amount of pixels across the screen.
///</summary>
///<param name = "Offset">The amount of pixels to move the Animator by from its current position.</param>
void Engine::Core::Animator::Move(const Vector2f & Offset)
{
	this->AnimationSprite->move(Offset);
}

