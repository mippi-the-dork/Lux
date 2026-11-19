# Updating, Support and Compatibility — Technical

**Lux v2.0.10 · Source-reviewed diagnostics**

## Descriptor and packaging

`Lux.uplugin` declares an Editor module loaded at PostEngineInit and a Win64 platform allowlist. `CanContainContent=false`; the active toolbar is C++ Slate rather than a dependency on an Editor Utility Widget at runtime.

`Lux.Build.cs` references editor modules; do not package this module as a runtime game dependency. Source installs require a compatible Unreal 5.8 C++ build environment and Win64 Editor target.

## Upgrade considerations

The per-user config includes initialization flags for advanced property migration. `ULuxEditorSubsystem::Initialize` keeps earlier personal settings and initializes only values newly added by the plugin. Do not delete an entire project configuration as an update workaround without understanding the consequences.

<figure class="doc-media" data-kind="image" data-media-id="update-source-ownership">
<img src="../../../assets/media-placeholder.png" alt="Lux release update and configuration ownership diagram." loading="lazy">
<figcaption>Lux updates affect editor plugin files while personal preferences and project settings remain separate.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a concise diagram separating Plugins/Lux module files, shared Project Settings config, personal EditorPerProjectUserSettings and transient runtime-editor component. Indicate that the component is recreated, not migrated as level content.</span></figcaption>
</figure>

## Technical reports

A useful diagnostic includes whether the input came from a Level Editor viewport, the target perspective client's world, exact platform/version, the light setter involved, and whether a render feature such as volumetric fog was configured. Avoid treating a valid boolean or setter return as proof of a visible GPU effect.

Source: [Lux.uplugin](https://github.com/mippi-the-dork/Lux/blob/main/Lux.uplugin), [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For practical support steps, [read Design](DESIGN.md).
