#pragma once
#include "Octree.h"

Octree::Octree(vec3 location, vec3 maxDistances, Octree* creator)
{
	position = location;
	bounds = maxDistances;

	shapes = vector<Shape*>();
	parent = creator;
}

Octree::~Octree()
{
	for (Shape* shape : shapes) delete shape;
	delete[] children;
}

void Octree::Update() {
	for (int i = 0; i < shapes.size(); i++) {

	}
}

void Octree::AddShape(Shape* shape)
{
	if (shape->position.x < position.x - bounds.x || shape->position.x > position.x + bounds.x || //Denies shape if it is out of bounds
		shape->position.y < position.y - bounds.y || shape->position.y > position.y + bounds.y ||
		shape->position.z < position.z - bounds.z || shape->position.z > position.z + bounds.z) return;
	shapes.push_back(shape);
	if (shapes.size() > maxShapes) Subdivide();
}
void Octree::RemoveShape(Shape* shape)
{
	for (int i = 0; i < shapes.size(); i++) {
		if (shapes[i] == shape) {
			shapes.erase(shapes.begin() + i);
			break;
		}
	}
	if (parent != nullptr && parent->CountShapes() < maxShapes) parent->Collapse();
}
int Octree::CountShapes() {
	if (children == nullptr) return shapes.size();
	int total = 0;
	for (int i = 0; i < 8; i++) {
		total += children[i]->shapes.size();
	}
	return total;
}

void Octree::Subdivide()
{
	if (children != nullptr) return; //idiotproof
	children = new Octree*[8];
	children[0] = new Octree(vec3(position.x - bounds.x, position.y - bounds.y, position.z - bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//---
	children[1] = new Octree(vec3(position.x - bounds.x, position.y - bounds.y, position.z + bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//--+
	children[2] = new Octree(vec3(position.x - bounds.x, position.y + bounds.y, position.z - bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//-+-
	children[3] = new Octree(vec3(position.x - bounds.x, position.y + bounds.y, position.z + bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//-++
	children[4] = new Octree(vec3(position.x + bounds.x, position.y - bounds.y, position.z - bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//+--
	children[5] = new Octree(vec3(position.x + bounds.x, position.y - bounds.y, position.z + bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//+-+
	children[6] = new Octree(vec3(position.x + bounds.x, position.y + bounds.y, position.z - bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//++-
	children[7] = new Octree(vec3(position.x + bounds.x, position.y + bounds.y, position.z + bounds.z), vec3(bounds.x, bounds.y, bounds.z), this);//+++
	for (Shape* shape : shapes) {
		for (int i = 0; i < 8; i++) {
			children[i]->AddShape(shape);
		}
	}
	shapes.clear();
}
void Octree::Collapse()
{
	if (children == nullptr) return; //idiotproof
	for (int i = 0; i < 8; i++) {
		for (Shape* shape : children[i]->shapes) shapes.push_back(shape);
		delete children[i];
	}
	delete[] children;
}
