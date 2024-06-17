#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")	// writefactory
#pragma comment(lib, "windowscodecs.lib")
#include <dwrite.h>
#include <fstream>

#include "GIEngine.h"
#include "RenderComponent.h"
#include "RenderCircle.h"
#include "RenderLine.h"
#include "RenderRect.h"
#include "RenderText.h"
#include "RenderSprite.h"
#include "Transform.h"
#include "ImageData.h"
#include "Macro.h"

namespace dod
{
	Id2d* Id2d::_instanceGI = nullptr;

	Id2d* CreateD2dEngine()
	{
		return new GIEngine();
	}

	GIEngine::GIEngine()
		: _hWnd(nullptr)
		, _pFactory(nullptr)
		, _pWICFactory(nullptr)
		, _pWriteFactory(nullptr)
		, _pTextFormat(nullptr)
		, _pRenderTarget(nullptr)
		, _pWhiteBrush(nullptr)
		, _pBlackBrush(nullptr)
		, _pCameraTR(nullptr)
		, _pRedBrush(nullptr)
		, _pBitmap(nullptr)
		, _ready(S_FALSE)
		, _renderTargetSize(D2D1_SIZE_F())

	{
		_instanceGI = this;
	}

	GIEngine::~GIEngine()
	{

	}

	void GIEngine::Initialize(HWND hWnd, int screenWidth, int screenHeight)
	{
		_hWnd = hWnd;

		HRESULT hResult = CoInitialize(NULL);

		HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_pFactory);

		static const WCHAR s_FontName[] = L"바탕";
		static const FLOAT s_FontSize = 12;

		// 초기화
		if (SUCCEEDED(hr))
		{
			hr = CoCreateInstance(
				CLSID_WICImagingFactory,
				NULL,
				CLSCTX_INPROC_SERVER,
				IID_IWICImagingFactory,
				reinterpret_cast<void**>(&_pWICFactory)
			);
		}

		if (SUCCEEDED(hr))
		{
			hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
				__uuidof(_pWriteFactory),
				reinterpret_cast<IUnknown**>(&_pWriteFactory));
		}

		if (SUCCEEDED(hr))
		{
			hr = _pWriteFactory->CreateTextFormat(
				s_FontName,
				NULL,
				DWRITE_FONT_WEIGHT_NORMAL,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				s_FontSize,
				L"",
				&_pTextFormat
			);
		}

		//텍스트 정렬방식
		if (SUCCEEDED(hr))
		{
			_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
			_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		}

		// 스프라이트
		_componentContainer.clear();
		_spriteResourcePool.clear();
		_checkSheet.clear();

		// 리소스선행
		/// redy 자체 수정 예정
		_ready = CreateDeviceResource();
	}

	void GIEngine::EnrollComponent(RenderComponent* rc)
	{
		if (rc == nullptr)
		{
			return;
		}
		_componentContainer.insert(rc);
	}

	void GIEngine::DisenrollComponent(RenderComponent* rc)
	{
		if (rc == nullptr)
		{
			return;
		}
		_componentContainer.erase(rc);
	}

	void GIEngine::SetCamera(Transform* cameraTransform)
	{
		_pCameraTR = cameraTransform;
	}

	Matrix3x3 GIEngine::GetCameraTransform(RenderComponent* a, Transform* cameraTransform)
	{
		if (_pCameraTR == nullptr)
		{
			return a->_ptransform->GetTranformMatrix();
		}
		Matrix3x3 matrix33 = a->_ptransform->GetTranformMatrix() * cameraTransform->GetTranformMatrix().Inverse();
		matrix33.matrix[2][0] += 640.f;
		matrix33.matrix[2][1] += 360.f;

		return matrix33;
	}

	void GIEngine::BeginRender()
	{
		_ready = CreateDeviceResource();

		//문제없을때 렌더하기
		if (SUCCEEDED(_ready) && !(_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			_renderTargetSize = _pRenderTarget->GetSize();

			_pRenderTarget->BeginDraw();
			_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
			_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
		}		
	}

	void GIEngine::AllRender(double deltaTime)
	{
		BeginRender();

		for (int i = 0; i < 10; i++)							// 레이어 for문
		{
			for (const auto& a : _componentContainer)		// 컴포넌트 for문
			{
				if (i == a->GetLayerNumber())				// 레이어 조건문
				{
					D2D1::Matrix3x2F mat = ReturnMatrix(GetCameraTransform(a, _pCameraTR));
					_pRenderTarget->SetTransform(mat);
					switch (a->GetRendertype())					// 컴포넌트 switch문
					{
						case dod::eRenderType::NONE:
							// 크래쉬 나야함 나중에 넣어 주세요.
							break;
						case dod::eRenderType::CIRCLE:
							DrawEllipse(reinterpret_cast<RenderCircle*>(a)->_circleR);
							break;
						case dod::eRenderType::RECT:
							if (reinterpret_cast<RenderRect*>(a)->_fillCheck == 0)
							{
								DrawRectangle(reinterpret_cast<RenderRect*>(a)->_rectTopX, reinterpret_cast<RenderRect*>(a)->_rectTopY,
									reinterpret_cast<RenderRect*>(a)->_rectBottomX, reinterpret_cast<RenderRect*>(a)->_rectBottomY);
								break;
							}
							SetBrushColor(255, 255, 255, 0);
							DrawFillRectangle(reinterpret_cast<RenderRect*>(a)->_rectTopX, reinterpret_cast<RenderRect*>(a)->_rectTopY,
								reinterpret_cast<RenderRect*>(a)->_rectBottomX, reinterpret_cast<RenderRect*>(a)->_rectBottomY);
							break;							
						case dod::eRenderType::LINE:
							DrawLine(reinterpret_cast<RenderLine*>(a)->_linePoxX1, reinterpret_cast<RenderLine*>(a)->_linePoxY1,
								reinterpret_cast<RenderLine*>(a)->_linePoxX2, reinterpret_cast<RenderLine*>(a)->_linePoxY2);
							break;
						case dod::eRenderType::TEXT:
							DrawTextKNT(reinterpret_cast<RenderText*>(a)->_posX, reinterpret_cast<RenderText*>(a)->_posY,
								reinterpret_cast<RenderText*>(a)->_str, reinterpret_cast<RenderText*>(a)->_strLength);
							break;
						case dod::eRenderType::SPRITE:
						{
							RenderSprite* pRenderSprite = reinterpret_cast<RenderSprite*>(a);

							// 컴포넌트에 이미지가 핸들이 셋팅되어있는지 확인
							if (pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].handle == -1)
							{
								// 핸들이 셋팅되어있지 않을때 해당 패스의 이미지가 로드되어 있는지 확인
								auto iter = _checkSheet.find(pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].imagePath);
								if (iter != _checkSheet.end())
								{
									pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].handle = (*iter).second;
									pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].animationMaxCount = (int)_spriteResourcePool[(*iter).second].infoVector.size();
								}
								else
								{
									int handle = LoadSpriteSheet(pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].imagePath.c_str());
									pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].handle = handle;

									pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].animationMaxCount
										= LoadSpriteSetSheet(handle, pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].imagePath.c_str());
								}
							}

							// 애니메이션 관리
							if (pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].animationMaxCount > 1)
							{
								pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].elapsedTime += deltaTime;
								while (pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].elapsedTime > pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].frameTime)
								{
									pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].animationIndex = (pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].animationIndex + 1) % (pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].animationMaxCount);
									pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].elapsedTime -= pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].frameTime;
								}
							}
							DrawSprite(pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].handle, pRenderSprite->_imageDataVector[pRenderSprite->_imageDataIndex].animationIndex,
								pRenderSprite->_posX, pRenderSprite->_posY);
							break;
						}
						default:
							// 크래쉬 나야함 나중에 넣어 주세요.
							break;
					}
				}
			}
		}
		EndRender();
	}

	void GIEngine::EndRender()
	{
		if (SUCCEEDED(_ready) && !(_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
		{
			// 그리고 끝내기
			HRESULT hr = _pRenderTarget->EndDraw();

			// 사용후 삭제
			if (hr == D2DERR_RECREATE_TARGET)
			{
				hr = S_OK;
				DiscardDeviceResource();
			}
		}
	}

	void GIEngine::Finalize()
	{
		SafeRelease(&_pFactory);
		SafeRelease(&_pRenderTarget);
		SafeRelease(&_pWriteFactory);
		SafeRelease(&_pTextFormat);
		SafeRelease(&_pWhiteBrush);
		SafeRelease(&_pBlackBrush);
		SafeRelease(&_pRedBrush);
		//SafeRelease(&_pNowBrush);

		CoUninitialize();
	}

	/// <summary>
	/// 브러쉬 풀을 이용하던가 소규모의 브러시를 정의하고 그것만 사용할것
	/// </summary>
	/// <param name="r"></param>
	/// <param name="g"></param>
	/// <param name="b"></param>
	/// <param name="a"></param>
	void GIEngine::SetBrushColor(float r, float g, float b, float a)
	{
// 		SafeRelease(&_pNowBrush);
// 
// 		_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &_pNowBrush);
	}

	void GIEngine::DrawRectangle(float x1, float y1, float x2, float y2)
	{
		D2D1_RECT_F _rt = {};
		_rt.left = x1 - (x2 - x1) / 2;
		_rt.top = y1 + (y1 - y2) / 2;
		_rt.right = x2 - (x2 - x1) / 2;
		_rt.bottom = y2 + (y1 - y2) / 2;
		_pRenderTarget->DrawRectangle(_rt, _pWhiteBrush, 2.0f);
	}

	void GIEngine::DrawFillRectangle(float x1, float y1, float x2, float y2)
	{
		D2D1_RECT_F _rt = {};
		_rt.left = x1 - (x2 - x1) / 2;
		_rt.top = y1 + (y1 - y2) / 2;
		_rt.right = x2 - (x2 - x1) / 2;
		_rt.bottom = y2 + (y1 - y2) / 2;
		_pRenderTarget->FillRectangle(_rt, _pBlackBrush);
	}

	void GIEngine::DrawLine(float x1, float y1, float x2, float y2)
	{
		D2D1_POINT_2F point1 = {};
		point1.x = x1;
		point1.y = y1;
		D2D1_POINT_2F point2 = {};
		point2.x = x2;
		point2.y = y2;

		_pRenderTarget->DrawLine(point1, point2, _pRedBrush, 2.0f);
	}

	void GIEngine::DrawEllipse(float left, float top, float right, float bottom)
	{

		D2D1_ELLIPSE region = {};
		region.point.x = left;
		region.point.y = top;
		region.radiusX = (right - left);
		region.radiusY = (bottom - top);

		_pRenderTarget->DrawEllipse(region, _pWhiteBrush);
	}

	void GIEngine::DrawEllipse(float r)
	{
		this->DrawEllipse(0, 0, r, r);
	}

	bool GIEngine::DrawTextKNT(float x, float y, const wchar_t* str, int len)
	{
		if (str != NULL)
		{
			_pRenderTarget->DrawText(str, (UINT32)len, _pTextFormat,
				D2D1::RectF(x, y, x + 500, y + 40),
				_pWhiteBrush);
		}

		return true;
	}

	int GIEngine::LoadSpriteSheet(const char* filePath)
	{
		wchar_t* wcstring = this->ConvertCStoWCS(filePath);
		int result = LoadSpriteSheet(wcstring);
		delete[] wcstring;

		return result;
	}

	int GIEngine::LoadSpriteSheet(const wchar_t* filePath)
	{
		HRESULT hr;
		ID2D1Bitmap* pNewBitmap;

		hr = LoadBitmapFromFile(_pRenderTarget, _pWICFactory, filePath, 0, 0, &pNewBitmap);
		Assert(hr == S_OK, "이미지 로드 실패");

		int handle = (int)_spriteResourcePool.size();

		SpriteResource spriteresource(pNewBitmap);
		_spriteResourcePool.push_back(spriteresource);

		if (SUCCEEDED(hr))
		{
			_checkSheet.insert(std::make_pair(filePath, handle));

			return (handle);
		}

		return handle;
	}

	int GIEngine::LoadSpriteSetSheet(int imageHandle, const wchar_t* imagePath)
	{
		std::wstring filePath = imagePath;
		std::wstring::size_type const a(filePath.find_last_of(L'.'));
		filePath = filePath.substr(0, a);

		filePath.push_back(L'.');
		filePath.push_back(L't');
		filePath.push_back(L'x');
		filePath.push_back(L't');

		/// TODO --- 파일을 읽어서(기본 핸들에 대한 이름과 같은 이름의 어떤 파일을 읽고 그곳에서 데이터를 읽어온 후에 SpriteGI를 만들어서 넣어준다.
		std::wifstream readFile;
		readFile.open(filePath.c_str());
		Assert(readFile.is_open(), "이미지 정보 텍스트파일 열기 실패" && filePath.c_str());

		// 삽입용 스프라이트 인덱스
		int i = 0;
		while (readFile.good())
		{
			float oriX = 0;
			float oriY = 0;
			float width = 0;
			float height = 0;

			readFile >> oriX >> oriY >> width >> height;

			SpriteGI spriteGI(oriX, oriY, width, height);
			_spriteResourcePool[imageHandle].infoVector.push_back(spriteGI);
			i++;
		}

		readFile.close();
		return (int)_spriteResourcePool[imageHandle].infoVector.size();
	}

	void GIEngine::DrawSprite(int handle, int spriteIndex, float posX, float posY)
	{
		SpriteGI* sprite = &_spriteResourcePool[handle].infoVector[spriteIndex];

		// 오류 체크
		if (sprite == NULL)
		{
			return;
		}
		ID2D1Bitmap* sheet = _spriteResourcePool[handle].bitmap;
		if (sheet == NULL)
		{
			return;
		}

		_pRenderTarget->DrawBitmap(sheet,
			D2D1::RectF(posX - (sprite->width) / 2, (float)(posY - (sprite->height) / 2),
				(float)(posX + (sprite->width) / 2), (float)(posY + (sprite->height) / 2)),
			1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
			D2D1::RectF((float)sprite->oriX, (float)sprite->oriY,
				(float)sprite->oriX + (float)sprite->width, (float)sprite->oriY + (float)sprite->height)
		);
	}

	// 	void GIEngine::DrawSprite(SpriteGI* sprite, float posX, float posY)
	// 	{
	// 		SpriteGI* Orisprite = dynamic_cast<SpriteGI*>(sprite);
	// 
	// 		if (sprite == NULL)
	// 		{
	// 			return;
	// 		}
	// 
	// 		ID2D1Bitmap* sheet = _spriteSheet[Orisprite->spriteSheetIndex];
	// 		if (sheet != NULL)
	// 		{
	// 			D2D1_SIZE_F size = _pBitmap->GetSize();
	// 
	// 			_pRenderTarget->DrawBitmap(sheet,
	// 				D2D1::RectF(posX - (sprite->width) / 2, (float)(posY - (sprite->height) / 2),
	// 					(float)(posX + (sprite->width) / 2), (float)(posY + (sprite->height) / 2)),
	// 				1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
	// 				D2D1::RectF((float)Orisprite->oriX, (float)Orisprite->oriY,
	// 					(float)(Orisprite->oriX + sprite->width), (float)(Orisprite->oriY + sprite->height))
	// 			);
	// 
	// 		}
	// 	}

	void GIEngine::RemoveAllSprite()
	{
		// 시간상 구현 불가
	}

	void GIEngine::RemoveAllSpriteSheet()
	{
		// 시간상 구현 불가
	}

	// hr
	HRESULT GIEngine::CreateDeviceResource()
	{
		//렌더 타겟 생성
		if (_pRenderTarget != nullptr)
		{
			return S_FALSE;
		}

		RECT rc;
		GetClientRect(_hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

		HRESULT hr = _pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(_hWnd, size), &_pRenderTarget);

		_pRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
		
		// 브러시 생성
		if (SUCCEEDED(hr))
		{
			hr = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(255.f, 255.f, 255.f), &_pWhiteBrush);
			hr = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.f, 0.f, 0.f, 1.0f), &_pBlackBrush);
			hr = _pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(255.0f, 0.0f, 0.0f), &_pRedBrush);
		}

		return hr;
	}

	void GIEngine::DiscardDeviceResource()
	{
		SafeRelease(&_pRenderTarget);
		SafeRelease(&_pWhiteBrush);
		SafeRelease(&_pBlackBrush);
		SafeRelease(&_pRedBrush);
	}

	// 스프라이트 읽기 보조
	wchar_t* GIEngine::ConvertCStoWCS(const char* orig)
	{
		size_t newsize = strlen(orig) + 1;
		wchar_t* wcstring = new wchar_t[newsize];

		size_t convertedChars = 0;
		mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

		return wcstring;
	}

	HRESULT GIEngine::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
	{
		HRESULT hr = S_OK;
		IWICBitmapDecoder* pDecoder = NULL;
		IWICBitmapFrameDecode* pSource = NULL;
		IWICStream* pStream = NULL;
		IWICFormatConverter* pConverter = NULL;
		IWICBitmapScaler* pScaler = NULL;

		hr = pIWICFactory->CreateDecoderFromFilename(
			uri,
			NULL,
			GENERIC_READ,
			WICDecodeMetadataCacheOnLoad,
			&pDecoder
		);
		if (SUCCEEDED(hr))
		{

			hr = pDecoder->GetFrame(0, &pSource);
		}

		if (SUCCEEDED(hr))
		{
			hr = pIWICFactory->CreateFormatConverter(&pConverter);
		}
		if (SUCCEEDED(hr))
		{
			if (destinationWidth != 0 || destinationHeight != 0)
			{
				UINT originalWidth, originalHeight;
				hr = pSource->GetSize(&originalWidth, &originalHeight);
				if (SUCCEEDED(hr))
				{
					if (destinationWidth == 0)
					{
						FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
						destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
					}
					else if (destinationHeight == 0)
					{
						FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
						destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
					}

					hr = pIWICFactory->CreateBitmapScaler(&pScaler);
					if (SUCCEEDED(hr))
					{
						hr = pScaler->Initialize(
							pSource,
							destinationWidth,
							destinationHeight,
							WICBitmapInterpolationModeCubic
						);
					}
					if (SUCCEEDED(hr))
					{
						hr = pConverter->Initialize(
							pScaler,
							GUID_WICPixelFormat32bppPBGRA,
							WICBitmapDitherTypeNone,
							NULL,
							0.f,
							WICBitmapPaletteTypeMedianCut
						);
					}
				}
			}
			else
			{
				hr = pConverter->Initialize(
					pSource,
					GUID_WICPixelFormat32bppPBGRA,
					WICBitmapDitherTypeNone,
					NULL,
					0.f,
					WICBitmapPaletteTypeMedianCut
				);
			}
		}
		if (SUCCEEDED(hr))
		{
			hr = pRenderTarget->CreateBitmapFromWicBitmap(
				pConverter,
				NULL,
				ppBitmap
			);
		}

		SafeRelease(&pDecoder);
		SafeRelease(&pSource);
		SafeRelease(&pStream);
		SafeRelease(&pConverter);
		SafeRelease(&pScaler);

		return hr;
	}
}