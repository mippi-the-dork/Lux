# Color Temperature — Technical

**Lux v2.0.10 · Source-reviewed implementation reference**

## Enabled state and slider gating

`SLuxViewportControl::PopulateAdvancedMenu` adds `Use Temperature` and `Temperature` to the Advanced Temperature section. The Temperature numeric row uses an `IsEnabled` lambda returning the subsystem's `GetUseTemperature()`. Disabling the checkbox does not clear the stored Kelvin value.

## Native state

`ULuxEditorSubsystem::SetUseTemperature` forwards to `UPointLightComponent::SetUseTemperature`. `SetTemperature` clamps to 1,000–20,000 K and invokes `SetTemperature` on the component when active. User preferences preserve both values independently. The native light combines the temperature tint with its RGB Light Color.

<figure class="doc-media" data-kind="image" data-media-id="temperature-color-flow">
<img src="../../../assets/media-placeholder.png" alt="Lux Light Color and Use Temperature interaction diagram." loading="lazy">
<figcaption>Color temperature is an optional tint applied together with the native Light Color setting.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Diagram a checkbox-controlled Kelvin field (1000–20000 K) and a separate Light Color swatch feeding the same point-light color result. Show Temperature disabled when Use Temperature is unchecked.</span></figcaption>
</figure>

## Defaults and constraints

Initial defaults are **Use Temperature Off** and **Temperature 6,500 K**. `ULuxProjectSettings` provides their reset values; a changed project default does not replace every user's saved settings until they Reset to Project Defaults. The renderer's tonemapping and exposure influence visible Kelvin differences.

Source: [SLuxViewportControl.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/SLuxViewportControl.cpp) and [LuxProjectSettings.h](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Public/LuxProjectSettings.h).

---

For practical use and expected results, [read Design](DESIGN.md).
