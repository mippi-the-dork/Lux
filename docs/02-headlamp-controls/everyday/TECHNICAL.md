# Everyday Light Controls — Technical

**Lux v2.0.10 · Source-reviewed implementation reference**

## Native menu controls

`SLuxViewportControl::MakeSettingsMenu` places four controls in its Headlamp section. `MakeNumberRow` uses `SNumericEntryBox<float>` with `AllowSpin(true)`, live `OnValueChanged` and `OnValueCommitted`; the Attenuation Radius row displays **cm**. `MakeColorRow` uses `SColorBlock` and a nonmodal `OpenColorPicker`, with alpha disabled. `MakeBooleanRow` uses `SCheckBox`.

## Setters and defaults

`ULuxEditorSubsystem::SetIntensity` clamps to project Minimum/Maximum Intensity (initially 0–50,000), while `SetAttenuationRadius` clamps to project Minimum/Maximum Attenuation Radius (initially 0–10,000 cm). Other setters update cached user values, mark preferences dirty, and immediately apply to the transient `UPointLightComponent` if it exists.

| Lux property | Native point-light update |
| --- | --- |
| Intensity | `SetIntensity` |
| Attenuation Radius | `SetAttenuationRadius` |
| Light Color | `SetLightColor` |
| Cast Shadows | `SetCastShadows` |

<figure class="doc-media" data-kind="image" data-media-id="everyday-value-flow">
<img src="../../../assets/media-placeholder.png" alt="Lux native menu fields mapped to subsystem properties and point light setters." loading="lazy">
<figcaption>The native menu writes editor-user preferences and the active transient point light together.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a diagram showing the four Headlamp menu controls calling ULuxEditorSubsystem setters, which write ULuxUserSettings and update the transient UPointLightComponent. Show project range clamps only on Intensity and Attenuation Radius.</span></figcaption>
</figure>

## Rendering constraints

Shadow cost and the visible effect of color/intensity depend on renderer features and scene exposure. A setter receiving a valid value is not proof that every view or material responds visibly.

Source: [SLuxViewportControl.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/SLuxViewportControl.cpp), [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For practical use and expected results, [read Design](DESIGN.md).
