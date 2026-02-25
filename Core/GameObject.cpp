#include <algorithm>
#include <cmath>
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include <glm/glm.hpp>


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime) {
    for (auto &component: m_components) {
        component->Update(deltaTime);
    }
}

void dae::GameObject::FixedUpdate() {
    for (auto &component: m_components) {
        component->FixedUpdate();
    }
}

void dae::GameObject::Render() const {
    for (const auto &component: m_components) {
        component->Render();
    }
}

void dae::GameObject::SetLocalPosition(const glm::vec2 &position) {
    m_transform.SetLocalPosition(glm::vec3(position, 0.f));
    SetTransformDirty();
}

void dae::GameObject::SetLocalRotation(const float radians) {
    m_transform.SetLocalRotation(radians);
    SetTransformDirty();
}

void dae::GameObject::SetLocalScale(const glm::vec2 &scale) {
    m_transform.SetLocalScale(scale);
    SetTransformDirty();
}

const glm::vec3 &dae::GameObject::GetLocalPosition() const {
    return m_transform.GetLocalPosition();
}

glm::vec2 dae::GameObject::GetWorldPosition() const {
    if (m_transform.IsDirty()) {
        if (m_parent) {
            m_transform.UpdateWorldTransform(m_parent->GetWorldTransform());
        }
        else {
            m_transform.UpdateWorldTransform();
        }
    }
    return m_transform.GetWorldPosition();
}

float dae::GameObject::GetWorldRotation() const {
    if (m_transform.IsDirty()) {
        if (m_parent) {
            m_transform.UpdateWorldTransform(m_parent->GetWorldTransform());
        }
        else {
            m_transform.UpdateWorldTransform();
        }
    }
    return m_transform.GetWorldRotation();
}

const glm::mat3 &dae::GameObject::GetWorldTransform() const {
    if (m_transform.IsDirty()) {
        if (m_parent) {
            m_transform.UpdateWorldTransform(m_parent->GetWorldTransform());
        }
        else {
            m_transform.UpdateWorldTransform();
        }
    }
    return m_transform.GetWorldTransform();
}

void dae::GameObject::SetTransformDirty() {
    m_transform.SetDirty();
    for (auto *child: m_children) {
        child->SetTransformDirty();
    }
}

void dae::GameObject::RemoveAndSetNewParent(GameObject *parent) {
    if (m_parent) {
        m_parent->RemoveChild(this);
    }
    if (parent) {
        parent->AddChild(this);
    }
    else {
        m_parent = nullptr;
    }
}

void dae::GameObject::SetParent(GameObject *parent, bool keepWorldPosition) {
    if (parent == this || m_parent == parent)
        return;

    if (IsChild(parent)) { // if new parent is a child detach first
        parent->SetParent(m_parent);
    }

    if (keepWorldPosition) {
        const auto currentWorld = GetWorldTransform(); // save the old transform to apply it later
        RemoveAndSetNewParent(parent);

        if (parent) {
            const auto parentWorld = parent->GetWorldTransform();
            const auto newLocal = glm::inverse(parentWorld) * currentWorld;

            m_transform.SetLocalPosition(glm::vec3(newLocal[2][0], newLocal[2][1], 0.f));
            m_transform.SetLocalRotation(std::atan2(newLocal[0][1], newLocal[0][0]));

            const float sx = glm::length(glm::vec2(newLocal[0][0], newLocal[0][1]));
            const float sy = glm::length(glm::vec2(newLocal[1][0], newLocal[1][1]));
            m_transform.SetLocalScale(glm::vec2(sx, sy));
        }
        else {
            // no parent means local = world
            m_transform.SetLocalPosition(glm::vec3(currentWorld[2][0], currentWorld[2][1], 0.f));
            m_transform.SetLocalRotation(std::atan2(currentWorld[0][1], currentWorld[0][0]));

            const float sx = glm::length(glm::vec2(currentWorld[0][0], currentWorld[0][1]));
            const float sy = glm::length(glm::vec2(currentWorld[1][0], currentWorld[1][1]));
            m_transform.SetLocalScale(glm::vec2(sx, sy));
        }

        SetTransformDirty();
    }
    else {
        RemoveAndSetNewParent(parent);
        SetTransformDirty();
    }
}

dae::GameObject *dae::GameObject::GetParent() const {
    return m_parent;
}

size_t dae::GameObject::GetChildCount() const {
    return m_children.size();
}

dae::GameObject *dae::GameObject::GetChildAt(size_t index) const {
    return m_children[index];
}

void dae::GameObject::AddChild(GameObject *child) {
    if (!child || child == this) {
        return;
    }

    if (child->m_parent == this) {
        return;
    }

    if (child->m_parent) {
        child->m_parent->RemoveChild(child);
    }

    child->m_parent = this; // setting the parent
    m_children.emplace_back(child);
}

void dae::GameObject::RemoveChild(GameObject *child) {
    if (!child)
        return;

    const auto it = std::ranges::find(m_children, child);
    if (it == m_children.end())
        return;

    m_children.erase(it);
    child->m_parent = nullptr;
}

bool dae::GameObject::IsChild(const GameObject *object) const {
    if (object == nullptr)
        return false;

    for (const auto *child: m_children) {
        if (child == object || child->IsChild(object))
            return true;
    }
    return false;
}
