#pragma once
#include "AUIScreen.h"
#include "UINames.h"

class ToolBar : public AUIScreen
{
public:
	ToolBar(std::string name);
	~ToolBar();
	void drawUI() override;

};

