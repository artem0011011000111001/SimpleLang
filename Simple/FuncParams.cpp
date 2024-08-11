#include "FuncParams.h"

using namespace Simple;

FuncParams::FuncParams(Map<int, FunctionPtr> func_bodies)
	: func_bodies(MOVE(func_bodies)) {}

FuncParams FuncParams::clone() const {
	FuncParams clone;

	for (auto& func_body : func_bodies) {
		clone.func_bodies.emplace(func_body.first, func_body.second->clone());
	}
	return MOVE(clone);
}