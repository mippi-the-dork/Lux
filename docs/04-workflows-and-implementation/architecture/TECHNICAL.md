# Editor Architecture and Lifecycle — Technical

**Lux v2.0.10 · Source-reviewed implementation reference**

## Native integration architecture

`FLuxModule` registers Slate styling and a Level Editor ToolMenus entry. `SLuxViewportControl` owns the native on/off and settings widgets. `FLuxInputProcessor` and `FLuxViewportTracker` track interaction with `SLevelViewport` widgets. `ULuxEditorSubsystem` (`UEditorSubsystem`, `FTickableEditorObject`) manages the light, user preferences and world lifecycle.

<figure class="doc-media" data-kind="image" data-media-id="architecture-source-map">
<img src="../../../assets/media-placeholder.png" alt="Lux source components and configuration ownership diagram." loading="lazy">
<figcaption>Lux separates native UI, input tracking, transient light management and stored preferences into distinct editor classes.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a class/data flow diagram including FLuxModule, SLuxViewportControl, FLuxInputProcessor, FLuxViewportTracker, ULuxEditorSubsystem, ULuxProjectSettings, ULuxUserSettings and UPointLightComponent. Indicate ownership and callback direction.</span></figcaption>
</figure>

## State machine and invalidation

When `SetHeadlampState` enables Lux, `EnsureLight` creates an `RF_Transient` movable `UPointLightComponent` in `EWorldType::Editor`, after resolving the perspective viewport. `Tick` runs while enabled or while preferences remain dirty; it follows camera location and saves pending preferences after 0.5 seconds. `SetHeadlampState(false)` calls `DestroyLight`.

During editor world cleanup, `HandleWorldCleanup` sets the unloading-world guard and destroys the component. `Deinitialize` disables the headlamp, unbinds cleanup and saves pending personal properties. The module's shutdown unregisters tool menus, input processor, viewport tracker and style.

## A useful source map

| Source file | Responsibility |
| --- | --- |
| [Lux.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/Lux.cpp) | Module startup, toolbar registration and cleanup |
| [SLuxViewportControl.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/SLuxViewportControl.cpp) | Native widget layout, tooltips, numbers, color, checkboxes, Advanced menu |
| [LuxViewportTracker.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxViewportTracker.cpp) | Which Level Editor camera owns the light position |
| [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp) | Temporary light, settings, world cleanup and tick |
| [LuxProjectSettings.h](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Public/LuxProjectSettings.h) | Shared bounds and reset defaults |
| [LuxUserSettings.h](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Public/LuxUserSettings.h) | Personal property persistence |

## Architectural boundaries

The module is Editor-only, requires no engine modifications, does not package a runtime system and does not create independent lights per editor viewport. Alternate or unsupported render paths may not visibly respond to every native property.

---

For workflows and expected behavior, [read Design](DESIGN.md).
