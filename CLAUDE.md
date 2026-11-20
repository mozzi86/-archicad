<!-- GSD:project-start source:PROJECT.md -->
## Project

**Archicad-Skill für Claude Code**

Ein Claude-Code-Skill, der Claude befähigt, mit dem Archicad-MCP-Server (`mcp__archicad__*`) umfassend zu arbeiten: alle gängigen Architektur- und 2D-Modellierungsoperationen, in allen CRUD-Variationen, mit kontextbewusster Discovery, asymmetrischer Sicherheit und Bulk-Klassifizierungs-Workflows. Zielgruppe: ein einzelner Architekt/Planer (der User dieses Setups), der täglich in Archicad arbeitet und Claude als Assistent für wiederkehrende Modellier-, Klassifizierungs- und Bestands-Aufgaben einsetzt.

**Core Value:** **Claude kann jederzeit in einem laufenden Archicad-Projekt arbeiten — neue Elemente erstellen, Bestand abfragen, Bulk-Operationen ausführen — ohne dass Tool-Namen oder Parameter zur Laufzeit erfunden werden müssen.** Discovery-zentriert, asymmetrisch sicher, selbst-verbessernd.

### Constraints

- **Tech Stack**: Markdown-Skill-Dateien für Claude Code, kein eigener Code. Hub-and-Spoke-Architektur (1 SKILL.md + reference/* + recipes/*).
- **MCP-Abhängigkeit**: Skill ist nur funktional, wenn der Archicad-MCP-Server (`mcp__archicad__*`) konfiguriert und Archicad mit MCP-Plugin geöffnet ist.
- **Discovery-First**: Konkrete MCP-Tool-Namen werden nicht hartkodiert, sondern als „typischer Name (Hinweis)" dokumentiert; Validierung via Discovery zur Laufzeit. Begründung: Robustheit gegen Archicad-Versionswechsel.
- **Live-Verifikation Pflicht**: Jede Recipe-Datei wird gegen das laufende Archicad geprüft, bevor sie als „fertig" gilt. Worked Example dient als Smoke-Test.
- **Sicherheit asymmetrisch**: Create + Read frei; Update + Delete mit User-Confirm + Element-ID-Aufzählung. Keine Batch-Obergrenze (User-Präferenz).
- **Self-Improvement on**: Skill wächst pro Session durch Reflection-Trigger; Einträge mit Datums-Marker, Verifikation-Loop bei Wiederholfehlern.
<!-- GSD:project-end -->
