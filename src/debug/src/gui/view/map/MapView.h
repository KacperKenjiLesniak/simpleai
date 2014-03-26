#pragma once

#include <QGraphicsView>
#include <AI.h>
#include <server/AIStubTypes.h>
#include "MapScene.h"

namespace ai {
namespace debug {

class AIDebugger;
class MapScene;
class MapItem;

class MapView: public QGraphicsView {
	Q_OBJECT
private:
	MapScene _scene;
	AIDebugger& _debugger;
public:
	MapView(AIDebugger& debugger);
	virtual ~MapView();

	void updateMapView();

	/**
	 * @brief Creates a @c MapItem and allows you to create your own instances to render extra details
	 */
	virtual MapItem* createMapItem(const AIStateWorld& state);
};

}
}
