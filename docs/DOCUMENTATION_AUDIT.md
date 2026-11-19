# Lux Documentation Audit

**Baseline:** Lux v2.0.10 current public repository.  
**Sources inspected:** `Lux.uplugin`, README, editor subsystem, tracker, native Slate control, Project Settings and User Settings classes.  
**Evidence level:** Source/editorial review. No UE editor or live GitHub Pages browser test has been executed in this documentation pass.

## Assessment

Lux's source and README already support a strong manual covering the headlamp's controls, lifecycle and limits. The new site organizes that information into **five sections, 16 feature topics and 32 complementary Design/Technical pages** with independent, task-focused guidance.

## Outstanding gaps and priorities

| Priority | Finding | Resolution / next step | Status |
| --- | --- | --- | --- |
| P0 | Confirm live website routing, Design/Technical switch and body search | Test deployed desktop/mobile site, fix any rendering or navigation regressions | Not run |
| P0 | Verify current documentation against live UE behavior | Run editor checks for toolbar, camera selection, settings and component cleanup | Source-reviewed; editor tests not run |
| P1 | Complete visual demonstrations | Replace typed screenshot/GIF placeholders with actual Unreal Editor captures using the instructions beneath each slot | Pending |
| P1 | Renderer-specific behavior varies | Verify Advanced Lighting properties in representative fog/material/rendering setups; keep limitations explicit | Not run |
| P1 | Multiple viewport and level transitions need validation | Verify tracking behavior with perspective, orthographic, PIE, layout changes and map changes | Not run |
| P1 | Settings persistence needs user testing | Test project defaults, per-user save debounce, Reset and restart behavior | Not run |
| P2 | Historical roadmap detail not yet verified | Review old release tags and commit history before assigning features to earlier versions | Pending source history |
| P2 | Accessibility and responsive layout | Check keyboard navigation, narrow layouts, image sizing, search and focus outlines | Not run |
| P2 | Pin technical source links to version tag | Replace `main` links with an immutable matching v2.0.10 tag or commit when verified | Pending |

## A complete Lux guide should answer

- Where does the control appear and how is it operated?
- What does each numeric field or checkbox change, and what are its initial defaults/bounds?
- Does this change a stored personal preference, shared project default or temporary light?
- What happens in multi-viewport, orthographic, PIE and editor-world transitions?
- What should the user see, and what renderer conditions might make a valid value seem ineffective?
- How can users return to authored lighting or reset their chosen properties?
- What native C++ class owns the behavior, and what has actually been verified?
- What screenshot or GIF demonstrates the result accurately?

## Improvement plan

**First:** Execute the [Verification Matrix](VERIFICATION_MATRIX.md) on the actual target Unreal build and deployed website. Record failures and evidence.

**Second:** Capture genuine editor media for all remaining placeholders. Keep each public-facing caption and update the separate capture-instruction line or remove it only once the asset is complete.

**Third:** Improve any category FAQ based on actual support questions and pinned release source references. Avoid adding placeholder navigation sections that do not contain user value.

**Maintenance:** Update the current version, page content, screenshots, roadmap and verification statuses together whenever plugin behavior changes.

[Media Inventory](MEDIA_INVENTORY.md) · [Verification Matrix](VERIFICATION_MATRIX.md) · [Roadmap](ROADMAP.md)
