# Toolbar and Headlamp Toggle — Technical

**Lux v2.0.10 · Source-reviewed implementation reference**

## Slate composition

`SLuxViewportControl::Construct` creates a native `SHorizontalBox` containing a 24px-high `SButton` for the icon and a separate 24px-high `SComboButton` for its menu. The button uses `FLuxStyle::GetToolbarIcon()` and the application `SimpleButton` style.

## Activation

The icon's `OnClicked` locates the `ULuxEditorSubsystem`, toggles `SetHeadlampState`, and returns a handled Slate reply. The icon tint uses `EStyleColor::AccentBlue` when active and foreground otherwise. The dropdown's `OnGetMenuContent` creates the menu and never toggles the light.

<figure class="doc-media" data-kind="image" data-media-id="toolbar-slate-composition">
<img src="../../../assets/media-placeholder.png" alt="Slate widget hierarchy of Lux toolbar controls." loading="lazy">
<figcaption>The native Slate toolbar separates the Lux activation button from the settings menu.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a labeled technical mockup of SHorizontalBox containing the SButton with SVG icon and SComboButton with arrow, with arrows to SetHeadlampState and MakeSettingsMenu. Include active/inactive tint annotations.</span></figcaption>
</figure>

## Toolbar registration and cleanup

`FLuxModule::RegisterMenus` extends `LevelEditor.ViewportToolBar`; `StartupModule` registers its ToolMenus callback and Slate input preprocessor, while `ShutdownModule` unregisters both and frees style and tracker state. Asset-editor and PIE toolbars are outside that extension.

Source: [Lux.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/Lux.cpp), [SLuxViewportControl.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/SLuxViewportControl.cpp).

---

For practical use and expected results, [read Design](DESIGN.md).
