#include "Transform.h"
#include <cmath>

void dae::Transform::SetLocalPosition(const glm::vec3 &position) {
    m_localPosition = position;
}

void dae::Transform::SetLocalRotation(const float radians) {
    m_localRotation = radians;
}

void dae::Transform::SetLocalScale(const glm::vec2 &scale) {
    m_localScale = scale;
}

const glm::vec3 &dae::Transform::GetLocalPosition() const {
    return m_localPosition;
}

float dae::Transform::GetLocalRotation() const {
    return m_localRotation;
}

const glm::vec2 &dae::Transform::GetLocalScale() const {
    return m_localScale;
}

void dae::Transform::SetDirty() {
    m_isDirty = true;
}

void dae::Transform::UpdateWorldTransform(const glm::mat3 &parentWorld) {
    m_worldTransform = parentWorld * ComputeLocalTransform();
    m_isDirty = false;
}

void dae::Transform::UpdateWorldTransform() {
    m_worldTransform = ComputeLocalTransform();
    m_isDirty = false;
}

glm::vec2 dae::Transform::GetWorldPosition() const {
    return {m_worldTransform[2][0], m_worldTransform[2][1]};
}

float dae::Transform::GetWorldRotation() const {
    return std::atan2(m_worldTransform[0][1], m_worldTransform[0][0]);
}

glm::mat3 dae::Transform::ComputeLocalTransform() const {
    const float cosR = std::cos(m_localRotation);
    const float sinR = std::sin(m_localRotation);

    // 2D TRS column major matrix
    // [cos*sx, sin*sx, 0]
    // [-sin*sy, cos*sy, 0]
    // [tx, ty, 1]
    glm::mat3 transform{1.f};
    transform[0][0] = cosR * m_localScale.x;
    transform[0][1] = sinR * m_localScale.x;
    transform[1][0] = -sinR * m_localScale.y;
    transform[1][1] = cosR * m_localScale.y;
    transform[2][0] = m_localPosition.x;
    transform[2][1] = m_localPosition.y;
    return transform;
}
