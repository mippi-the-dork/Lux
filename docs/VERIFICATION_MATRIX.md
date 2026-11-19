# Lux v2.0.10 Verification Matrix

**Target:** UE 5.8.x · Windows 64-bit · Lux v2.0.10.  
**Status:** Test cases prepared; **not run** in this documentation pass. A reviewed C++ function does not count as a passed Editor test.

## Record the test environment

Record exact Unreal version, Lux commit/release, project name and rendering path, Windows build, viewport layout, installed plugin location, tester/date, and log/screenshot evidence for each executed case.

## Unreal Editor

| ID | Scenario | Expected result | Status |
| --- | --- | --- | --- |
| LUX-01 | Fresh compatible Editor load | Lux icon at beginning of right-anchored Level Editor viewport toolbar group | Not run |
| LUX-02 | Click icon twice | Gray → Accent Blue → gray; light created/destroyed; separate arrow unaffected | Not run |
| LUX-03 | Open arrow while headlamp off | Settings open without turning light on | Not run |
| LUX-04 | Scrub/type Intensity and Radius | Immediate property changes, project min/max respected | Not run |
| LUX-05 | Open Light Color picker | Native picker updates Lux color without modifying placed lights | Not run |
| LUX-06 | Toggle Cast Shadows | Corresponding native point-light shadow setting changes | Not run |
| LUX-07 | Open Advanced Lighting, change each property | Valid native values; renderer-dependent effects described accurately | Not run |
| LUX-08 | Toggle Use Temperature and change Kelvin | Temperature input disabled when off, enabled when on | Not run |
| LUX-09 | Swap between two perspective Level Editor viewports | Single light tracks the most recently interacted perspective camera | Not run |
| LUX-10 | Interact with orthographic, PIE and asset editor viewports | Those cameras are not followed by Lux | Not run |
| LUX-11 | Use two lit Level Editor viewports | Same shared-world light may affect both; no second light created | Not run |
| LUX-12 | Change levels with Lux enabled | Old component cleaned up and recreated for appropriate new Editor world | Not run |
| LUX-13 | Disable Lux and inspect Outliner / save level | No authored Light Actor, no temporary headlamp saved in map | Not run |
| LUX-14 | Adjust user values, restart Editor | Values preserved, Lux starts disabled | Not run |
| LUX-15 | Change project Intensity/Radius bounds | Current personal values clamp to allowed range | Not run |
| LUX-16 | Reset to Project Defaults while on and off | All light properties reset, enabled state unchanged | Not run |
| LUX-17 | Verify high radius with shadows vs shadows disabled | Project-relevant render performance measured without invented benchmarks | Not run |
| LUX-18 | Disable plugin/shutdown while active | No lingering light, input processor, callbacks or UI | Not run |

## Documentation website

| ID | Scenario | Expected result | Status |
| --- | --- | --- | --- |
| DOC-01 | Load Lux Docs root and all five category overviews | All pages and topic links render | Static links to check; browser not run |
| DOC-02 | Switch Design / Technical on every topic | Correct paired pages and active selection | Not run |
| DOC-03 | Search a page title and a phrase inside a body | Title search immediate; body search finds relevant excerpt | Not run |
| DOC-04 | View hero, real Lux images/GIF and placeholder figures | No overflow; captions and capture instructions legible | Not run |
| DOC-05 | Open Pages on phone/tablet/desktop sizes | Sidebar, TOC, tables and image widths usable | Not run |
| DOC-06 | Keyboard navigation, focus, Escape and links | No keyboard trap; clear focus state | Not run |
| DOC-07 | Test links to GitHub source, releases, issues and Fab | Correct public destinations | Not run |

## Recording results

Mark an individual case **Passed, Failed, Blocked or Not Applicable** only after execution with the exact build, steps and observed evidence. Keep failures as visible records, not erased assumptions.

The documentation pages are source-reviewed but do not certify that every renderer or source-control setup behaves identically.

[Documentation Audit](DOCUMENTATION_AUDIT.md) · [Lux Controls](02-headlamp-controls/README.md)
