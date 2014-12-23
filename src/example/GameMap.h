#pragma once

#include "GameEntity.h"
#include <server/Zone.h>
#include <set>
#include <iostream>

namespace ai {
namespace example {

class GameMap {
private:
	int _size;
	ai::Zone _zone;
	ai::Server& _server;
	typedef std::set<ai::example::GameEntity*> Entities;
	Entities _entities;

public:
	GameMap(int size, const std::string& name, ai::Server& server) :
			_size(size), _zone(name), _server(server) {
		_server.addZone(&_zone);
	}

	~GameMap() {
		for (Entities::iterator i = _entities.begin(); i != _entities.end(); ++i) {
			delete *i;
		}
		_server.removeZone(&_zone);
	}

	inline const std::string& getName() const {
		return _zone.getName();
	}

	inline GameEntity* addEntity(GameEntity* entity) {
		_entities.insert(entity);
		ai::AI& ai = *entity;
		_zone.addAI(&ai);
		return entity;
	}

	inline bool remove(const ai::CharacterId& id) {
		// TODO: improve
		for (Entities::iterator i = _entities.begin(); i != _entities.end(); ++i) {
			GameEntity* entity = *i;
			if (entity->getId() == id) {
				return remove(entity);
			}
		}
		return false;
	}

	inline bool remove(GameEntity* entity) {
		if (entity == nullptr)
			return false;
		if (_entities.erase(entity) != 1)
			return false;
		ai::AI& ai = *entity;
		_zone.removeAI(&ai);
		return true;
	}

	inline void update(long dt) {
		for (Entities::iterator i = _entities.begin(); i != _entities.end(); ++i) {
			(*i)->update(dt, _size);
		}
	}

	inline bool isBlocked(const ai::Vector3f& pos) const {
		if (pos.x < -_size || pos.x >= _size)
			return true;
		if (pos.z < -_size || pos.z >= _size)
			return true;
		return false;
	}

	void initializeAggro() {
		// TODO: remove me once we have an attack
		Entities::iterator i = _entities.begin();
		if (i == _entities.end())
			return;
		GameEntity *firstEntity = *i++;
		for (; i != _entities.end(); ++i) {
			ai::Entry* e = firstEntity->addAggro(**i, 1000.0f + static_cast<float>(rand() % 1000));
			e->setReduceByValue(1.0f + static_cast<float>(rand() % 3));
		}
	}

	// returns a random start position within the boundaries
	ai::Vector3f getStartPosition() const {
		const int x = (rand() % (2 * _size)) - _size;
		const float y = 0.0f;
		const int z = (rand() % (2 * _size)) - _size;
		return ai::Vector3f(static_cast<float>(x), y, static_cast<float>(z));
	}
};

}
}
