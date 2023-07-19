#pragma once
#include "CommonInclude.h"


namespace IJ
{
	enum class myKeyCode
	{
		One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero,
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M, 
		Ctrl, Alt, Space, Up, Left, Down, Right,
		Mouse_L, Mouse_R, Mouse_M,
		END,
	};

	enum class myKeyState
	{
		Down,
		Up,
		Pressing,
		None,
	};

	class Input
	{
	public:
		struct Key
		{
			myKeyCode code;
			myKeyState state;
			bool isPressedBefore;
		};

		static void Initialize();
		static void Update();

		__forceinline static bool GetKeyDown(myKeyCode code)
		{ 
			return myKeys[(int)code].state == myKeyState::Down;
		}

		__forceinline static bool GetKeyUp(myKeyCode code)
		{
			return myKeys[(int)code].state == myKeyState::Up;
		}

		__forceinline static bool GetKeyPressing(myKeyCode code)
		{
			return myKeys[(int)code].state == myKeyState::Pressing;
		}

	private:
		static std::vector<Key> myKeys;
	};
}
