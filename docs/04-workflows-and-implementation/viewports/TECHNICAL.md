# Viewport Following and Multi-Viewport Behavior — Technical

**Lux v2.0.10 · Source-reviewed implementation reference**

## Slate input tracking

`FLuxInputProcessor` registers at the start of the Slate input preprocessors. On mouse button down it calls `FLuxViewportTracker::NotifyInteraction(Event.GetScreenSpacePosition())`; on key down it calls the same with `SlateApp.GetCursorPos()`. Both handlers return **false** and do not consume Unreal's normal editor input.

`NotifyInteraction` inspects the Level Editor's `SLevelViewport` geometries and records the viewport under the interaction point as a weak pointer.

## Viewport selection policy

`GetActivePerspectiveClient()` first checks the tracked `SLevelViewport`, then Unreal's active viewport against known Level Editor clients, then another available perspective Level Editor viewport. It rejects an active tracked orthographic client rather than relocating the light to an ortho camera.

<figure class="doc-media" data-kind="image" data-media-id="viewport-tracker-policy">
<img src="../../../assets/media-placeholder.png" alt="Lux active perspective viewport selection logic." loading="lazy">
<figcaption>Lux resolves the last interacted perspective Level Editor viewport before using supported fallbacks.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a decision flow showing a valid tracked SLevelViewport, then matching active Level Editor viewport, then first available perspective fallback. Separate rejected orthographic, PIE and asset-editor clients from valid targets.</span></figcaption>
</figure>

## Shared-world component

`ULuxEditorSubsystem::Tick` gets the chosen client and sets the transient light's world location to the camera's position if changed beyond 0.01 units. Camera rotation is intentionally ignored because the point light is omnidirectional. `HandleWorldCleanup` destroys the old component and guards against registering into an unloading world.

Source: [LuxViewportTracker.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxViewportTracker.cpp), [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For workflows and expected behavior, [read Design](DESIGN.md).
