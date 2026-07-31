# Folder Structure

```text
Mythraen/
├── Config/                 # Unreal configuration
├── Content/
│   ├── Core/               # Shared assets, tags, data
│   │   └── Input/          # Input actions and mapping contexts
│   ├── Characters/
│   ├── Environment/
│   ├── UI/
│   ├── Items/
│   ├── Quests/
│   └── Maps/
├── Docs/                   # Design and engineering documentation
├── Plugins/                # Optional project plugins
├── Source/
│   └── Mythraen/           # Primary C++ module
├── Tools/                  # Import/build/content helper tools
└── Mythraen.uproject
```

## Content rules

- Place assets by gameplay domain, not by file type.
- Use a `_Dev` suffix or dedicated developer folder for temporary content; never reference it from shipping maps.
- Use Unreal asset prefixes: `BP_`, `DA_`, `DT_`, `WBP_`, `M_`, `MI_`, `T_`, `SK_`, `ABP_`, `BT_`, `BB_`.
