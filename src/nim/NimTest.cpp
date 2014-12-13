#include "NimTest.hpp"
#include <iostream>
#include <nim/assets/model/ModelLoader.hpp>
#include <nim/engine/components/Transform.hpp>
#include <nim/engine/components/Camera.hpp>
#include <nim/engine/core/diag/Log.hpp>

NimTest::NimTest() {

}

int main(int argc, char *argv[]) {
	NimTest game;
	game.loadWindow();
	Scene* scene = new Scene();

	Entity e1;
	Transform t1(0, -1, -2);
	t1.rotation.set(0, 45, 0);
	e1.transform = &t1;
	Path path("res/models/Goose.obj");
	Model model = ModelLoader::loadModel(path);
	e1.mesh = &model.meshes[0];

	Entity e2;
	Transform t2(0, 0, 0);
	Camera camera(90, 1, 0.1, 100);
	e2.transform = &t2;
	e2.camera = &camera;
	scene->mainCamera = e2;

	Entity e3;
	Transform t3(0, 0, 0);
	Light light;
	light.color.set(0.5, 0, 0.5);
	e3.transform = &t3;
	e3.light = &light;

	scene->addEntity(e1);
	scene->addEntity(e2);
	scene->addEntity(e3);

	game.addScene(scene);
	game.setScene(scene);

	game.start();

	return 0;
}
