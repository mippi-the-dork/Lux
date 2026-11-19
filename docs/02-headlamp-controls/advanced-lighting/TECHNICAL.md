# Advanced Lighting Controls — Technical

**Lux v2.0.10 · Source-reviewed implementation reference**

## Advanced property mapping

`SLuxViewportControl::PopulateAdvancedMenu` declares an Advanced **Lighting** section with four native numeric widgets and a checkbox. `ULuxEditorSubsystem` forwards changes to the same transient `UPointLightComponent`:

| Setting | Setter | Supported value bounds |
| --- | --- | --- |
| Source Radius | `SetSourceRadius` | 0–10,000 cm |
| Volumetric Scattering Intensity | `SetVolumetricScatteringIntensity` | 0–100 |
| Indirect Lighting Intensity | `SetIndirectLightingIntensity` | 0–6 |
| Specular Scale | `SetSpecularScale` | 0–1 |
| Affect Translucent Lighting | `SetAffectTranslucentLighting` | Boolean |

These limits are implemented in the corresponding setter functions; they are not configurable minimum/maximum project settings like Intensity and Attenuation Radius. The Project Settings Advanced Defaults configure **reset values**, not new bounds.

<figure class="doc-media" data-kind="image" data-media-id="advanced-property-routing">
<img src="../../../assets/media-placeholder.png" alt="Lux advanced lighting setter diagram with ranges." loading="lazy">
<figcaption>Advanced Lighting controls map directly to native point-light properties.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a five-row chart mapping Advanced submenu controls to ULuxEditorSubsystem setter calls and UPointLightComponent operations. Indicate each numeric bound and label translucency as a boolean.</span></figcaption>
</figure>

## Effect visibility

Volumetric contributions require compatible fog and rendering. Indirect lighting depends on the supported rendering path; shadows depend on light methods and geometry. None of these features writes a level Light Actor.

Source: [SLuxViewportControl.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/SLuxViewportControl.cpp), [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For practical use and expected results, [read Design](DESIGN.md).
