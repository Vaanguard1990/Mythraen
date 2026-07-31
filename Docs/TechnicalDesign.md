# Technical Design

## Technology

- Unreal Engine 5
- C++ for reusable systems and gameplay framework
- Blueprints for composition, encounters, UI presentation, and content tuning
- Primary Data Assets and Data Tables for content definitions

## Architectural principles

- Keep systems modular; prefer actor components for optional player and NPC capabilities.
- Keep game rules in C++, content values and references in assets.
- Depend on interfaces rather than concrete actor classes where interaction is concerned.
- Use gameplay tags for stable semantic identifiers.
- Keep UI passive: UI observes state exposed by components and controllers.

## Planned runtime modules

| Area | Responsibility |
| --- | --- |
| Core | Game instance, game mode, save orchestration, shared types |
| Character | Movement, camera, attributes, equipment hooks |
| Interaction | Focus detection and interaction interface |
| Inventory | Item definitions, stacks, pickups, persistence |
| Dialogue | Conversation state, dialogue data, presentation events |
| Quests | Objectives, progression, rewards, save serialization |
| Combat | Abilities, damage, targeting, enemy reactions |
| AI | Perception, behavior trees, encounter coordination |
| UI | HUD, prompts, menus and accessible feedback |

## Persistence

Save data uses versioned structures. Persistent identifiers are stable names or gameplay tags, never transient actor pointers. World actors serialize state through a save subsystem.
