#pragma once
#include "AUIScreen.h"
class EngineProfiler :public AUIScreen
{
public:
	EngineProfiler(std::string name);
	~EngineProfiler();
	void drawUI() override;
};

