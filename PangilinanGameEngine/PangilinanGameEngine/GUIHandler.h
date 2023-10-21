#pragma once

#include "Window.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "SwapChain.h"

class AppWindow;
class GUIHandler
{
public:
	GUIHandler();
	~GUIHandler();

	bool init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* device_context);

	bool onUpdateStart(SwapChain* m_swap_chain);
	void onUpdateEnd();

	bool release();
	

public:
	static GUIHandler* get();


private:
	static GUIHandler* sharedInstance;

	friend class AppWindow;

};

