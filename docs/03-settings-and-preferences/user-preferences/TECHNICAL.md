# Per-User Preferences and Session State — Technical

**Lux v2.0.10 · Source-reviewed implementation**

## Class and config mapping

`ULuxUserSettings` inherits `UObject` and uses `Config=EditorPerProjectUserSettings`, storing Intensity, AttenuationRadius, Color, CastShadows, advanced values and one-time initialization flags. `ULuxProjectSettings` uses `Config=Editor` instead.

`ULuxEditorSubsystem` keeps `bEnabled=false` as a session-only C++ field. The `TransientLightComponent` is constructed with `RF_Transient` and is not serialized into level content.

## Save batching

Property setters call `MarkPreferencesDirty()` and update the live component. In `Tick`, pending user preferences are saved after **0.5 seconds** without another change; `Deinitialize` flushes changes at shutdown. This avoids writing the config file repeatedly for every scrubbed numeric value.

<figure class="doc-media" data-kind="image" data-media-id="preferences-storage">
<img src="../../../assets/media-placeholder.png" alt="Lux configuration and transient state persistence diagram." loading="lazy">
<figcaption>Project defaults, personal values, session activation and the transient component use separate storage lifetimes.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Make a four-lane storage diagram: Config=Editor project defaults, EditorPerProjectUserSettings personal properties, session-only bEnabled, and RF_Transient UPointLightComponent. Show which survive editor restart.</span></figcaption>
</figure>

## Migration

`Initialize` checks per-user initialization flags. Existing user preferences are preserved when new advanced values are introduced; only missing defaults are filled from project settings.

Source: [LuxUserSettings.h](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Public/LuxUserSettings.h), [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For practical editor guidance, [read Design](DESIGN.md).
