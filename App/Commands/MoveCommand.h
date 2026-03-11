#pragma once
#include "Command.h"
#include "GameObject.h"
#include "GameTime.h"
#include <glm/glm.hpp>

namespace dae {
    class MoveCommand final : public GameObjectCommand {
    public:
        MoveCommand(GameObject *gameObject, glm::vec2 direction, float speed)
            : GameObjectCommand(gameObject)
          , m_direction(direction)
          , m_speed(speed) {}

        void Execute() override {
            auto pos = glm::vec2(GetGameObject()->GetLocalPosition());
            pos += m_direction * m_speed * Time::deltaTime;
            GetGameObject()->SetLocalPosition(pos);
        }

    private:
        glm::vec2 m_direction;
        float m_speed;
    };
}
