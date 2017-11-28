#pragma once
#include "ModelLoader.h"
#include <glut.h>
class VboDrawer : public Model_loader
{
public:
	VboDrawer();

	/**
			*Modell kirajzolása VBO módszerrel
	*/
	void DrawModel(float x, float y, float z);

};

