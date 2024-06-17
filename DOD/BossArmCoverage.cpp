#include "BossArmCoverage.h"

BossArmCoverage::BossArmCoverage()
{

}

BossArmCoverage::~BossArmCoverage()
{

}

void BossArmCoverage::OnCreate()
{

}

void BossArmCoverage::OnEnable()
{

}

void BossArmCoverage::OnUpdate()
{

}

void BossArmCoverage::OnDisable()
{

}

void BossArmCoverage::OnRelease()
{

}

void BossArmCoverage::BossArmCoverageInitalation()
{
	bossArmCoverageTransform = GetComponent<dod::Transform>();
	_pArmCoverageRenderComponenet = GetComponent<dod::RenderComponent>();
}
