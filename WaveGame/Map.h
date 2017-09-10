#pragma once

#include <memory>
#include <vector>
#include "Prop.h"

using namespace std;

class Map
{
public:
	Map();
	Map(Vector2f Dimensions);
	~Map();

	void AddProp(shared_ptr<Prop> Prop);

private:
	vector<shared_ptr<Prop>> MapProps;
	Vector2f MapDimensions;
};

