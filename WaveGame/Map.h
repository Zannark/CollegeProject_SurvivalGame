#pragma once

#include <vector>
#include <SFML\Graphics.hpp>
#include <memory>
#include "GameTexture.h"

using namespace std;

namespace Engine::Core
{
	class Map
	{
	public:
		Map();
		~Map();

		///<summary>
		///Sets what the background texture is for the map.
		///</summary>
		///<param name = "ID">A string which is the ID of the texture for the background.</param>
		void AddBackground(string ID);

		///<summary>
		///Adds a prop to the Props vector, so they can be drawn.
		///</summary>
		///<param name = "ID">A string which is the ID for the texture.</param>
		///<param name = "Position">A Vector2f which contains the on screen position for the prop.</param>
		void AddProp(string ID, Vector2f Position);

		///<summary>
		///Gets all props which are loaded into the map.
		///</summary>
		///<returns>The props which are loaded in the map.</returns>
		vector<shared_ptr<GameTexture>> GetProps(void);

		///<summary>
		///Checks if there is an prop at the given position.
		///</summary>
		///<param name = "Position">The position to see if there is a prop there.</param>
		///<returns>True if there is a prop, false otherwise.</returns>
		bool IsPropAtPosition(Vector2f Position);

		///<summary>
		///Draws the background. The background is the first thing which should be drawn.
		///This ensures that the props, player and enemies are on top of it.
		///</summary>
		///<param name = "Window">A pointer to the RenderWindow is being drawn to.</param>
		void DrawBackground(shared_ptr<RenderWindow> Window);

		///<summary>
		///Draws the prop to the screen.
		///</summary>
		///<param name = "Window">A pointer to the RenderWindow is being drawn to.</param>
		void DrawProps(shared_ptr<RenderWindow> Window);

	private:
		GameTexture Background;
		vector<shared_ptr<GameTexture>> Props;
	};
}
