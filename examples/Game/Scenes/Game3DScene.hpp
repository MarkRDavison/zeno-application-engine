#pragma once

#include <zae/Engine/Scene/Scene.hpp>
#include <zae/Engine/Resources/Resources.hpp>

class Game3DScene : public zae::Scene
{
public:
	Game3DScene(zae::Camera* camera);

protected:
	void Start() override;
	void Update(float delta) override;

private:
	std::vector<zae::ResourceNode> mesheResourceNodes;
	uint32_t meshResourceNodeIndex = 0;
};