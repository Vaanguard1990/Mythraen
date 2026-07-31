# Coding Guidelines

## C++

- Follow Unreal Engine naming and reflection conventions.
- Keep public headers small; use forward declarations where possible.
- Mark UObject references with `UPROPERTY` when they must participate in reflection or garbage collection.
- Prefer `TObjectPtr` for reflected UObject members.
- Validate external data and fail safely with useful log messages.
- Avoid hard-coded content paths in gameplay systems; inject assets through properties or data assets.
- Keep functions short and single-purpose. Extract reusable rules into components or subsystems.

## Blueprints

- Use Blueprints to assemble actors and tune content, not to duplicate engine-level system logic.
- Expose intentionally designed C++ extension points with `BlueprintCallable` or `BlueprintImplementableEvent`.
- Use descriptive categories and tooltips for designer-facing properties.
- Do not place long-running loops or global state in level Blueprints.

## Source control

- Commit cohesive, buildable changes.
- Do not commit generated engine or IDE files.
- Use clear imperative commit messages, for example: `Add interaction component`.
