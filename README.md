# Archicad-Skill für Claude Code

Ein Claude-Code-Skill, der Claude befähigt, im laufenden Archicad-Projekt zu arbeiten — Wände/Decken/Fenster/Türen klassifizieren, Property-Werte setzen, Bulk-Operationen ausführen, IFC-Probleme diagnostizieren, DWG→IFC-Pipelines bauen. Über den Archicad-MCP-Server (`mcp__archicad__*`).

Entwickelt von **Mudi** (Architekturbüro), live-verifiziert an realen -Projekten  Mit -Office-spezifischem Wissen ausgestattet (Klassifizierung, Z_/A_-Layer-Schema, bekannte Template-Bugs).

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
| **Fast-Path für Read-only-Queries** (`/arc`) | ✅ neu 2026-07 | `commands/arc.md` |
| **Direkter HTTP-CLI-Wrapper** (`arc`) | ✅ neu 2026-07 | `scripts/arc` |

## Voraussetzungen

1. **Claude Code** installiert ([Anthropic-Doku](https://docs.anthropic.com/claude-code))
2. **Archicad-MCP-Server** konfiguriert in deiner `~/.claude/mcp.json`
3. **Archicad 29+** mit aktiviertem MCP-Plugin laufend
4. **Archicad-Projekt offen** (Solo oder Teamwork)

## Installation

### Schritt 1 — Skill nach `~/.claude/skills/archicad/` kopieren

### Schritt 2 — Claude Code neu starten

Der Skill wird beim nächsten Start automatisch erkannt. Der `description`-Trigger im Frontmatter matcht auf konkrete User-Utterances („klassifiziere alle Wände", „Bodenbelag synchronisieren", „IFC-Diagnose", …) sowie auf jeden Aufruf von `mcp__archicad__*`-Tools.

### Schritt 3 — Verifikation

In Claude Code eingeben:
```
Welche Archicad-Instanz läuft?
```
Claude sollte den `archicad`-Skill nutzen und via `mcp__archicad__discovery_list_active_archicads` antworten.

### Schritt 4 — Fast-Path aktivieren (optional, empfohlen)

Der Skill kommt mit zwei Beschleunigern für Read-only-Queries und Bulk-Operationen:

**a) `/arc`-Slash-Command** (für Einzelfragen wie „wieviele Zonen?", „welches Projekt?"):
```bash
ln -sf ~/.claude/skills/archicad/commands/arc.md ~/.claude/commands/arc.md
```

**b) `arc`-CLI** (direkter HTTP-Zugriff, umgeht MCP-Pagination):
```bash
ln -sf ~/.claude/skills/archicad/scripts/arc ~/.local/bin/arc
arc doctor   # Self-Check: Instanzen, Tapir-Add-On, MCP-Config
```

Nutzung:
```bash
arc ports              # aktive Instanzen
arc info               # Projekt + Story
arc zones              # alle Zonen-GUIDs
arc tapir GetElementsByType '{"elementType":"Wall"}'
arc call GetProjectInfo
```

Details: `scripts/arc --help` und `reference/mcp-conventions.md § Direkter HTTP-Zugriff`.

**Namens-Historie:** früher `/archicad` und `ac` — umbenannt weil `ac` mit dem macOS-System-Binary `/usr/sbin/ac` (BSD process accounting) kollidiert und `/archicad` mit dem Skill-Namen. Falls du noch alte Symlinks hast: `rm ~/.claude/commands/archicad.md ~/.local/bin/ac` und die Zeilen oben neu ausführen.

## Was der Skill NICHT kann

Ehrliche Scope-Grenzen (siehe `reference/dwg-ifc-kg300.md` § „Was die Pipeline NICHT kann"):

- **IFC-Übersetzer-Settings** ändern → UI-Aufgabe, MCP hat keine Endpoints
- **Werkzeug-Standard-Einstellungen** anpassen → UI-Aufgabe
- **Komposite-Zuweisung** an existierendes Element → `set_details.typeSpecificDetails` ist WallSettings-only
- **Wand/Tür/Fenster/Curtain-Wall erstellen** → kein MCP-Create-Endpoint in v29 (User zeichnet manuell)
- **DWG-Annotation-Parsing** (Raumcodes, BRH-Werte, Plantext-Specs) → out-of-scope, Backlog

## Benutzungs-Beispiele

**Bulk-Klassifizierung aller Wände:**
```
Klassifiziere alle Wände im offenen Projekt als SAB > Wand. Mit Teamwork-Reserve + Verify.
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

## Update-Workflow

Wenn Mudi den Skill weiterentwickelt:
1. Mudi pusht Änderungen ins OneDrive-Vorlagen-Verzeichnis
2. Du kopierst neu (Schritt 1 wiederholen) oder synct deinen lokalen Pfad
3. Optional: `git log --oneline` in deinem lokalen `~/.claude/skills/archicad/.git` zeigt die Commit-Historie

## Mitwirken / Feedback

Wenn du beim Arbeiten was findest:
- **Neuer Tool-Name** den MCP zurückgibt, der nicht dokumentiert ist → in `recipes/<passende-datei>.md` mit Datums-Marker ergänzen
- **Bug** im Schwarz-Template → in `reference/schwarz-office-facts.md` § „Bekannte Schwarz-Template-Bugs"
- **Neues Workflow-Pattern** das du oft brauchst → eigenes Recipe oder Reference ergänzen

Skill-Update zurück an Mudi (per Direkt-Nachricht oder OneDrive-Commit) damit alle profitieren.

## Versionshistorie

Siehe `git log` im Skill-Ordner. 38+ atomic Commits mit Phase-1-bis-6-Entwicklungshistorie + Memory-Konsolidierung.

## Lizenz / Nutzung

Bitte nicht ohne Rücksprache mit Mudi außerhalb des Büros weitergeben — enthält office-spezifische GUIDs, Layer-Konventionen und Workflows.

---

**Autor:** Mudi · **Office:**  · **Stand:** Mai 2026 · **Skill-Version:** v1.0-rc1
