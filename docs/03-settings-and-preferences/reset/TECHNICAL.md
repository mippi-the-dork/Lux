# Reset to Project Defaults — Technical

**Lux v2.0.10 · Source-reviewed implementation**

## Reset implementation

`ULuxEditorSubsystem::ResetToProjectDefaults()` reads `GetDefault<ULuxProjectSettings>()`, overwrites the cached `ULuxUserSettings` values, clamps numeric values to their supported ranges, and calls `MarkPreferencesDirty()` and `ApplyLightSettings()`.

It handles all eleven light properties: Intensity, Attenuation Radius, Color, Cast Shadows, Source Radius, Volumetric Scattering Intensity, Use Temperature, Temperature, Specular Scale, Indirect Lighting Intensity and Affect Translucent Lighting.

## No activation toggle

The reset function does **not** modify `bEnabled`. If Lux is off, it updates stored preferences; if Lux is on, the values are also applied to its existing transient component immediately.

<figure class="doc-media" data-kind="image" data-media-id="reset-state-update">
<img src="../../../assets/media-placeholder.png" alt="Lux reset data flow without altering session on/off state." loading="lazy">
<figcaption>Reset copies the project defaults into personal preferences and refreshes the live temporary light if one exists.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a flowchart from the Lux menu Reset command to ULuxProjectSettings, through supported clamps into ULuxUserSettings, and finally to ApplyLightSettings for an existing transient point light. Explicitly keep bEnabled outside the flow.</span></figcaption>
</figure>

## Why use a transaction-free preference update?

These values belong to personal Lux editor preferences, not the level. Reset is not a normal Actor transformation or light-Actor edit. It should not be confused with Undo of the level's authored content.

Source: [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For practical editor guidance, [read Design](DESIGN.md).
