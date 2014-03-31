#include <tree/ITask.h>
#include <common/AIException.h>

namespace ai {

ITask::ITask(const std::string& name, const std::string& parameters, const ConditionPtr& condition) :
		TreeNode(name, parameters, condition) {
}

ITask::~ITask() {
}

TreeNodeStatus ITask::execute(AI& entity, long deltaMillis) {
	if (TreeNode::execute(entity, deltaMillis) == CANNOTEXECUTE)
		return state(CANNOTEXECUTE);

	try {
		return state(doAction(entity, deltaMillis));
	} catch (std::exception&) {
		return state(EXCEPTION);
	}
}

void ITask::addChild(const TreeNodePtr& /*child*/) {
	throw AIException("An action node may not have a child");
}

}
