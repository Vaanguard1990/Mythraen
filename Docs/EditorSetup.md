# Editor Setup

Binary Unreal assets (`.uasset`, `.umap`) are authored in the editor, not in
source control tooling. This page lists the one-time content setup that the
C++ foundation expects.

## 1. Input assets

Create the following under `Content/Core/Input`:

| Asset | Type | Value type | Notes |
| --- | --- | --- | --- |
| `IA_Move` | Input Action | Axis2D (Vector2D) | X strafes, Y moves forward |
| `IA_Look` | Input Action | Axis2D (Vector2D) | X yaws, Y pitches |
| `IA_Jump` | Input Action | Digital (bool) | — |
| `IMC_Default` | Input Mapping Context | — | Bindings below |

`IMC_Default` bindings:

- **IA_Move** — `W` (Swizzle Input Axis Values: YXZ), `S` (Swizzle YXZ + Negate),
  `D`, `A` (Negate), and gamepad `Left Thumbstick 2D-Axis`.
- **IA_Look** — `Mouse XY 2D-Axis` (Negate Y) and gamepad
  `Right Thumbstick 2D-Axis` (Negate Y).
- **IA_Jump** — `Space Bar` and gamepad `Face Button Bottom`.

## 2. Character and game mode Blueprints

1. Create `BP_MythraenCharacter` in `Content/Characters`, derived from
   `MythraenCharacter`.
2. In its **Input** category, assign `IMC_Default`, `IA_Move`, `IA_Look` and
   `IA_Jump`. Without a mapping context the character spawns but does not move,
   and a warning is logged.
3. Assign a skeletal mesh and animation Blueprint on the mesh component.
4. Create `BP_MythraenGameMode` in `Content/Core`, derived from
   `MythraenGameMode`, and set **Default Pawn Class** to `BP_MythraenCharacter`.

## 3. Test map

1. Create `Map_Brumavia_Test` in `Content/Maps` with a floor, a light and a
   `Player Start`.
2. In **World Settings**, set the GameMode Override to `BP_MythraenGameMode`.
3. Uncomment `EditorStartupMap` and `GameDefaultMap` in
   `Config/DefaultEngine.ini`.

## 4. Verify

Play In Editor: the character should move relative to the camera, orient toward
its movement direction, look with mouse and right stick, and jump.
