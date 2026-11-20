---
quick_id: 261120-bqp
status: complete
---
- Merge von origin/main (25cf856) in elm-0.10.4-fixes: nur scripts/plattform_abgleich/plattform_abgleich.py, keine Konflikte, byte-gleich mit origin/main.
- `bauen --help` zeigt `--verbund {einzeln,zusammen}` (mit PYTHONPATH auf ELMonkey/core).
- Befund (vorbestehend, nicht durch den Merge): im Skill-Repo fehlt `core/`, das Skript läuft ohne installiertes elmonkey-core nicht (ModuleNotFoundError: elmonkey) – auch die alte Fassung nicht.
