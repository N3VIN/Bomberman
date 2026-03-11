#pragma once

namespace dae {
    class GameObject;

    class Command {
    public:
        virtual ~Command() = default;
        virtual void Execute() = 0;
    };

    class GameObjectCommand : public Command {
    public:
        explicit GameObjectCommand(GameObject *gameObject)
            : m_GameObject(gameObject) {}

    protected:
        [[nodiscard]] GameObject *GetGameObject() const { return m_GameObject; }

    private:
        GameObject *m_GameObject;
    };
}
