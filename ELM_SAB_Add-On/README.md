# ELM_SAB_Add-On

SAB-eigenes Archicad-Add-On mit zusätzlichen **JSON-Befehlen** (Namespace `ELM_SAB`) —
die Erweiterungsschicht neben [Tapir](https://github.com/ENZYME-APD/tapir-archicad-automation),
erreichbar über dieselbe JSON-API und damit über den `tapir-archicad-mcp`-Server (Claude).

**Warum ein eigenes Add-On statt Tapir-Fork?** Vorbild ist
[tlorantfy/archicad-additional-json-commands](https://github.com/tlorantfy/archicad-additional-json-commands):
ein kleines Zusatz-Add-On bleibt von Tapir-Updates unberührt, und beide sind parallel nutzbar.

## Befehle

| Befehl | Status | Zweck |
|---|---|---|
| `SetPenOfElements` | v0.1 — ungebaut, Compile-Check steht aus | Stifte von 2D-Elementen (Hatch, Line, PolyLine, Arc, Circle, Spline, Text) auf definierte Stift-Indizes setzen. Use-Case: importierte Fachplaner-DWGs mit wilden RGB-Stiften auf SAB-Stifttabelle normalisieren (THN-Projekt, Nagel-Brandschutzpläne). |

Geplant: `GetPenOfElements` (Diagnose vor Änderung), ggf. `SetFillTypeOfElements`.

## Build (macOS)

Voraussetzungen: Xcode + CMake + **Archicad API DevKit 29** (Download via Graphisoft Developer-Seite
oder automatisch, siehe `Tools/`).

```bash
cd ELM_SAB_Add-On
cmake -B Build -DAC_VERSION=29 -DAC_API_DEVKIT_DIR=/pfad/zum/DevKit .
cmake --build Build --config Debug
```

Ergebnis-Bundle nach `/Applications/Graphisoft/Archicad 29/Add-Ons/` kopieren, Archicad neu starten.

**Hinweis MDID:** `RFIX/AddOnFix.grc` enthält noch die Platzhalter-Developer-ID (1/1).
Für Verteilung über den lokalen Rechner hinaus eine registrierte Graphisoft-Developer-ID eintragen.

## Aufruf über MCP / JSON-API

```python
# über archicad-python / JSON-API:
result = acc.ExecuteAddOnCommand(
    act.AddOnCommandId('ELM_SAB', 'SetPenOfElements'),
    {
        'elements': [{'elementId': {'guid': '...'}}],
        'contourPen': 20,
        'fillForegroundPen': 20,
        'fillBackgroundPen': 0
    }
)
```

Der typische Workflow (Claude / archicad-Skill):
1. Schraffuren/Linien per Ebenen-Filter finden (`elements_get_elements_by_type` + Ebene)
2. `SetPenOfElements` mit Ziel-SAB-Stiften aufrufen
3. Stichprobe visuell prüfen

## Basis

Aufgesetzt auf [GRAPHISOFT/archicad-addon-cmake](https://github.com/GRAPHISOFT/archicad-addon-cmake)
(Template, MIT) — `Tools/` stammt aus archicad-addon-cmake-tools. Command-Muster nach Tapir (MIT).
