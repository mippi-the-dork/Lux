# What Lux Does — Technical

**Lux v2.0.10 · Unreal Engine 5.8.x · Win64 · Editor-only**

## Plugin module and responsibility

[Lux.uplugin](https://github.com/mippi-the-dork/Lux/blob/main/Lux.uplugin) declares an Editor module named `Lux`, loaded at `PostEngineInit`, targeted to Unreal Engine 5.8.x/Win64. `FLuxModule` registers the Level Editor viewport toolbar entry and Slate input preprocessor. `ULuxEditorSubsystem` owns the temporary light and editor-user settings.

## The actual light

`ULuxEditorSubsystem::EnsureLight()` obtains `GEditor->GetEditorWorldContext().World()`, requires `EWorldType::Editor`, and creates a `UPointLightComponent` with `GetTransientPackage()`, `RF_Transient` and `EComponentMobility::Movable`. It registers the component in the editor world after placing it at the active perspective viewport's location.

<figure class="doc-media" data-kind="image" data-media-id="overview-light-lifecycle">
<img src="../../../assets/media-placeholder.png" alt="Lux architecture diagram of editor subsystem, viewport and transient light." loading="lazy">
<figcaption>The Lux editor subsystem owns a temporary point light whose position follows the active perspective viewport.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a technical flow from Level Editor toolbar to ULuxEditorSubsystem, transient movable UPointLightComponent, editor world and selected perspective camera. Label the world as Editor-only and show that no placed AActor or game-world module is created.</span></figcaption>
</figure>

## Lifetime and storage

`bEnabled` is a session boolean initialized false, so Lux starts disabled on each editor launch. Current light values live in `ULuxUserSettings` (`EditorPerProjectUserSettings`); project limits and defaults live in `ULuxProjectSettings` (`Config=Editor`). None of these values writes a temporary light into map or external Actor packages.

## Explicit boundaries

Lux does not follow PIE/game or orthographic cameras. The light is in the **shared editor world**, not isolated per viewport. Renderer exposure, fog, material response and shadow method determine visible effects. No engine-source modification is required.

Implementation: [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp), [Lux.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/Lux.cpp).

---

For hands-on controls and workflows, [read Design](DESIGN.md).
