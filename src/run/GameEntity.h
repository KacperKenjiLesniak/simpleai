#pragma once

#include <SimpleAI.h>
#include <list>

namespace ai {
namespace example {

class GameMap;

class GameEntity : public ai::ICharacter {
private:
	const ai::example::GameMap* _map;
	GroupId _groupId;
	ATOMICINT _hitpoints;
	int _damage;
	int _attackDelay;

	ai::Vector3f getStartPosition() const;

public:
	GameEntity(const ai::CharacterId& id,
			const ai::example::GameMap* map,
			const ai::TreeNodePtr& root,
			ai::GroupMgr& groupManager);

	~GameEntity () {
		_ai.getGroupMgr().remove(_groupId, this);
	}

	operator ai::AI& () {
		return _ai;
	}

	ai::Entry* addAggro (GameEntity& entity, float aggro) {
		return _ai.getAggroMgr().addAggro(entity, aggro);
	}

	inline int getHitpoints () const {
		return _hitpoints;
	}

	inline int getDamage () const {
		return _damage;
	}

	inline int getAttackDelay () const {
		return _attackDelay;
	}

	/**
	 * @return @c false if the dealt damage did not lead to death, @c true otherwise.
	 */
	inline bool applyDamage (int damage) {
		return (_hitpoints -= damage) <= 0;
	}

	void update (long deltaTime, bool debuggingActive) override;
};

}
}
