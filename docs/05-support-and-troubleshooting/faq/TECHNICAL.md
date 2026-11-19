# Frequently Asked Questions — Technical

**Lux v2.0.10 · Source-reviewed diagnostics**

## Quick diagnostic ownership

| Question | Implementation boundary |
| --- | --- |
| Icon not present | `FLuxModule::RegisterMenus`, Level Editor ToolMenus extension |
| Active but no light | `SetHeadlampState`, `EnsureLight`, valid editor world/perspective camera |
| Wrong viewport | `FLuxViewportTracker::GetActivePerspectiveClient` |
| Unexpected bounds | `ULuxProjectSettings` and subsystem setters |
| Temperature unavailable | `SLuxViewportControl::MakeNumberRow` enabled predicate |
| Values not restored | `ULuxUserSettings` config and save batching |
| Map change behavior | `HandleWorldCleanup`, `DestroyLight`, tick recreation |

## Testing the actual result

Source inspection can show the intended call path, but not guarantee a visible lighting effect under a project's materials and renderer. Reproduce separately with a known Level Editor perspective viewport, white light, nonzero Intensity, valid radius and simple test geometry.

<figure class="doc-media" data-kind="image" data-media-id="faq-diagnostic-branches">
<img src="../../../assets/media-placeholder.png" alt="Lux troubleshooting flow chart from common symptoms to implementation areas." loading="lazy">
<figcaption>Common Lux questions can be traced to specific editor systems and preference layers.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Draw a decision tree beginning with 'Icon missing?', 'Icon blue but no light?', 'Wrong viewport?', and 'Settings not saved?', leading to toolbar, subsystem, tracker and config ownership.</span></figcaption>
</figure>

Source: [Lux.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/Lux.cpp), [LuxEditorSubsystem.cpp](https://github.com/mippi-the-dork/Lux/blob/main/Source/Lux/Private/LuxEditorSubsystem.cpp).

---

For practical support steps, [read Design](DESIGN.md).
