#pragma once
#include <memory>
#include <vector>
#include "Entity.h"
#include "LineModel.h"
#include "Model3D.h"
#include "Timer.h"
#include "Common.h"

#ifdef _DEBUG
	#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
	// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
	// allocations to be of _CLIENT_BLOCK type
#else
	#define DBG_NEW new
#endif

class EntityManager : Common
{
public:
	EntityManager();
	virtual ~EntityManager();

	bool Initialize(Utilities* utilities);
	bool BeginRun();
	void SetCamera(Camera* cam);

	void Input();
	void Update(float deltaTime);
	void Draw3D();
	void Draw2D();

	size_t AddEntity(Entity* entity);
	size_t AddEntity();
	size_t AddLineModel(LineModel* model);
	size_t AddLineModel(LineModelPoints model);
	size_t AddLineModel();
	size_t AddModel3D(Model3D* model3D);
	size_t AddModel3D(Model3D* model3D, Model model);
	size_t AddModel3D(Model3D* model3D, Model model, float scale);
	size_t AddModel3D(Model3D* model3D, Camera* camera);
	size_t AddModel3D(Model3D* model3D, Model model, Camera* camera);
	size_t AddModel3D(Model3D* model3D, Model model, float scale, Camera* camera);
	size_t AddModel3D(Model model);
	size_t AddModel3D(Model model, float scale);
	size_t AddModel3D(Model model, float scale, Camera* camera);
	size_t AddTimer();
	size_t AddTimer(float amount);
	size_t AddCommon(Common* common);

	Entity* CreateEntity();
	LineModel* CreateLineModel();
	Model3D* CreateModel3D(Model model, Camera* camera);

	std::vector<Entity*> Entities = {};
	std::vector<LineModel*> LineModels = {};
	std::vector<Model3D*> Model3Ds = {};
	std::vector<Timer*> Timers = {};
	std::vector<Common*> Commons = {};

private:
	Utilities* Utils = {};
	Camera* Cam = {};
};

