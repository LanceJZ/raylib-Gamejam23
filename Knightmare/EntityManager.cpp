#include "EntityManager.h"

EntityManager::EntityManager()
{
}

EntityManager::~EntityManager()
{
	for (auto model : LineModels)
	{
		delete(model);
	}

	for (auto model : Model3Ds)
	{
		delete(model);
	}

	for (auto entity : Entities)
	{
		delete(entity);
	}

	for (auto timer : Timers)
	{
		delete(timer);
	}

	for (auto common : Commons)
	{
		delete(common);
	}

	Entities.clear();
	LineModels.clear();
	Model3Ds.clear();
	Timers.clear();
	Commons.clear();
}

bool EntityManager::Initialize()
{
	for (auto common : Commons)
	{
		common->Initialize(Utils);
	}

	for (auto model3D : Model3Ds)
	{
		model3D->Initialize(Utils);
	}

	for (auto lineModel : LineModels)
	{
		lineModel->Initialize(Utils);
	}
	return true;
}

bool EntityManager::BeginRun()
{
	for (auto model3D : Model3Ds)
	{
		model3D->BeginRun();
	}

	for (auto lineModel : LineModels)
	{
		lineModel->BeginRun();
	}

	for (auto common : Commons)
	{
		common->BeginRun();
	}

	return true;
}

void EntityManager::SetCamera(Camera* cam)
{
	Cam = cam;

	for (auto model3D : Model3Ds)
	{
		model3D->SetCamera(Cam);
	}
}

void EntityManager::SetUtilities(Utilities* utilities)
{
	Utils = utilities;
}

void EntityManager::Input()
{
	for (size_t i = 0; i < LineModels.size(); i++)
	{
		LineModels[i]->Input();
	}

	for (size_t i = 0; i < Model3Ds.size(); i++)
	{
		Model3Ds[i]->Input();
	}
}

void EntityManager::Update(float deltaTime)
{
	for (auto entity : Entities)
	{
		if (entity->Enabled) entity->Update(deltaTime);
	}

	for (size_t i = 0; i < LineModels.size(); i++)
	{
		if (LineModels[i]->Enabled) LineModels[i]->Update(deltaTime);
	}

	for (size_t i = 0; i < Model3Ds.size(); i++)
	{
		if (Model3Ds[i]->Enabled) Model3Ds[i]->Update(deltaTime);
	}

	for (auto timer : Timers)
	{
		timer->Update(deltaTime);
	}

	for (auto common : Commons)
	{
		common->Update();
	}
}

void EntityManager::Draw3D()
{
	for (auto entity : Entities)
	{
		if (entity->Enabled) entity->Draw();
	}

	for (auto lineModel : LineModels)
	{
		if (lineModel->Enabled)	lineModel->Draw();
	}

	for (auto model3D : Model3Ds)
	{
		if (model3D->Enabled) model3D->Draw();
	}
}

void EntityManager::Draw2D()
{
	for (auto common : Commons)
	{
		common->Draw2D();
	}
}

size_t EntityManager::AddEntity(Entity* entity)
{
	size_t entityNumber = Entities.size();
	Entities.push_back(entity);
	Entities[entityNumber]->Initialize(Utils);

	return entityNumber;
}

size_t EntityManager::AddEntity()
{
	size_t entityNumber = Entities.size();
	Entity* newEntity = DBG_NEW Entity();
	Entities.push_back(newEntity);
	Entities[entityNumber]->Initialize(Utils);

	return entityNumber;
}

size_t EntityManager::AddLineModel(LineModel* model)
{
	size_t number = LineModels.size();

	LineModels.push_back(model);
	LineModels[number]->Initialize(Utils);

	return number;
}

size_t EntityManager::AddLineModel(LineModelPoints model)
{
	size_t number = LineModels.size();

	LineModels.push_back(DBG_NEW LineModel());
	LineModels[number]->SetModel(model);
	LineModels[number]->Initialize(Utils);

	return number;
}

size_t EntityManager::AddLineModel()
{
	size_t number = LineModels.size();

	LineModels.push_back(DBG_NEW LineModel());
	LineModels[number]->Initialize(Utils);

	return number;
}

size_t EntityManager::AddModel3D(Model3D* model3D)
{
	size_t modelNumber = Model3Ds.size();

	Model3Ds.push_back(model3D);
	Model3Ds[modelNumber]->Initialize(Utils);
	Model3Ds[modelNumber]->SetCamera(Cam);

	return modelNumber;
}

size_t EntityManager::AddModel3D(Model3D* model3D, Model model)
{
	return AddModel3D(model3D, model, 1.0f);
}

size_t EntityManager::AddModel3D(Model3D* model3D, Model model, float scale)
{
	size_t modelNumber = AddModel3D(model3D);
	Model3Ds[modelNumber]->SetModel(model, scale);
	Model3Ds[modelNumber]->SetCamera(Cam);

	return modelNumber;
}

size_t EntityManager::AddModel3D(Model model)
{
	size_t modelNumber = Model3Ds.size();
	Model3Ds.push_back(DBG_NEW Model3D());
	Model3Ds[modelNumber]->SetModel(model, 1.0f);
	Model3Ds[modelNumber]->Initialize(Utils);
	Model3Ds[modelNumber]->SetCamera(Cam);

	return modelNumber;
}

size_t EntityManager::AddModel3D(Model model, float scale)
{
	size_t modelNumber = AddModel3D(model);
	Model3Ds[modelNumber]->SetCamera(Cam);
	Model3Ds[modelNumber]->Scale = scale;

	return modelNumber;
}

size_t EntityManager::AddTimer()
{
	size_t timerNumber = Timers.size();
	Timers.push_back(DBG_NEW Timer());

	return timerNumber;
}

size_t EntityManager::AddTimer(float amount)
{
	size_t number = AddTimer();
	Timers[number]->Set(amount);

	return number;
}

size_t EntityManager::AddCommon(Common* common)
{
	size_t commonNumber = Commons.size();
	Commons.push_back(common);
	Commons[commonNumber]->Initialize(Utils);

	return commonNumber;
}

Entity* EntityManager::CreateEntity()
{
	Entity* newEntity = DBG_NEW Entity();
	Entities.push_back(newEntity);
	newEntity->Initialize(Utils);
	newEntity->BeginRun();

	return newEntity;
}

LineModel* EntityManager::CreateLineModel()
{
	LineModel* newLineModel = DBG_NEW LineModel();
	LineModels.push_back(newLineModel);
	newLineModel->Initialize(Utils);
	newLineModel->BeginRun();

	return newLineModel;
}

Model3D* EntityManager::CreateModel3D(Model model)
{
	Model3D* newModel3D = DBG_NEW Model3D();
	Model3Ds.push_back(newModel3D);
	newModel3D->SetModel(model, 1.0f);
	newModel3D->Initialize(Utils);
	newModel3D->SetCamera(Cam);

	return newModel3D;
}