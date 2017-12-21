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
#include <tuple>
#include <cstdlib>
#include <math.h>
#include "Common.h"
#include "Map.h"
#include "Player.h"

using namespace sf;
using namespace std;
using namespace Engine::GamePlay;

//This is going to be increased while working on A*, then I'll experiment with it.
//#define NODE_DISTANCE (size_t)15.0f
#define NODE_DISTANCE (size_t)32
#define INTERVAL_LIMIT 10
#define UPDATE_LIMIT 1000

namespace Engine::Core
{
	///<summary>
	///An object which represents point in 2D space for the Navigation mesh.
	///</summary>
	struct NavigationNode
	{
		NavigationNode(Vector2f Location, Player P, bool IsUseable);
		NavigationNode() = default;

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

		bool operator<(const NavigationNode& RHS) const;

		bool operator!() const;

		explicit operator bool() const;

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

		///<summary>
		///For testing if a node is actually there or not.
		///If true the cell can be used for pathfinding, if it is false pretend it doesn't exsist and iterate over it.
		///</summary>
		bool IsUseable;
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
		
		///<summary>
		///Called once per frame. At given intervals the heuristic gets updated.
		///</summary>
		///<param name = "P">The player to get their location.</param>
		///<param name = "dt">Delta Time.</param>
		void Update(Player P, float dt);

		///<summary>
		///Used to draw vector of NavigationNode objects for debugging purposes.
		///Not to be used in game.
		///</summary>
		///<param name = "Window">A pointer to the RenderWindow in use.</param>
		void DebugDraw(shared_ptr<RenderWindow> Window);

		///<summary>
		///Returns the coords x and y.
		///</summary>
		///<param name = "Position">The position to get</param>
		///<returns>Returns the node at x and y.</returns>
		NavigationNode Get(Vector2i Position);

		///<summary>
		///TODO: Work out the english language.
		///</summary>
		Vector2i GetCellFromPosition(Vector2f Position);

		Vector2f GetPositionFromCell(Vector2i Cell);

		size_t GetHeight(void);

	private:
		vector<vector<NavigationNode>> NavNodes;
		map<string, int> NodeInformation; ///Contains information about rows and columns.

		mutex LoadingMuxtex;
		thread LoadingThread;

		size_t CurrentNodePosition;
		size_t CurrentNodeRow;
		size_t IntervalCounter; //Incremented once per frame.
		
		void CreateNavigationMesh(const std::shared_ptr<sf::RenderWindow> &Window, Player P, Map M);
		void UpdateNavigationNodes(Player P, size_t Batch);
	};
}