#include "NavigationMesh.h"

NavigationMesh::NavigationMesh(Map *Map)
{
	Vector2f LastNodePlacement(0, 0);
	auto Props = Map->GetProps();
	IntRect Tester = IntRect(0, 0, 1, 1);

	for (int x = 0; x < (int)Map->GetBackground().GetDimensions().x; x += 5)
	{
		for (int y = 0; y < (int)Map->GetBackground().GetDimensions().y; y += 5)
		{
			for (int i = 0; i < Props.size(); i++)
			{
				Tester = IntRect(x, y, 1, 1);
				IntRect PropRect = IntRect(Props[i]->GetTexture().GetPosition().x,
										   Props[i]->GetTexture().GetPosition().y,
										   Props[i]->GetTexture().GetDimensions().x, 
									       Props[i]->GetTexture().GetDimensions().y);

				cout << Props[i]->GetTexture().GetPosition().x << " "
					 << Props[i]->GetTexture().GetPosition().y << " "
					 << Props[i]->GetTexture().GetDimensions().x << " "
					 << Props[i]->GetTexture().GetDimensions().y << endl;
	
				RectangleShape S = RectangleShape(Vector2f(Tester.width, Tester.height));
				S.setPosition(Tester.left, Tester.top);
				S.setFillColor(Color::Red);
				S.setOutlineColor(Color::Transparent);
				S.setOutlineThickness(1);

				if (!Tester.intersects(PropRect))
				{
					this->Nodes.push_back(NavigationNode(x, y));
					this->NodeDrawDebug.push_back(S);
				}
			}
		}
	}

	cout << this->NodeDrawDebug.size() << endl;
}

NavigationMesh::~NavigationMesh()
{
}

void NavigationMesh::Draw(RenderWindow * Window)
{
	for (int i = 0; i < this->NodeDrawDebug.size(); i++)
	{
		Window->draw(this->NodeDrawDebug[i]);
	}
}
