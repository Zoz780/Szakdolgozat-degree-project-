#pragma once
#include "ModelLoader.h"
#include <glut.h>
class VboDrawer : public Model_loader
{
public:
	VboDrawer();

	/**
			*Modell kirajzol�sa VBO m�dszerrel
	*/
	void DrawModel(float x, float y, float z);

};

