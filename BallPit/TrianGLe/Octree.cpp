#pragma once
#include "Octree.h"

Octree::Octree(vec3 location, vec3 maxDistances, Octree* creator)
{
	position = location;
	bounds = maxDistances;

	balls = vector<Ball*>();
	parent = creator;
}

Octree::~Octree()
{
	for (Ball* ball : balls) delete ball;
	delete[] children;
}

void Octree::Update() {
	for (int i = 0; i < balls.size(); i++) {
		Ball* ball = balls[i];
		ball->Update();
		if (!InRegion(ball, this)) { //Moves ball up hierarchy if it reaches inter-region bounds
			parent->AddBall(ball);
			RemoveBall(ball);
			i--;
		}
		if (children != nullptr) { //Checks to see if inter-regional ball needs to move into child
			for (int a = 0; a < 8; a++) {
				if (InRegion(ball, children[a])) {
					children[a]->AddBall(ball);
					RemoveBall(ball);
					break;
				}
			}
		}
	}
	for (int i = 0; i < balls.size(); i++) {
		Ball* ball1 = balls[i];
		for (int j = i; j < balls.size(); j++) {
			Ball* ball2 = balls[j];
			if (ball1->CollidesWith(ball2)) ball1->ResolveCollision(ball2);
		}
		if (children != nullptr) { //Ball is inter-regional and needs to check other potential collisions
			for (int a = 0; a < 8; a++) {
				vector<Ball*>* ballList = &(children[a]->balls);
				for (int b = 0; b < ballList->size(); b++) {
					if (ball1->CollidesWith((*ballList)[b])) ball1->ResolveCollision((*ballList)[b]);
				}
			}
		}
		if (ball1->OutOfBounds()) ball1->Rebound();
	}
}

void Octree::Render()
{
	for (Ball* ball : balls) ball->Render();
	if (children != nullptr) {
		for (int i = 0; i < 8; i++) children[i]->Render();
	}
}

void Octree::AddBall(Ball* ball)
{
	if (!InRegion(ball, this)) return; //Denies ball if it is out of bounds
	balls.push_back(ball);
	if (balls.size() > maxBalls) Subdivide();
}
void Octree::RemoveBall(Ball* ball)
{
	for (int i = 0; i < balls.size(); i++) {
		if (balls[i] == ball) {
			balls.erase(balls.begin() + i);
			break;
		}
	}
	if (parent != nullptr && parent->CountBalls() < maxBalls) parent->Collapse();
}
int Octree::CountBalls() {
	if (children == nullptr) return balls.size();
	int total = 0;
	for (int i = 0; i < 8; i++) {
		total += children[i]->balls.size();
	}
	return total;
}

void Octree::Subdivide()
{
	if (children != nullptr) return; delete children; //idiotproof 
	children = new Octree*[8];
	children[0] = new Octree(vec3(position.x - bounds.x, position.y - bounds.y, position.z - bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//---
	children[1] = new Octree(vec3(position.x - bounds.x, position.y - bounds.y, position.z + bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//--+
	children[2] = new Octree(vec3(position.x - bounds.x, position.y + bounds.y, position.z - bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//-+-
	children[3] = new Octree(vec3(position.x - bounds.x, position.y + bounds.y, position.z + bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//-++
	children[4] = new Octree(vec3(position.x + bounds.x, position.y - bounds.y, position.z - bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//+--
	children[5] = new Octree(vec3(position.x + bounds.x, position.y - bounds.y, position.z + bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//+-+
	children[6] = new Octree(vec3(position.x + bounds.x, position.y + bounds.y, position.z - bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//++-
	children[7] = new Octree(vec3(position.x + bounds.x, position.y + bounds.y, position.z + bounds.z) / 2.f, vec3(bounds.x, bounds.y, bounds.z) / 2.f, this);//+++
	for (Ball* ball : balls) {
		for (int i = 0; i < 8; i++) {
			children[i]->AddBall(ball);
		}
	}
	balls.clear();
}
void Octree::Collapse()
{
	if (children == nullptr) return; //idiotproof
	for (int i = 0; i < 8; i++) {
		for (Ball* ball : children[i]->balls) balls.push_back(ball);
		delete children[i];
	}
	delete[] children;
}

bool Octree::InRegion(Ball* ball, Octree* region)
{
	if (parent == nullptr) //Full bounds if full region
		return !(ball->position.x < position.x - region->bounds.x || ball->position.x > position.x + region->bounds.x ||
			ball->position.y < position.y - region->bounds.y || ball->position.y > position.y + region->bounds.y ||
			ball->position.z < position.z - region->bounds.z || ball->position.z > position.z + region->bounds.z);
	else //If sub-region, exclude balls that are inter-regional
		return !(ball->position.x - ball->radius < position.x - region->bounds.x || ball->position.x + ball->radius > position.x + region->bounds.x ||
		ball->position.y - ball->radius < position.y - region->bounds.y || ball->position.y + ball->radius > position.y + region->bounds.y ||
		ball->position.z - ball->radius < position.z - region->bounds.z || ball->position.z + ball->radius > position.z + region->bounds.z);
}
