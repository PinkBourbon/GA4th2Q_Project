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
	/// Abstract �� ��� ������ ����� �ʼ� ���
	/// </summary>

	class Id2d
	{
	protected:
		static Id2d* _instanceGI;

	public:
		virtual ~Id2d() {}

		// �����ν��Ͻ�
		static Id2d* GetInstance()
		{
			return _instanceGI;
		}

		// �ʱ�ȭ
		virtual void Initialize(HWND hWnd, int screenWidth, int screenHeight) = 0;

		virtual void EnrollComponent(RenderComponent* rc) = 0;
		virtual void DisenrollComponent(RenderComponent* rc) = 0;

		/// <summary>
		/// 
		/// </summary>
		/// <param name="cameraTransform"></param>
		virtual void SetCamera(Transform* cameraTransform) = 0;

		// �귯�� ����
		//virtual void SetBrushColor(float r, float g, float b, float a) = 0;

		// Render
		virtual void AllRender(double deltaTime) = 0;
		// Render ��

		// ���� ����
		virtual void Finalize() = 0;
	};

	Id2d* CreateD2dEngine();
}