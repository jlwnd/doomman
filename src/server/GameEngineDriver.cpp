#include <server/GameEngineDriver.h>

#include "common/Types.h"

namespace DoomMan {
GameEngineDriver::GameEngineDriver(GameState& state, QObject* parent)
    : QObject(parent), m_engine(state) {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &GameEngineDriver::tick);
};

void GameEngineDriver::start() {
    m_timer->start(TICK_RATE_MS);
};

void GameEngineDriver::processInput(uint32_t playerId, PlayerInput input) {
    m_engine.processInput(playerId, input);
};

void GameEngineDriver::tick() {
    m_engine.step(TICK_RATE_MS);
    emit gameStateUpdated();
}

}  // namespace DoomMan