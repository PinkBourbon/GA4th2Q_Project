#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <map>
#include <unordered_map>
#include <d2d1.h>
#include <d2d1_1.h>
#include <wincodec.h>

//#include "d2d1effects_2.h"		// 이펙트 준비
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

		// 초기화
		virtual void Initialize(HWND hWnd, int screenWidth, int screenHeight) override;

		virtual void EnrollComponent(RenderComponent* rc) override;
		virtual void DisenrollComponent(RenderComponent* rc) override;

		virtual void SetCamera(Transform* cameraTransform) override;

		// 렌더(중앙부분 제외)
		virtual void AllRender(double deltaTime) override;


		// 종료
		virtual void Finalize() override;

	private:
		void BeginRender();
		void EndRender();

		/// AllRender 내용물

		// 브러시 설정
		void SetBrushColor(float r, float g, float b, float a) ;
		

		//좌표에 도형 출력
		void DrawRectangle(float x1, float y1, float x2, float y2);
		void DrawFillRectangle(float x1, float y1, float x2, float y2);
		void DrawLine(float x1, float y1, float x2, float y2);
		void DrawEllipse(float left, float top, float right, float bottom);
		void DrawEllipse(float r);

		// 문자 출력
		bool DrawTextKNT(float x, float y, const wchar_t* str, int len);

		// 스프라이트 로드
		int LoadSpriteSheet(const char* filePath);

		/// <summary>
		/// 이미지시트를 로드하는 함수 
		/// </summary>
		/// <param name="filePath">이미지의 경로</param>
		/// <returns>해당 이미지의 핸들값(-1 일 경우 넣지 못했음을 뜻함)</returns>
		int LoadSpriteSheet(const wchar_t* filePath);

		/// <summary>
		/// 이미지 이름과 동일한 이름의 텍스트파일을 읽어 이미지를 자르기 위한 정보를 SpriteResource의 spriteGI vector에 저장한다
		/// </summary>
		/// <param name="imageHandle">이미지 핸들</param>
		/// <param name="imagePath">이미지 경로(이미지 원본 확장자 포함)</param>
		/// <returns>자른 스프라이트의 갯수(최속값은 1)</returns>
		int LoadSpriteSetSheet(int imageHandle, const wchar_t* imagePath);

		// 카메라 트랜스폼 적용
		Matrix3x3 GetCameraTransform(RenderComponent* a, Transform* cameraTransform);

		// 스프라이트 출력
		void DrawSprite(int handle, int spriteIndex, float posX, float posY);
		//void DrawSprite(SpriteGI* sprite, float posX, float posY);

		// 스프라이트 제거
		void RemoveAllSprite();
		void RemoveAllSpriteSheet();

	
		HRESULT CreateDeviceResource();
		void DiscardDeviceResource();

		// 스프라이트 소스 찾기
		wchar_t* ConvertCStoWCS(const char* orig);


	private:
		// 윈도 
		HWND _hWnd;
		HRESULT _ready;

		// 팩토리
		ID2D1Factory* _pFactory;
		IDWriteFactory* _pWriteFactory;
		IDWriteTextFormat* _pTextFormat;

		// 그리기 대상
		std::unordered_set<RenderComponent*> _componentContainer;

		ID2D1HwndRenderTarget* _pRenderTarget;
		D2D1_SIZE_F _renderTargetSize;

		// 카메라
		Transform* _pCameraTR;

		// 브러시
		ID2D1SolidColorBrush* _pWhiteBrush;
		ID2D1SolidColorBrush* _pBlackBrush;
		ID2D1SolidColorBrush* _pRedBrush;
		//ID2D1SolidColorBrush* _pNowBrush;

		// 스프라이트
		IWICImagingFactory* _pWICFactory;

		// 리소스 관리 		
		// 실제 이미지 리소스가 들어있는 벡터, 우리가 사용하는 핸들은 사실 이 벡터의 인덱스 이다.
		std::vector<SpriteResource> _spriteResourcePool;

		// 파일 경로를 키로 검색해서 이미 들어있을 경우에는 이미 로드가 된 이미지 이기 때문에 value인 핸들을 돌려주면 된고
		// 없을 경우에는 로드가 되어있지 않기 때문에 로드해서 맵에 넣어 줘야한다.
		std::unordered_map<std::wstring/*파일경로*/, int/*이미지핸들*/> _checkSheet;


		// 비트맵
		ID2D1Bitmap* _pBitmap;

		// 매트릭스
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