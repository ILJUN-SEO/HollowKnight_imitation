#include "IJ_Input.h"


namespace IJ
{
	std::vector<Input::Key> Input::myKeys = {};

	int ASCII[(int)myKeyCode::END] =
	{
		'1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M', 
		VK_LCONTROL, VK_MENU, VK_SPACE, VK_UP,VK_LEFT, VK_DOWN, VK_RIGHT,
		VK_LBUTTON, VK_RBUTTON, VK_MBUTTON,
	};

	void Input::Initialize()
	{
		for (int i = 0; i < (int)myKeyCode::END; i++)
		{
			Key key = {};
			key.code = (myKeyCode)i;
			key.state = myKeyState::None;
			key.isPressedBefore = false;

			myKeys.push_back(key);
		}
	}

	void Input::Update()
	{
		for (int i = 0; i < (int)myKeyCode::END; i++)
		{
			if (GetAsyncKeyState(ASCII[i]) & 0x8000)
			{
				if (myKeys[i].isPressedBefore == true)
					myKeys[i].state = myKeyState::Pressing;
				else
					myKeys[i].state = myKeyState::Down;

				myKeys[i].isPressedBefore = true;
			}
			else
			{
				if (myKeys[i].isPressedBefore == true)
					myKeys[i].state = myKeyState::Up;
				else
					myKeys[i].state = myKeyState::None;

				myKeys[i].isPressedBefore = false;
			}
		}
	}
}