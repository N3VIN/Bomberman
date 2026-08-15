# BEngine

BEngine is a small 2D engine built on SDL3. The engine code lives in `Core/`, under the `bengine` namespace, and every game target links it as a static library.

I built NES Bomberman on top of it as a test bed. This README covers the engine and the reasoning behind its design.

## Game loop

The loop is implemented in `Core/Engine/Engine.cpp`, inside `RunOneFrame()`. It uses a fixed timestep with a lag accumulator:

- Measure the real delta time and add it to `m_lag`.
- Drain `m_lag` in a loop, running one `FixedUpdate()` per fixed timestep.
- Run one variable `Update(deltaTime)`, followed by `Render()`.

Deterministic gameplay belongs in `FixedUpdate`. Code that depends on the frame rate belongs in `Update`.

Native builds sleep to cap the frame rate. Web builds do not because the browser drives the loop through `requestAnimationFrame`. Both paths use the same `RunOneFrame()` implementation.

## Scene graph and components

A `Scene` owns its `GameObject`s through `unique_ptr`. Parent and child links are raw, non-owning pointers. The scene already owns every object, so the hierarchy does not need reference counting.

Game object behavior lives in components. `AddComponent<T>(...)` constructs a component in place, while `GetComponent<T>()` retrieves one with `dynamic_cast`. Both functions use a `ComponentType` concept based on `std::derived_from<T, Component>`, which produces clearer errors at the call site.

`Transform` is a plain member rather than a component. I followed Unity here because every game object always has a transform. World transforms are cached and recomputed lazily, with a dirty flag that propagates to child objects.

## Patterns

- **Game Loop / Update:** The fixed-timestep loop described above.
- **Command:** `InputManager` binds a scancode or gamepad button, together with its key state, to an `ICommand`. Rebinding controls and splitting keyboard and gamepad input only require different bindings.
- **Service Locator:** Provides the audio service and event bus. Audio uses a `NullAudioService` fallback, so calls become no-ops when no audio service is registered. The web build uses the same fallback.
- **Singleton:** Reserved for long-lived managers that need one global instance: `Renderer`, `SceneManager`, `ResourceManager`, `InputManager`, and `Time`. The course challenges the use of singletons, so I kept the list narrow.
- **Observer:** `Subject` and `IObserver` implement synchronous observation. Observers register themselves with their subject.

## Multicast delegate

The engine includes the classic `Subject` and `IObserver` pair, but the OOP-style observer pattern never felt natural to me after working with C# events and Unreal's `TMulticastDelegate`.

Taking some inspiration from the side notes in *Game Programming Patterns*, I implemented a typed `MulticastDelegate<Args...>` in `Core/Patterns/MulticastDelegate.h`. Subscribers register a callback without inheriting from an observer interface.

It also handles subscription lifetime and re-entrancy:

- `Subscribe` returns a `ScopedDelegate`. Destroying the handle automatically removes the subscription, so a listener cannot outlive it.
- Unsubscribing during `Broadcast` marks the listener as dead. The delegate waits until the broadcast finishes before erasing it, which avoids invalidating the listener vector during iteration.

## Event bus

The delegate worked well for local relationships, but it did not scale across unrelated systems. Subscribers needed a pointer to the object that owned the delegate, so systems ended up holding references solely to connect events.

`EventBus`, defined in `Core/Patterns/EventBus.h`, solves that with a type-erased map from `std::type_index` to a `MulticastDelegate<const Event&>` slot. Publishers call `Broadcast(SomeEvent{...})`, and listeners use `Subscribe<SomeEvent>(...)`. They share the event type without holding references to each other.

The delegate still handles callback storage, RAII subscriptions, and re-entrancy. The bus only routes events by type. Local one-to-one relationships continue to use delegates directly.

The event bus comes from `ServiceLocator` instead of having its own singleton. This keeps one known access point without adding another global manager.

## Build

BEngine uses C++23 and MSVC with `/W4 /WX`, so warnings are treated as errors. Templates are constrained with concepts.

A CMake post-build step copies `Data/` and the SDL DLLs next to the executable.

### Windows

```sh
cmake --preset x64-debug
cmake --build out/build/x64-debug
```

### Emscripten

Install the toolchain through [Chocolatey](https://chocolatey.org/) on Windows:

```sh
choco install -y cmake emscripten ninja python
```

Then build and serve the project:

```sh
mkdir build_web
cd build_web
emcmake cmake ..
emmake ninja
python -m http.server
```

Open [http://localhost:8000](http://localhost:8000) in a browser.
