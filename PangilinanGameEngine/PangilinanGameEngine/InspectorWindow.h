#pragma once
#include "AUIScreen.h"
class InspectorWindow : public AUIScreen
{
public:
	InspectorWindow(std::string name);
	~InspectorWindow();
	void drawUI() override;
};

