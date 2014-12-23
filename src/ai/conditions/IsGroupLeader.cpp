#include "IsGroupLeader.h"
#include "AI.h"

namespace ai {

bool IsGroupLeader::evaluate(const AI& entity) {
	return entity.getGroupMgr().isGroupLeader(_groupId, entity.getCharacter());
}

CONDITION_FACTORY_IMPL(IsGroupLeader)

}
