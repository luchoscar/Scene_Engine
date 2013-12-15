#pragma once

class BaseObject
{

protected:
	float color[3];
	float position[2];
	float rotation;
	float scale;

public:
	BaseObject();
	virtual ~BaseObject();

	virtual void Draw() = 0;
	virtual void Update() = 0;
};
