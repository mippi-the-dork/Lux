# Practical Lighting Inspection Workflows — Technical

**Lux v2.0.10 · Source-reviewed implementation reference**

## Workflow to implementation map

| User task | Lux subsystem path | Native/render dependency |
| --- | --- | --- |
| Navigate interior | `SetHeadlampState`, `Tick`, `EnsureLight` | Valid perspective Editor camera |
| Brightness and reach | `SetIntensity`, `SetAttenuationRadius` | Project clamps, surface distance, exposure |
| Shadow inspection | `SetCastShadows` | Movable point-light shadow method |
| Material response | `SetLightColor`, `SetSourceRadius`, `SetSpecularScale` | Material and renderer support |
| Fog/translucency | `SetVolumetricScatteringIntensity`, `SetAffectTranslucentLighting` | Fog and translucency renderer path |

## Costs and limits

The headlamp is a movable point light. High intensity alone doesn't guarantee expensive rendering, but large influence radii and dynamic shadows can increase work, as can supported volumetric and translucent contributions. Lux doesn't offer independent per-viewport render isolation.

<figure class="doc-media" data-kind="image" data-media-id="inspection-performance">
<img src="../../../assets/media-placeholder.png" alt="Lux editor headlamp features influencing renderer cost." loading="lazy">
<figcaption>The inspection light remains a transient editor component while rendering features determine the lighting cost.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a conceptual cost diagram showing one Lux point light with attenuation radius, Cast Shadows, volumetric and translucent contributions labeled. Avoid invented frame times or performance numbers.</span></figcaption>
</figure>

## Verification guidance

Compare the same scene from the same camera with Lux on/off, keeping project exposure fixed. Record which renderer/fog/shadow configuration was used before claiming a specific advanced control produces a visible result.

Source: [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For workflows and expected behavior, [read Design](DESIGN.md).
