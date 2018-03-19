#pragma once

#include <string>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <exception>
#include <memory>
#include <map>
#include <iostream>
#include <fstream>
#include "SFML_Collision.h"
#include "Cache.h"

using namespace std;
using namespace sf;

///NOTE: Animators need to have their animations added in the ctor for the classes which use them, for now.

namespace Engine::Core
{
	///<summary>
	///Describes a single animation on a sprite sheet.
	///There can be many animations per sprite sheet.
	///</summary>
	struct AnimationInformation
	{
		AnimationInformation()
		{
			this->FrameLength = 0;
			this->YAxisPosition = 0;
		}

		///How many frames long the animation is.
		unsigned int AnimationLength;
		///How long each frame of the animation is active for (Seconds).
		float FrameLength;
		///The position of the first frame of the animaiton, on the Y-Axis. The X-axis is to be assumed at 0.
		int YAxisPosition;
		///The name of the animation.
		string AnimationName;
	};

	///<summary>
	///Handles the rendering and animation of sprites, from a sprite sheet.
	///Replaces the GameTexture class.
	///</summary>
	class Animator
	{
	public:
		Animator() = default;
		Animator(string SpriteSheetPath, Vector2i FrameSize);
		Animator(const Animator& Animation);
		~Animator();

		void AddAnimation(AnimationInformation Animaiton, bool IsDefaultAnimation = false);
		void SwitchAnimation(string AnimationName);
		void SwitchToDefault(void);
		void PlayAnimation(float dt);
		void Draw(RenderWindow* Wnd);
		void SetPosition(const Vector2f& Position);
		void SetOrigin(const Vector2f& Origin);
		void SetRotation(const float& Angle);
		void Move(const Vector2f& Offset);
		shared_ptr<Texture> GetSFMLTexture(void) const;
		shared_ptr<Sprite> GetSFMLSprite(void) const;
		const Vector2f& GetPosition(void) const;
		const Vector2f& GetSize(void) const;
		const string& GetCurrentAnimation(void) const;

	private:
		///Animations[(AnimationName)] = AnimationInfo;
		map<string, AnimationInformation> Animations;
		///The size of each animation frame.
		Vector2i AnimationFrameSize;
		///The name of the animation which should be defaulted to when there is no other animaiton to use.
		string DefaultAnimation;
		///The current animaiton which is playing.
		AnimationInformation CurrentAnimation;
		///The current frame to draw.
		IntRect CurrentFrame;
		///How long the animation frame has been shown for.
		float FrameTime;
		///Which frame the animation is currently on.
		unsigned int CurrentFrameNumber;

		shared_ptr<Texture> Tex;
		shared_ptr<Sprite> AnimationSprite;
	};

	///<summary>
	///A cache of animations which can be addressed throughout the program.
	///</summary>
	class AnimationCache
	{
	public:
		static Cache<Animator> Cache;
	};

	extern void InitAnimatorCache(void);
}
