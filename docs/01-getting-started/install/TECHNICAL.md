# Installation and Compatibility — Technical

**Lux v2.0.10 · Unreal Engine 5.8.x · Win64 · Editor-only**

## Descriptor contract

`Lux.uplugin` identifies `VersionName: "2.0.10"`, `EngineVersion: "5.8.0"`, `Type: "Editor"`, `LoadingPhase: "PostEngineInit"`, and `PlatformAllowList: ["Win64"]`. `CanContainContent` is false even though the repository includes Editor Utility Widget assets; the active toolbar UI is native Slate.

## Build and startup

`Source/Lux/Lux.Build.cs` declares editor-side dependencies. `FLuxModule::StartupModule` initializes the Lux Slate style, registers an input preprocessor when Slate is initialized, and adds its ToolMenus startup callback. Shutdown unregisters the preprocessor, menu ownership, tracker and Slate style.

## Toolbar scope

`FLuxModule::RegisterMenus` extends the Level Editor viewport toolbar rather than every asset-editor toolbar. Therefore a game viewport or an asset preview does not promise the Lux control.

<figure class="doc-media" data-kind="image" data-media-id="install-toolbar-location">
<img src="../../../assets/media-placeholder.png" alt="Lux position within the native Unreal Editor viewport toolbar." loading="lazy">
<figcaption>Lux is registered with the Level Editor viewport's native toolbar controls.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture the Level Editor toolbar with the Lux icon and its neighboring dropdown arrow highlighted immediately before the right-anchored viewport controls. Keep the surrounding toolbar items visible for orientation.</span></figcaption>
</figure>

## Diagnostics

If compiled source builds fail, verify matching UE and toolchain and inspect the first Lux-specific compilation error. Avoid assuming runtime module availability or support for platforms not declared in the descriptor.

Source: [Lux.uplugin](https://github.com/mippi-the-dork/Lux/blob/main/Lux.uplugin) · [Lux.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/Lux.cpp).

---

For hands-on controls and workflows, [read Design](DESIGN.md).
