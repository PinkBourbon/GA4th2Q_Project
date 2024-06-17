#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <map>
#include <unordered_map>
#include <d2d1.h>
#include <d2d1_1.h>
#include <wincodec.h>

//#include "d2d1effects_2.h"		// ����Ʈ �غ�
#include "d2d1helper.h"
#include "GIMacro.h"
#include "Id2d.h"
#include "SpriteGI.h"
#include "RenderComponent.h"
#include "Matrix3x3.h"
#include "RenderSprite.h"
#include "SpriteResource.h"

namespace dod
{
	class RenderComponent;
	struct Matrix3x3;
		
	class GIEngine : public Id2d
	{
	public:
		GIEngine();
		virtual ~GIEngine();

		// �ʱ�ȭ
		virtual void Initialize(HWND hWnd, int screenWidth, int screenHeight) override;

		virtual void EnrollComponent(RenderComponent* rc) override;
		virtual void DisenrollComponent(RenderComponent* rc) override;

		virtual void SetCamera(Transform* cameraTransform) override;

		// ����(�߾Ӻκ� ����)
		virtual void AllRender(double deltaTime) override;


		// ����
		virtual void Finalize() override;

	private:
		void BeginRender();
		void EndRender();

		/// AllRender ���빰

		// �귯�� ����
		void SetBrushColor(float r, float g, float b, float a) ;
		

		//��ǥ�� ���� ���
		void DrawRectangle(float x1, float y1, float x2, float y2);
		void DrawFillRectangle(float x1, float y1, float x2, float y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawEllipse(float left, float top, float right, float bottom);
		void DrawEllipse(float r);

		// ���� ���
		bool DrawTextKNT(float x, float y, const wchar_t* str, int len);

		// ��������Ʈ �ε�
		int LoadSpriteSheet(const char* filePath);

		/// <summary>
		/// �̹�����Ʈ�� �ε��ϴ� �Լ� 
		/// </summary>
		/// <param name="filePath">�̹����� ���</param>
		/// <returns>�ش� �̹����� �ڵ鰪(-1 �� ��� ���� �������� ����)</returns>
		int LoadSpriteSheet(const wchar_t* filePath);

		/// <summary>
		/// �̹��� �̸��� ������ �̸��� �ؽ�Ʈ������ �о� �̹����� �ڸ��� ���� ������ SpriteResource�� spriteGI vector�� �����Ѵ�
		/// </summary>
		/// <param name="imageHandle">�̹��� �ڵ�</param>
		/// <param name="imagePath">�̹��� ���(�̹��� ���� Ȯ���� ����)</param>
		/// <returns>�ڸ� ��������Ʈ�� ����(�ּӰ��� 1)</returns>
		int LoadSpriteSetSheet(int imageHandle, const wchar_t* imagePath);

		// ī�޶� Ʈ������ ����
		Matrix3x3 GetCameraTransform(RenderComponent* a, Transform* cameraTransform);

		// ��������Ʈ ���
		void DrawSprite(int handle, int spriteIndex, float posX, float posY);
		//void DrawSprite(SpriteGI* sprite, float posX, float posY);

		// ��������Ʈ ����
		void RemoveAllSprite();
		void RemoveAllSpriteSheet();

	
		HRESULT CreateDeviceResource();
		void DiscardDeviceResource();

		// ��������Ʈ �ҽ� ã��
		wchar_t* ConvertCStoWCS(const char* orig);


	private:
		// ���� 
		HWND _hWnd;
		HRESULT _ready;

		// ���丮
		ID2D1Factory* _pFactory;
		IDWriteFactory* _pWriteFactory;
		IDWriteTextFormat* _pTextFormat;

		// �׸��� ���
		std::unordered_set<RenderComponent*> _componentContainer;

		ID2D1HwndRenderTarget* _pRenderTarget;
		D2D1_SIZE_F _renderTargetSize;

		// ī�޶�
		Transform* _pCameraTR;

		// �귯��
		ID2D1SolidColorBrush* _pWhiteBrush;
		ID2D1SolidColorBrush* _pBlackBrush;
		ID2D1SolidColorBrush* _pRedBrush;
		//ID2D1SolidColorBrush* _pNowBrush;

		// ��������Ʈ
		IWICImagingFactory* _pWICFactory;

		// ���ҽ� ���� 		
		// ���� �̹��� ���ҽ��� ����ִ� ����, �츮�� ����ϴ� �ڵ��� ��� �� ������ �ε��� �̴�.
		std::vector<SpriteResource> _spriteResourcePool;

		// ���� ��θ� Ű�� �˻��ؼ� �̹� ������� ��쿡�� �̹� �ε尡 �� �̹��� �̱� ������ value�� �ڵ��� �����ָ� �Ȱ�
		// ���� ��쿡�� �ε尡 �Ǿ����� �ʱ� ������ �ε��ؼ� �ʿ� �־� ����Ѵ�.
		std::unordered_map<std::wstring/*���ϰ��*/, int/*�̹����ڵ�*/> _checkSheet;


		// ��Ʈ��
		ID2D1Bitmap* _pBitmap;

		// ��Ʈ����
		D2D1::Matrix3x2F ReturnMatrix(const Matrix3x3& m)
		{	
			return D2D1::Matrix3x2F(m.matrix[0][0], m.matrix[0][1], m.matrix[1][0], m.matrix[1][1], m.matrix[2][0], m.matrix[2][1]);
		}

		// 	HRESULT LoadResourceBitmap(
		// 		ID2D1RenderTarget* pRenderTarget,
		// 		IWICImagingFactory* pIWICFactory,
		// 		PCWSTR resourceName,
		// 		PCWSTR resourceType,
		// 		UINT destinationWidth,
		// 		UINT destinationHeight,
		// 		ID2D1Bitmap** ppBitmap
		// 	);
		HRESULT LoadBitmapFromFile(
			ID2D1RenderTarget* pRenderTarget,
			IWICImagingFactory* pIWICFactory,
			PCWSTR uri,
			UINT destinationWidth,
			UINT destinationHeight,
			ID2D1Bitmap** ppBitmap
		);
	};
}