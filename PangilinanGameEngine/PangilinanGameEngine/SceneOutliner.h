#pragma once
#include "AUIScreen.h"
class SceneOutliner : public AUIScreen
{
public:
	SceneOutliner(std::string name);
	~SceneOutliner();
	void drawUI() override;
};

