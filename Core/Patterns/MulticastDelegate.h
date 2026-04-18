#pragma once
#include <algorithm>
#include <cstdint>
#include <functional>
#include <ostream>
#include <print>

namespace dae {
    inline constexpr uint64_t INVALID_ID = 0;

    template<typename...>
    class MulticastDelegate; // forward declaring.

    class DelegateHandle final {
    public:
        constexpr DelegateHandle() noexcept = default;
        constexpr bool operator==(const DelegateHandle &other) const = default;

        constexpr bool IsValid() const noexcept {
            return m_id != INVALID_ID;
        }

    private:
        uint64_t m_id{INVALID_ID};

        template<typename...>
        friend class MulticastDelegate;

        constexpr explicit DelegateHandle(uint64_t id) noexcept
            : m_id(id) {}
    };

    template<typename... Args>
    class MulticastDelegate final {
    public:
        MulticastDelegate() = default;
        ~MulticastDelegate() = default;

        MulticastDelegate(const MulticastDelegate &) = delete;
        MulticastDelegate &operator=(const MulticastDelegate &) = delete;
        MulticastDelegate(MulticastDelegate &&) = delete;
        MulticastDelegate &operator=(MulticastDelegate &&) = delete;

        // lambda
        template<typename Func>
        DelegateHandle Subscribe(Func &&callback) {
            const DelegateHandle handle{++m_handleID};
            m_listeners.push_back(ListenerHandle{handle, std::forward<Func>(callback), true});
            return handle;
        }

        // member function
        template<typename Class>
        DelegateHandle AddRaw(Class *instance, void (Class::*memberFunction)(Args...)) {
            return Subscribe([instance, memberFunction](Args... args) {
                    std::invoke(memberFunction, instance, args...);
                }
            );
        }

        // const member function
        template<typename Class>
        DelegateHandle AddRaw(Class *instance, void (Class::*memberFunction)(Args...) const) {
            return Subscribe([instance, memberFunction](Args... args) {
                    std::invoke(memberFunction, instance, args...);
                }
            );
        }

        bool Unsubscribe(DelegateHandle handle) {
            std::println("Unsubscribe called");
            if (!handle.IsValid()) {
                return false;
            }

            for (auto &listener: m_listeners) {
                if (listener.handle == handle && listener.isAlive) {
                    listener.isAlive = false;
                    m_isDirty = true; // mark for delete
                    return true;
                }
            }

            return false;
        }

        void Broadcast(Args... args) {
            std::println("Broadcast called");
            ++m_depth;
            for (const auto &listener: m_listeners) {
                if (!listener.isAlive) {
                    continue;
                }

                auto callbackFn = listener.callbackFn;
                std::invoke(callbackFn, args...); // call the subscribed function
            }

            --m_depth;
            // defer until all the broadcast finishes and only when unsubscribe is called
            if (m_depth == 0 && m_isDirty) {
                std::erase_if(m_listeners, [](ListenerHandle &handle) {
                                  return !handle.isAlive;
                              }
                );

                m_isDirty = false;
            }
        }

        bool IsListenersEmpty() const noexcept {
            return std::ranges::none_of(m_listeners, &ListenerHandle::isAlive);
        }

    private:
        struct ListenerHandle final {
            DelegateHandle handle;
            std::function<void(Args...)> callbackFn;
            bool isAlive;
        };

        uint64_t m_handleID{INVALID_ID};
        std::vector<ListenerHandle> m_listeners{};
        int m_depth{0}; // num of broadcast calls for this delegate
        bool m_isDirty{false};
    };
}
