---
quick_id: 261119-u4u
status: complete
completed: 2026-11-19
commit: b5d6ee7
---
# Quick 261119-u4u: origin/main in elm-0.10.4-fixes gemergt — Summary

Merge-Commit **b5d6ee7** (Eltern 667fa88 + e567052), Autor-Mail mozzi666@gmail.com, nicht gepusht, Zweig unverändert
elm-0.10.4-fixes. Damit hat der installierte Skill den ELMonkey-Stand 630e6e0 (Auslöser „Projekt synchronisieren“,
Rezept `plattform-abgleich.md` live BFW07, Befehl `bauen`, `reference/diff-plattform.md`, `scripts/plattform_abgleich/`,
Installer-Umstellung) und behält alle 24 Zweig-Commits (THN-Lerneinträge 17.11., `archicad-nach-plattform.md`).

## Konflikte je Datei

| Datei | Lösung |
|-------|--------|
| `.planning/STATE.md` | Quick-Tasks-Tabelle vereinigt: Zweig-Zeilen 17.11.–12.11., darunter main-Zeilen 261109-mr8/-mnr (09.11.). Keine Doppelungen. Ältere Zeilen darunter unverändert (waren schon vorher nicht streng sortiert). |
| `README.md` (2) | Status: main-Fassung 0.11.12 (09.11.) oben; die Zweig-Zeile zu 0.10.4 bleibt darunter als „Earlier · Früher – Status 0.10.4 (03.11.2026)“ (Fakten SetLayerAttributes-Aliasse, 0.10.3 live THN 3.014 Wände bleiben erhalten). Fußzeile: main-Fassung (ELMonkey 0.11.12 mit Link; behebt auch das doppelte „November · November“). |
| `SKILL.md` | Rezeptliste mit beiden Zeilen: `archicad-nach-plattform.md` (Zweig) + `plattform-abgleich.md` mit „Projekt synchronisieren“ (main), `gebaeude-und-aussenanlage.md` einmal. 169 Zeilen. |
| `recipes/curtain-walls.md` (3) | Raster-Bullet + Rasterursprung: **Zweigfassung** (durchgestrichene „Segmentanfang“-Aussage + eigener Abschnitt „Rasterursprung (`gridOrigin`)“) — sie enthält alle Fakten der main-Bullet „Ursprungspunkt des Rasters“ und zusätzlich den Live-Test 17.11. mit 0.11.16 (Ursprung per API nicht verschiebbar, `GetCurtainWallFramesELM`). `angle`-Zeile: beide zusammengeführt (main: Favoriten speichern `SlantAngle 90`, 0 ab 0.11.12.2 akzeptiert, wirkt nicht, Link Zwischenstand-AC29; Zweig: per Create nicht anlegbar, Weg über Kopie), beide Datums-Marker. |
| `recipes/wall-operations.md` (2) | **main-Fassung**: eigener Abschnitt „Wände gegen den Bestandsplan abgleichen“ + TOC-Eintrag 14, Leibungs-Bögen als Unterpunkte von Punkt 6. Die Zweig-Punkte 8–11 haben dieselben Fakten (Zahlen 1:1 geprüft), daher keine Doppelung. Datei jetzt identisch mit main. |
| `reference/mcp-extension.md` (2) | Bundle-Wechsel: main-Fassung (nummeriert, `###`) plus Zweig-Zeile „Live THN (Teamwork, AC29):“. Zweiter Konflikt: Zweig-Seite leer, main-Abschnitte ELMonkey 0.11.0, ELM_SAB 0.11.13 GetSolidBounds, 0.11.12 ExportSurfaces übernommen (im Zweig nicht vorhanden, also keine Doppelung). |
| `reference/ui-aufgaben.md` | Zweig-Seite leer → main-Bullet „Sichtprüfung per API“ (FitInWindow) übernommen. |

## Prüfungen

- Keine Konfliktmarker mehr (`grep -rn '^<<<<<<<\|^=======$\|^>>>>>>>'` außerhalb .git leer).
- `git status`: sauber bis auf die ungetrackten Quick-Ordner (261013-mb5, 261119-u4u).
- `grep -c "Projekt synchronisieren" SKILL.md` = 1; `recipes/archicad-nach-plattform.md` vorhanden; alle 42 relativen Links in SKILL.md zeigen auf existierende Dateien.
- Doppelte Überschriften nur dort, wo sie schon in main doppelt waren (curtain-walls, mcp-extension, openings).

## Hinweise

- Bewusste Doppelung: FitInWindow-Sichtprüfung steht in `reference/mcp-extension.md` (Zweig) und `reference/ui-aufgaben.md` (main) — beide behalten.
- Rückweg-Liste (Inhalte, die noch nach mozzi86/ELMonkey müssen): `rueckweg_elmonkey.md` in diesem Ordner, 10 Einträge in SKILL.md, `recipes/archicad-nach-plattform.md`, `recipes/curtain-walls.md`, `reference/mcp-extension.md`.

## Deviations

Keine. Kein Push, kein Zweigwechsel.

## Self-Check: PASSED
- b5d6ee7 vorhanden, Eltern 667fa88 + e567052
- rueckweg_elmonkey.md und diese SUMMARY vorhanden
