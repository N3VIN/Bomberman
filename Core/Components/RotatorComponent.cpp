#include "RotatorComponent.h"
#include <cmath>
#include <numbers>
#include <glm/vec2.hpp>
#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(GameObject *parent)
    : Component(parent) {}

void dae::RotatorComponent::SetSpeed(float period, bool isClockwise) {
    auto direction = isClockwise ? -1.f : 1.f;

    m_speed = direction * 2 * static_cast<float>(std::numbers::pi) / period;
}

void dae::RotatorComponent::SetRadius(float radius) {
    m_radius = radius;
}

void dae::RotatorComponent::Update(float deltaTime) {
    m_angle += m_speed * deltaTime;

    const float x = m_radius * std::cos(m_angle);
    const float y = m_radius * std::sin(m_angle);

    GetParent()->SetLocalPosition(glm::vec2(x, y));
}
