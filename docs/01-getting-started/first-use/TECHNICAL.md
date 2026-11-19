# First Use — Technical

**Lux v2.0.10 · Unreal Engine 5.8.x · Win64 · Editor-only**

## First-click execution

`SLuxViewportControl::Construct` builds a 24-pixel-tall native Slate icon button and a separate `SComboButton`. The icon's `OnClicked` calls `ULuxEditorSubsystem::SetHeadlampState(!IsHeadlampActive())`; its tint uses `EStyleColor::AccentBlue` when active and `EStyleColor::Foreground` otherwise.

## Light creation on activation

`SetHeadlampState(true)` invokes `EnsureLight()`. No light is created until Lux is enabled and a valid perspective Level Editor viewport belongs to the editor world. `EnsureLight()` places the component at the viewport camera position before registration, avoiding a one-frame flash at the world origin.

## Updates and changes

Menu controls call `ULuxEditorSubsystem` setters. When a light component exists, the new value is applied immediately; otherwise the preference is stored for next activation. `Tick` follows the camera position without rotation updates, since a point light is omnidirectional.

<figure class="doc-media" data-kind="image" data-media-id="first-use-state-flow">
<img src="../../../assets/media-placeholder.png" alt="Lux enabled-state flow and persistent setting separation." loading="lazy">
<figcaption>The toolbar on/off state and saved light-property values are independent.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a compact state diagram showing session-only bEnabled toggling the transient light, while individual light settings are stored in ULuxUserSettings and read during the next activation. Include the independent settings arrow.</span></figcaption>
</figure>

Source: [SLuxViewportControl.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/SLuxViewportControl.cpp) · [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For hands-on controls and workflows, [read Design](DESIGN.md).
