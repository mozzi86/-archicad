# Archicad-Skill für Claude Code

Ein Claude-Code-Skill, der Claude befähigt, im laufenden Archicad-Projekt zu arbeiten — Wände/Decken/Fenster/Türen klassifizieren, Property-Werte setzen, Bulk-Operationen ausführen, IFC-Probleme diagnostizieren, DWG→IFC-Pipelines bauen. Über den Archicad-MCP-Server (`mcp__archicad__*`) plus optionalem direktem HTTP-Fast-Path.

Live-verifiziert an realen BIM-Projekten (Teamwork und Solo, AC29).

## Was ist neu in v1.1 (Juli 2026)

Auf Basis einer open source Analyse (tapir-archicad-MCP, ALAI-Archicad-CLI, ProfRino/bonsai-bim-skills, AlpacaLabs/skills-for-architects) sind fünf konkrete Verbesserungen eingeflossen:

- **`/arc`-Slash-Command** — Fast-Path für Read-only-Queries („wieviele Zonen?", „welches Projekt läuft?"). Umgeht MCP-Discovery, 3–5× schneller. → `commands/arc.md`
- **`arc`-CLI** — 210-Zeilen Python-CLI (stdlib only) für direkten HTTP-Zugriff auf die JSON-API. Verben: `ports`, `info`, `zones`, `layers`, `selected`, `tapir <cmd>`, `call <cmd>`, `doctor`. Umgeht MCP-Pagination bei Bulk-Operationen (kritisch bei >100 Elementen). → `scripts/arc`
- **Trigger-Phrase-reiche `description`** in SKILL.md — Multi-Line-Frontmatter mit konkreten deutschen User-Utterances („klassifiziere alle Wände", „Bodenbelag synchronisieren", „IFC-Diagnose"). Skill matcht damit zuverlässiger auf natürliche Anfragen. → `SKILL.md`
- **Discovery-Query Schema-Keyword-Tipp** — Bei Fehltreffern konkrete Parameter-Feldnamen an die Query anhängen (`"get walls elementType filter"` statt `"get walls"`). Der Semantic-Index von tapir-archicad-MCP indexiert auch Schema-Keywords. → `reference/mcp-conventions.md § Discovery-Pattern`
- **54 „User sagt:"-Opener** vor jedem Worked Example in allen 9 Recipes — macht Trigger-Muster für Claude explizit sichtbar. → `recipes/*.md`

Außerdem:
- **GitHub-basierte Distribution** statt OneDrive — Updates jetzt per `git pull`
- **DWG→IFC-Ceiling-Pipeline** aus dem alten Monorepo mit übernommen (5-Step, ifcopenshell-basiert) → `scripts/dwg_to_ceilings/`
- **Fehlende Sektionen aus dem Monorepo eingepflegt**: Klassifikations-System-GUID-Drift-Warnung, Ports-sind-volatil, Leere-properties-Liste-Bug, IsAlive-blocking → `reference/bulk-operations.md` + `reference/mcp-conventions.md`

## Was der Skill kann

| Bereich | Status | Datei |
|---|---|---|
| Klassifikation (bulk, Trust-but-verify) | ✅ live-verifiziert | `reference/bulk-operations.md` |
| Property-Werte setzen (Bodenbelag-Sync etc.) | ✅ live-verifiziert | `recipes/zones.md` |
| Wände-Operationen | ✅ live-verifiziert AC29 | `recipes/wall-operations.md` |
| Fenster/Türen | ✅ live-verifiziert | `recipes/openings.md` |
| Decken / Stützen / Träger | ✅ live-verifiziert | `recipes/slabs-columns-beams.md` |
| Zonen / Räume | ✅ live-verifiziert | `recipes/zones.md` |
| Vorhangfassaden | ✅ live-verifiziert | `recipes/curtain-walls.md` |
| Bibliothekselemente | ✅ live-verifiziert | `recipes/library-objects.md` |
| Surfaces / Materials / Composites | ✅ live-verifiziert | `recipes/surfaces-materials.md` |
| 2D-Hatches (Schraffuren) | ✅ live-verifiziert | `recipes/fills-hatches.md` |
| 2D-Linien / Polylinien | ✅ live-verifiziert | `recipes/lines-polylines.md` |
| DWG → IFC-Pipeline (Lageplan/KG 500) | ✅ live-verifiziert | `reference/dwg-ifc-import.md` |
| DWG → IFC für KG 300 (Wände/Decken/Stützen) | Pattern-Vorlage | `reference/dwg-ifc-kg300.md` |
| Office-Wissen (Template-Bugs, GUIDs) | konsolidiert | `reference/schwarz-office-facts.md` |
| **Fast-Path für Read-only-Queries** (`/arc`) | ✅ neu | `commands/arc.md` |
| **Direkter HTTP-CLI-Wrapper** (`arc`) | ✅ neu | `scripts/arc` |

## Voraussetzungen

1. **Claude Code** installiert ([Anthropic-Doku](https://docs.anthropic.com/claude-code))
2. **Archicad-MCP-Server** konfiguriert (z. B. via [`tapir-archicad-mcp`](https://github.com/SzamosiMate/tapir-archicad-MCP) — Registrierung als `archicad` in `~/.claude.json`)
3. **Archicad 27+** mit aktiviertem [Tapir Add-On](https://github.com/ENZYME-APD/tapir-archicad-automation) (Port 19723)
4. **Archicad-Projekt offen** (Solo oder Teamwork)

## Installation

### Schritt 1 — Repo klonen

```bash
# per SSH (empfohlen, kein Auth-Prompt bei künftigen Pulls)
git clone git@github.com:mozzi86/-archicad.git ~/.claude/repos/archicad-skill

# oder per HTTPS
git clone https://github.com/mozzi86/-archicad.git ~/.claude/repos/archicad-skill
```

### Schritt 2 — Skill-Ordner verlinken

```bash
mkdir -p ~/.claude/skills
ln -s ~/.claude/repos/archicad-skill ~/.claude/skills/archicad
```

Damit landet der Skill dort, wo Claude Code ihn findet — updates funktionieren dann per `git pull` im Repo, ohne neu zu kopieren.

### Schritt 3 — Claude Code neu starten

Der Skill wird beim nächsten Start automatisch erkannt. Der `description`-Trigger im Frontmatter matcht auf konkrete User-Utterances („klassifiziere alle Wände", „Bodenbelag synchronisieren", „IFC-Diagnose", …) sowie auf jeden Aufruf von `mcp__archicad__*`-Tools.

### Schritt 4 — Verifikation

In Claude Code eingeben:
```
Welche Archicad-Instanz läuft?
```
Claude sollte den `archicad`-Skill nutzen und via `mcp__archicad__discovery_list_active_archicads` antworten.

### Schritt 5 — Fast-Path aktivieren (optional, empfohlen)

Der Skill kommt mit zwei Beschleunigern für Read-only-Queries und Bulk-Operationen, die den MCP-Discovery-Roundtrip umgehen:

**a) `/arc`-Slash-Command** (für Einzelfragen wie „wieviele Zonen?", „welches Projekt?"):
```bash
ln -sf ~/.claude/skills/archicad/commands/arc.md ~/.claude/commands/arc.md
```

**b) `arc`-CLI** (direkter HTTP-Zugriff, umgeht MCP-Pagination bei Bulk-Operationen):
```bash
ln -sf ~/.claude/skills/archicad/scripts/arc ~/.local/bin/arc
arc doctor   # Self-Check: Instanzen, Tapir-Add-On, MCP-Config
```

Nutzung im Terminal:
```bash
arc ports              # aktive Instanzen
arc info               # Projekt + Story
arc zones              # alle Zonen-GUIDs
arc tapir GetElementsByType '{"elementType":"Wall"}'
arc call GetProjectInfo
```

Details: `arc --help` und `reference/mcp-conventions.md § Direkter HTTP-Zugriff`.

## Was der Skill NICHT kann

Ehrliche Scope-Grenzen (siehe `reference/dwg-ifc-kg300.md` § „Was die Pipeline NICHT kann"):

- **IFC-Übersetzer-Settings** ändern → UI-Aufgabe, MCP hat keine Endpoints
- **Werkzeug-Standard-Einstellungen** anpassen → UI-Aufgabe
- **Komposite-Zuweisung** an existierendes Element → `set_details.typeSpecificDetails` ist WallSettings-only
- **Wand/Tür/Fenster/Curtain-Wall erstellen** → kein MCP-Create-Endpoint in v29 (User zeichnet manuell). Ein community-Vorschlag ([Issue #10 in tapir-archicad-MCP](https://github.com/SzamosiMate/tapir-archicad-MCP/issues/10)) will 54 Creation-Tools nachziehen — nicht gemergt.
- **DWG-Annotation-Parsing** (Raumcodes, BRH-Werte, Plantext-Specs) → out-of-scope, Backlog

## Benutzungs-Beispiele

**Bulk-Klassifizierung aller Wände:**
```
Klassifiziere alle Wände im offenen Projekt nach SAB > Wand. Mit Teamwork-Reserve + Verify.
```

**Bodenbelag-Sync auf Räume:**
```
Setze die Property „Bodenbelag" auf allen Räumen im Erdgeschoss laut Schedule-Liste.
```

**IFC-Diagnose:**
```
Ich habe alles als IfcBuildingElementProxy im Export. Was ist los?
```
→ Skill kennt den Schwarz-Template-Bug und die Fix-Anleitung (siehe `reference/schwarz-office-facts.md`).

**Fast-Query per Slash-Command:**
```
/arc wieviele Fenster sind auf Story 2?
```
→ Umgeht MCP-Discovery, curl direkt an die JSON-API. 3–5× schneller.

## Update-Workflow

Da der Skill via git verlinkt ist:

```bash
cd ~/.claude/repos/archicad-skill
git pull
```

Fertig — beim nächsten Claude-Code-Start ist der neue Stand aktiv.

Wenn du eigene Änderungen hast (z. B. neue Recipes, Fixes):
```bash
cd ~/.claude/repos/archicad-skill
git add . && git commit -m "…" && git push
```

## Mitwirken / Feedback

Wenn du beim Arbeiten was findest:
- **Neuer Tool-Name** den MCP zurückgibt, der nicht dokumentiert ist → in `recipes/<passende-datei>.md` mit Datums-Marker ergänzen
- **Bug** im Office-Template → in `reference/schwarz-office-facts.md` § „Bekannte Schwarz-Template-Bugs"
- **Neues Workflow-Pattern** das du oft brauchst → eigenes Recipe oder Reference ergänzen

Commit + Push. Pull Requests sind willkommen, wenn's Fremd-User werden.

## Versionshistorie

Siehe `git log` im Repo. 40+ atomic Commits mit Phase-1-bis-6-Entwicklungshistorie, Live-Verify-Lektionen und den Fast-Path-Additions (Juli 2026).

## Lizenz / Nutzung

Enthält büro-spezifische GUIDs, Layer-Konventionen und Workflows im `reference/schwarz-office-facts.md`. Für Eigengebrauch frei nutzbar; bei Weitergabe an Fremdbüros bitte diese eine Datei entfernen oder anpassen.

Alles andere (Recipes, MCP-Conventions, Fast-Path-Tools) ist generisch AC29 + Tapir und für jeden Archicad-Nutzer sinnvoll.

---

**Repo:** [mozzi86/-archicad](https://github.com/mozzi86/-archicad) · **Stand:** Juli 2026 · **Skill-Version:** v1.1
