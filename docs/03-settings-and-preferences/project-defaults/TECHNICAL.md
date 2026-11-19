# Project Defaults and Limits — Technical

**Lux v2.0.10 · Source-reviewed implementation**

## Config ownership

`ULuxProjectSettings` is `UCLASS(Config=Editor, DefaultConfig)` and registers itself under **Project → Plugins → Lux** through a stable settings section name. It owns Intensity and Radius minimum/maximum/default values and reset values for all remaining headlamp properties.

## Runtime bounds

`ULuxEditorSubsystem::SetIntensity` and `SetAttenuationRadius` clamp to project bounds. `RefreshProjectLimits` re-applies those setters if project limits change. Project default values are constrained to their respective allowed range.

## Advanced values

Advanced Defaults are reset choices; the supported setter bounds are fixed for Source Radius (0–10000), Volumetric Scattering (0–100), Indirect Lighting (0–6), Specular Scale (0–1), and Temperature (1000–20000 K).

<figure class="doc-media" data-kind="image" data-media-id="project-config-flow">
<img src="../../../assets/media-placeholder.png" alt="Lux shared Project Settings and individual preferences data flow." loading="lazy">
<figcaption>Project defaults constrain supported numeric values and supply the reset targets for personal Lux preferences.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create an ownership diagram of ULuxProjectSettings (Config=Editor) feeding Intensity/Radius constraints and Reset to Project Defaults, while ULuxUserSettings keeps separate per-user selections.</span></figcaption>
</figure>

## Settings UI route

The dropdown's **Lux Project Settings** command uses `ISettingsModule::ShowViewer("Project","Plugins","Lux")`, matching the settings registration identity; other plugin pages should not be opened by this command.

Source: [LuxProjectSettings.h](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Public/LuxProjectSettings.h), [LuxProjectSettings.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxProjectSettings.cpp).

---

For practical editor guidance, [read Design](DESIGN.md).
