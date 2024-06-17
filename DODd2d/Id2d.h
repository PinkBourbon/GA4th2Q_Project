#pragma once
#include <windows.h>
#include <d2d1.h>

#include "RenderComponent.h"
#include "Transform.h"

//#include "DefineGI.h"

namespace dod
{
	class SpriteGI;
		
	/// <summary>
	/// Abstract 는 모든 하위에 줘야할 필수 요소
	/// </summary>

	class Id2d
	{
	protected:
		static Id2d* _instanceGI;

	public:
		virtual ~Id2d() {}

		// 리턴인스턴스
		static Id2d* GetInstance()
		{
			return _instanceGI;
		}

		// 초기화
		virtual void Initialize(HWND hWnd, int screenWidth, int screenHeight) = 0;

		virtual void EnrollComponent(RenderComponent* rc) = 0;
		virtual void DisenrollComponent(RenderComponent* rc) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="cameraTransform"></param>
		virtual void SetCamera(Transform* cameraTransform) = 0;

		// 브러시 설정
		//virtual void SetBrushColor(float r, float g, float b, float a) = 0;

		// Render
		virtual void AllRender(double deltaTime) = 0;
		// Render 끝

		// 엔진 종료
		virtual void Finalize() = 0;
	};

	Id2d* CreateD2dEngine();
}