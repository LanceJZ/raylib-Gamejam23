#pragma once
#include "Entity.h"

class Model3D : public Entity
{
public:
	bool Cull = true;
	float ModelScale = 1;
	Vector2 ViewableArea = { 0 };
	Vector3 ModelPosition = { 0 };
	Color ModelColor = WHITE;
	Color TheColor = WHITE;

	Model3D();
	~Model3D();

	bool Initialize(Utilities* utility);
	void LoadModel(Model &model, Texture2D &texture);
	bool BeginRun(Camera* camera);
	virtual void Input();
	void Update(float deltaTime);
	void Draw();

	void AddChild(Model3D* child);
	void SetModel(Model &model, float scale);
	void SetModelCopy(Model model, float scale);
	Model& GetModel();
	Camera* GetCamera();
	void Spawn(Vector3 pos, Vector3 vel);
	void Unload();

private:
	Model TheModel = {};
	Camera* TheCamera = nullptr;
	std::vector <Model3D*> Children;
	std::vector <Model3D*> Parents;

	virtual void AddChildren(Model3D* child);
};

