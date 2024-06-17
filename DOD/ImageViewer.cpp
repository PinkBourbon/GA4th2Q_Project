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

	keyComponent->onKeyDown = [](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject) //���� Ű�� �����ٸ� ȣ��
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
	//�̹����� �����Ǿ��� ���� ������.
}

void ImageViewer::OnDisable()
{

}

void ImageViewer::OnRelease()
{

}
