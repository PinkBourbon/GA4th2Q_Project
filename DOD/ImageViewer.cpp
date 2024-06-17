#include "ImageViewer.h"
#include "KeyComponent.h"
#include "GameEngine.h"

ImageViewer::ImageViewer()
	:Imagenumber(0)
{
}

ImageViewer::~ImageViewer()
{

}

void ImageViewer::OnCreate()
{
	dod::KeyComponent* keyComponent = GetComponent<dod::KeyComponent>();

	keyComponent->onKeyDown = [](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject) //뭐든 키가 눌린다면 호출
	{
		ImageViewer* imageViewer2 = ((ImageViewer*)(thisObject.engineptr->GetObjectptr(L"ImageViewer2")));
		ImageViewer* imageViewer = ((ImageViewer*)(thisObject.engineptr->GetObjectptr(L"ImageViewer")));

		if (keyinfo.code == dod::eButtonCode::PAD_DPAD_B)
		{
			if ( imageViewer2->objState == dod::eObjectState::OnUpdate)
			{
				imageViewer2->Imagenumber++;
			}

			if (imageViewer->objState == dod::eObjectState::OnUpdate)
			{
				imageViewer->Imagenumber++;
			}
		}
	};
}

void ImageViewer::OnEnable()
{

}

void ImageViewer::OnUpdate()
{
	//이미지가 변동되었을 때를 넣을것.
}

void ImageViewer::OnDisable()
{

}

void ImageViewer::OnRelease()
{

}
