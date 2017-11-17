#pragma once

#include <memory>
#include <vector>
#include <functional>
#include <SFML\Graphics.hpp>
#include <SFML\Main.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include "Common.h"
#include "Map.h"
#include "Player.h"

using namespace sf;
using namespace std;
using namespace Engine::GamePlay;

#define NODE_DISTANCE 15.0f
#define INTERVAL_LIMIT 10

namespace Engine::Core
{
	///<summary>
	///An object which represents point in 2D space for the Navigation mesh.
	///</summary>
	struct NavigationNode
	{
		NavigationNode(Vector2f Location, Player P);

		///<summary>
		///Compares itself with another NavigationNode object.
		///</summary>
		///<param name = "Rhs">The NavigationNode on the right hand side.</param>
		///<returns>True if they match, otherwise false.</returns>
		bool operator==(const NavigationNode& Rhs);

		///<summary>
		///Compares itself with a point in 2D space.
		///</summary>
		///<param name = "Rhs">The Vector2f on the right hand side.</param>
		///<returns>True if they match, otherwise false.</returns>
		bool operator==(const Vector2f& Rhs);
				
		///<summary>
		///Calculates the euclidean distance to the player, for the heuristic.
		///</summary>
		///<param name = "P">The Player.</param>
		void CalculateDistance(Player P);

		///<summary>
		///Used to draw the NavigationNode object for debugging purposes.
		///Not to be used in game.
		///</summary>
		///<param name = "Window">A pointer to the RenderWindow in use.</param>
		void DebugDraw(shared_ptr<RenderWindow> Window);

		///<summary>
		///A visual representation of the NavigationNode.
		///Used for debugging, not for in game use. 
		///</summary>
		shared_ptr<RectangleShape> Shape;

		///<summary>
		///The point data of the Node.
		///</summary>
		Vector2f Point;

		///<summary>
		///The estimated distance to the destination.
		///</summary>
		float Estimate;
	};

	///<summary>
	///A mesh of all the NavigationNodes, used for A* pathfinding.
	///</summary>
	class NavigationMesh
	{ 
	public:
		///<summary>
		///Constructs the nodes and places them in 2D space.
		///No NavigationNodes are placed in on top of Props and are 15 pixels apart from each other (on both x and y axis).
		///</summary>
		NavigationMesh(shared_ptr<RenderWindow> Window, Player P, Map M);
		~NavigationMesh();
		
		void Update(Player P, float dt);

		///<summary>
		///Used to draw vector of NavigationNode objects for debugging purposes.
		///Not to be used in game.
		///</summary>
		///<param name = "Window">A pointer to the RenderWindow in use.</param>
		void DebugDraw(shared_ptr<RenderWindow> Window);

	private:
		vector<NavigationNode> NavNodes;
		mutex LoadingMuxtex;
		thread LoadingThread;

		mutex NodeUpdateMutex;
		thread NodeUpdateThread;
		int CurrentNodePosition;
		int IntervalCounter; //Incremented once per frame.
		
		void CreateNavigationMesh(const std::shared_ptr<sf::RenderWindow> &Window, Player P, Map M);
	};
}