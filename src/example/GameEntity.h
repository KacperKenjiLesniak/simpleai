#pragma once

#include <AI.h>
#include <list>

class GameEntity : public ai::ICharacter {
private:
	ai::AI _ai;
	ai::Server& _server;
	std::list<ai::AIPosition> _route;

public:
	GameEntity (const ai::CharacterId& id, const ai::TreeNodePtr& root, ai::IPathfinder& pathfinder, ai::Server& server) :
			ai::ICharacter(id), _ai(*this, root, pathfinder), _server(server) {
		_server.addAI(_ai);
	}

	~GameEntity () {
		_server.removeAI(_ai);
	}

	void update(uint32_t deltaTime) {
		_ai.update(deltaTime);
	}

	inline std::list<ai::AIPosition>& getRoute () {
		return _route;
	}
};
