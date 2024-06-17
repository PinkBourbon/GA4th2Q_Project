#pragma once
#include <functional>
#include "IComponent.h"

namespace dod {
	enum class eButtonCode
	{
		PAD_L_JOYSTICKCLICK,
		PAD_R_JOYSTICKCLICK,
		PAD_L_JOYSTICKMOVE,
		PAD_R_JOYSTICKMOVE,
		PAD_L_TRIGGER,
		PAD_R_TRIGGER,
		PAD_L_SHOULDER,
		PAD_R_SHOULDER,
		PAD_DPAD_UP,
		PAD_DPAD_DOWN,
		PAD_DPAD_LEFT,
		PAD_DPAD_RIGHT,
		PAD_DPAD_A,
		PAD_DPAD_B,
		PAD_DPAD_X,
		PAD_DPAD_Y,
		PAD_DPAD_START,
		PAD_DPAD_BACK,
		KEY_UP,
		KEY_DOWN,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_SPACE,
		KEY_LCRTL,
		KEY_RCTRL,
		KEY_LALT,
		KEY_RALT,
		KEY_LSHIFT,
		KEY_RSHIFT,
		KEY_TAB,
		KEY_ENTER,
		KEY_ESC,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_NUM0,
		KEY_NUM1,
		KEY_NUM2,
		KEY_NUM3,
		KEY_NUM4,
		KEY_NUM5,
		KEY_NUM6,
		KEY_NUM7,
		KEY_NUM8,
		KEY_NUM9,
		MOUSE_LBUTTON,
		MOUSE_RBUTTON
	};

	struct KeyInfo
	{
	public:
		KeyInfo(eButtonCode c, int posX = 0, int posY = 0) : code(c), x(posX), y(posY) {}

		eButtonCode code;
		int x;
		int y;
	};

	struct KeyComponent : public IComponent//10개정도 일단 생각
	{
	public:
		KeyComponent()
			: onKeyDown([](const KeyInfo&, const GameObject&) {})
			, onKeyStay([](const KeyInfo&, const GameObject&) {})
			, onKeyUp([](const KeyInfo&, const GameObject&) {})
			,IComponent(eComponentType::Controller)
		{}

		virtual	~KeyComponent() {};

		//[]()->int {return 1; };
		//[] : 캡쳐;
		//() : 파라미터(매개변수) 리스트;
		//-> 다음은 리턴 타입.
		//{} : 함수 본체(구현)

	public:
		std::function<void(const KeyInfo&, const GameObject&)> onKeyDown;
		std::function<void(const KeyInfo&, const GameObject&)> onKeyUp;
		std::function<void(const KeyInfo&, const GameObject&)> onKeyStay;
	};
}

