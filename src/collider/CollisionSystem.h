#pragma once

#include <memory>
#include <list>
#include <vector>
#include "../entities/Entity.h"

std::vector<std::pair<std::shared_ptr<Entity>, std::shared_ptr<Entity>>> GetCollisions(const std::list<std::shared_ptr<Entity>>& entities);