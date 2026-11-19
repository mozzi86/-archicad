# Rückweg nach mozzi86/ELMonkey (skills/archicad)

Stand: Merge-Commit b5d6ee7 auf elm-0.10.4-fixes (Eltern 667fa88 + e567052), 2026-11-19.
Ermittelt mit `git diff origin/main HEAD -- SKILL.md recipes reference commands scripts`.

Diese Inhalte stehen nach dem Merge im installierten Skill, aber NICHT in origin/main (= ELMonkey 630e6e0).
Sie müssen nach mozzi86/ELMonkey `skills/archicad`, sonst gehen sie beim nächsten Spiegel ELMonkey → -archicad verloren.
`commands/` und `scripts/`: keine Unterschiede.

| # | Datei | Abschnitt / Stelle | Datums-Marker | Art |
|---|-------|--------------------|---------------|-----|
| 1 | `SKILL.md` | Abschnitt „## Holen aus Archicad = volles Paket“ (vor „Wo welches Wissen liegt“) | `<!-- 2026-11-16 -->` | neu (13 Zeilen) |
| 2 | `SKILL.md` | Rezeptliste: Zeile `recipes/archicad-nach-plattform.md` (vor `gebaeude-und-aussenanlage.md`) | `<!-- 2026-11-16 -->` | neu (1 Zeile) |
| 3 | `recipes/archicad-nach-plattform.md` | ganze Datei (Ablauf 1–7, Fallen 1–6, „Was der Nutzer entscheidet“), live BSZ 10659 | `<!-- 2026-11-16 -->` | neue Datei (59 Zeilen) |
| 4 | `recipes/curtain-walls.md` | „Spaltenraster nachträglich ändern“: Bullet „Volle Feldliste … Segmentanfang“ durchgestrichen + „Überholt (siehe Rasterursprung)“; ersetzt die main-Bullets „Volle Feldliste“ und „Ursprungspunkt des Rasters“ | `<!-- 2026-11-17 -->` | geändert |
| 5 | `recipes/curtain-walls.md` | neuer Unterabschnitt „### Rasterursprung (`gridOrigin`)“ — u. a. Live-Test 17.11. (AC29 Mac, ELMonkey 0.11.16): Ursprungspunkt per API nicht verschiebbar (`gridOriginReached: false`), `GetCurtainWallFramesELM` (0.11.16) mit `classRole`/`uBeg`/`uEnd`, fester Pfosten 1,016 m = normaler Rasterpfosten, ungleiche Teilungen nur per Neubau | `<!-- 2026-11-17 -->` | neu |
| 6 | `recipes/curtain-walls.md` | Parametertabelle Zeile `angle`: main-Text + Zusatz „Liegende Fassaden (angle 0) lassen sich per Create nicht anlegen … Weg über Kopie“ (Link auf Abschnitt „Liegende Fassaden (Bodenfliesen, Abhangdecken)“) und „nicht rad“ | `<!-- 2026-11-09 -->` + `<!-- 2026-11-16 -->` | zusammengeführt |
| 7 | `reference/mcp-extension.md` | Navigator-Abschnitt (nach LayoutBook-Bullet): drei Bullets „Navigator-Namen zurücklesen nur über Tapir“, „Plankopf-Titel = Zeichnungsname = Name des Quell-Ausschnitts“, „`RenameNavigatorItem` in Teamwork“ (Code -2130312910, Kriechkeller WD) | `<!-- 2026-11-17 -->` | neu |
| 8 | `reference/mcp-extension.md` | „### Bundle-Wechsel am Mac im Teamwork-Betrieb“: Zeile „Live THN (Teamwork, AC29):“ | `<!-- 2026-11-17 -->` | 1 Zeile ergänzt |
| 9 | `reference/mcp-extension.md` | Bullet „Kein `ModifyCurtainWall` (2026-07-25)“ durchgestrichen + „Überholt ab ELMonkey 0.11.12.1“ (`SetCurtainWallSegmentELM`) | `<!-- 2026-11-17 -->` | geändert |
| 10 | `reference/mcp-extension.md` | CaptureView-Abschnitt: Bullet „Sichtprüfung auf einen Bereich (live 2026-11-17)“ (FitInWindow zoomt immer auf alles) — steht in main nur in `reference/ui-aufgaben.md` | `<!-- 2026-11-17 -->` | neu (Doppelung zu ui-aufgaben bewusst) |

Außerhalb des Skill-Inhalts (nicht nach ELMonkey nötig, nur Info): README.md hat zusätzlich die Zeile
„Earlier · Früher – Status 0.10.4 (03.11.2026)“ unter dem Status 0.11.12.
