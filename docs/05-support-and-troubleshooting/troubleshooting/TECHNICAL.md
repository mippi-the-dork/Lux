# Troubleshooting — Technical

**Lux v2.0.10 · Source-reviewed diagnostics**

## Debugging in layers

1. **Module/toolbar:** Inspect `FLuxModule::StartupModule` and `RegisterMenus` for ToolMenus registration in a Level Editor viewport.
2. **Input/viewport:** `FLuxInputProcessor` retains a weak `SLevelViewport` target. Verify the tracked client's `IsPerspective()` and editor-world identity.
3. **Subsystem/light:** `SetHeadlampState` invokes `EnsureLight` only when enabled; `EnsureLight` requires a valid Editor world and perspective camera, then registers a transient movable point light.
4. **Setter/clamp:** Check project limits for the two primary numeric properties and fixed bounds for advanced values. `ApplyLightSettings` forwards to the native `UPointLightComponent`.
5. **Rendering:** A valid component is not proof of a visible result. Exposure, shadow methods, volume, material and GI settings can alter or suppress apparent changes.
6. **Persistence:** `ULuxUserSettings` saves personal properties on a 0.5-second debounce and shutdown; `bEnabled` intentionally has no persisted field.

<figure class="doc-media" data-kind="image" data-media-id="troubleshoot-light-lifecycle">
<img src="../../../assets/media-placeholder.png" alt="Lux toolbar-to-render troubleshooting flow diagram." loading="lazy">
<figcaption>Troubleshooting follows the native toolbar, viewport resolution, transient light and renderer layers.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Make a flowchart beginning at Lux icon click and tracing module registration, perspective viewport validation, EnsureLight, SetWorldLocation, ApplyLightSettings, and renderer. Mark failure points at each decision.</span></figcaption>
</figure>

## Known safety boundaries

The light is one shared editor-world component. Orthographic or PIE viewports aren't legal targets. World cleanup intentionally removes old components. Do not diagnose the presence of another lit editor viewport as unintended spawning of additional headlamps.

Source: [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp), [LuxViewportTracker.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxViewportTracker.cpp).

---

For practical support steps, [read Design](DESIGN.md).
