#include "InputManager.h"

#include <iostream>

namespace Satellite
{
	std::unordered_map<KeyCode, bool> InputManager::keys =
	{
		{ KeyCode::A, false },
		{ KeyCode::B, false },
		{ KeyCode::C, false },
		{ KeyCode::D, false },
		{ KeyCode::E, false },
		{ KeyCode::F, false },
		{ KeyCode::G, false },
		{ KeyCode::H, false },
		{ KeyCode::I, false },
		{ KeyCode::J, false },
		{ KeyCode::K, false },
		{ KeyCode::L, false },
		{ KeyCode::M, false },
		{ KeyCode::N, false },
		{ KeyCode::Ñ, false },
		{ KeyCode::O, false },
		{ KeyCode::P, false },
		{ KeyCode::Q, false },
		{ KeyCode::R, false },
		{ KeyCode::S, false },
		{ KeyCode::T, false },
		{ KeyCode::U, false },
		{ KeyCode::V, false },
		{ KeyCode::W, false },
		{ KeyCode::X, false },
		{ KeyCode::Y, false },
		{ KeyCode::Z, false },
		{ KeyCode::ESCAPE, false}
	};

	glm::vec2 InputManager::mouse_position = glm::vec2(0);

	bool InputManager::left_mouse_button_down = false;
	bool InputManager::right_mouse_button_down = false;
	bool InputManager::left_mouse_button_up = false;
	bool InputManager::right_mouse_button_up = false;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setting the keys' states
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InputManager::SetKey(KeyCode key_code, bool value)
	{
		auto key = keys.find(key_code);

		if (key == keys.end()) {
			std::cout << "ERROR - The key couldn't be found!!!" << std::endl;
			return;
		}

		key->second = value;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Getting the keys' states
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool InputManager::GetKey(KeyCode key_code)
	{
		auto key = keys.find(key_code);

		if (key == keys.end()) {
			std::cout << "ERROR - The key couldn't be found!!!" << std::endl;
			return false;
		}

		return key->second;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setting and getting mouse position
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void InputManager::SetMousePosition(glm::vec2 mouse_pos)
	{
		mouse_position = mouse_pos;
	}

	glm::vec2 InputManager::GetMousePosition()
	{
		return mouse_position;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Setting and getting mouse buttons left and right
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 0 for left button, 1 for right button
	void InputManager::SetMouseButtonDown(short int button, bool value)
	{
		switch (button)
		{
		case 0:
			left_mouse_button_down = value;
			break;
		case 1:
			right_mouse_button_down = value;
			break;
		}
	}

	// 0 for left button, 1 for right button
	void InputManager::SetMouseButtonUp(short int button, bool value)
	{
		switch (button)
		{
		case 0:
			left_mouse_button_up = value;
			break;
		case 1:
			right_mouse_button_up = value;
			break;
		}
	}

	// 0 for left button, 1 for right button
	bool InputManager::GetMouseButtonDown(short int button)
	{
		switch (button)
		{
		case 0:
			return left_mouse_button_down;
		case 1:
			return right_mouse_button_down;
		default:
			return false;
		}
	}

	// 0 for left button, 1 for right button
	bool InputManager::GetMouseButtonUp(short int button)
	{
		switch (button)
		{
		case 0:
			return left_mouse_button_up;
		case 1:
			return right_mouse_button_up;
		default:
			return false;
		}
	}
}