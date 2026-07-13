#include "SetPenOfElementsCommand.hpp"

// ---------------------------------------------------------------------------
// Schema
// ---------------------------------------------------------------------------

GS::Optional<GS::UniString> SetPenOfElementsCommand::GetInputParametersSchema () const
{
    return GS::UniString (R"({
        "type": "object",
        "properties": {
            "elements": {
                "type": "array",
                "description": "Liste der Ziel-Elemente (2D: Hatch, Line, PolyLine, Arc, Circle, Spline, Text).",
                "items": {
                    "type": "object",
                    "properties": {
                        "elementId": {
                            "type": "object",
                            "properties": {
                                "guid": { "type": "string" }
                            },
                            "required": ["guid"]
                        }
                    },
                    "required": ["elementId"]
                }
            },
            "contourPen": {
                "type": "integer",
                "description": "Stift-Index für Kontur-/Linienstift (Hatch-Kontur, Linien, Polylinien, Bögen, Splines, Text). Optional.",
                "minimum": 1,
                "maximum": 255
            },
            "fillForegroundPen": {
                "type": "integer",
                "description": "Stift-Index für Schraffur-Vordergrund (nur Hatch). Optional.",
                "minimum": 1,
                "maximum": 255
            },
            "fillBackgroundPen": {
                "type": "integer",
                "description": "Stift-Index für Schraffur-Hintergrund (nur Hatch). 0 = transparent. Optional.",
                "minimum": 0,
                "maximum": 255
            }
        },
        "required": ["elements"]
    })");
}

GS::Optional<GS::UniString> SetPenOfElementsCommand::GetResponseSchema () const
{
    return GS::UniString (R"({
        "type": "object",
        "properties": {
            "executionResults": {
                "type": "array",
                "items": {
                    "type": "object",
                    "properties": {
                        "success": { "type": "boolean" }
                    },
                    "required": ["success"]
                }
            }
        },
        "required": ["executionResults"]
    })");
}

// ---------------------------------------------------------------------------
// Ausführung
// ---------------------------------------------------------------------------

GS::ObjectState SetPenOfElementsCommand::Execute (const GS::ObjectState& parameters, GS::ProcessControl& /*processControl*/) const
{
    GS::Array<GS::ObjectState> elements;
    parameters.Get ("elements", elements);

    Int32 contourPen = -1;
    Int32 fillFgPen  = -1;
    Int32 fillBgPen  = -1;
    const bool hasContourPen = parameters.Get ("contourPen", contourPen);
    const bool hasFillFgPen  = parameters.Get ("fillForegroundPen", fillFgPen);
    const bool hasFillBgPen  = parameters.Get ("fillBackgroundPen", fillBgPen);

    if (!hasContourPen && !hasFillFgPen && !hasFillBgPen) {
        return CreateErrorResponse (APIERR_BADPARS, "Mindestens einer von contourPen/fillForegroundPen/fillBackgroundPen muss gesetzt sein.");
    }

    GS::ObjectState response;
    const auto& executionResults = response.AddList<GS::ObjectState> ("executionResults");

    ACAPI_CallUndoableCommand ("ELM_SAB SetPenOfElements", [&] () -> GSErrCode {
        for (const GS::ObjectState& elementItem : elements) {
            const GS::ObjectState* elementId = elementItem.Get ("elementId");
            if (elementId == nullptr) {
                executionResults (CreateFailedExecutionResult (APIERR_BADPARS, "elementId fehlt"));
                continue;
            }

            API_Element element = {};
            element.header.guid = GetGuidFromObjectState (*elementId);
            GSErrCode err = ACAPI_Element_Get (&element);
            if (err != NoError) {
                executionResults (CreateFailedExecutionResult (err, "Element nicht gefunden"));
                continue;
            }

            API_Element mask = {};
            ACAPI_ELEMENT_MASK_CLEAR (mask);

            bool changed = false;

            switch (element.header.type.typeID) {
                case API_HatchID:
                    if (hasContourPen) {
                        element.hatch.contPen.penIndex = static_cast<short> (contourPen);
                        element.hatch.contPen.colorOverridePenIndex = 0;
                        ACAPI_ELEMENT_MASK_SET (mask, API_HatchType, contPen);
                        changed = true;
                    }
                    if (hasFillFgPen) {
                        element.hatch.fillPen.penIndex = static_cast<short> (fillFgPen);
                        element.hatch.fillPen.colorOverridePenIndex = 0;
                        ACAPI_ELEMENT_MASK_SET (mask, API_HatchType, fillPen);
                        changed = true;
                    }
                    if (hasFillBgPen) {
                        element.hatch.fillBGPen = static_cast<short> (fillBgPen);
                        ACAPI_ELEMENT_MASK_SET (mask, API_HatchType, fillBGPen);
                        changed = true;
                    }
                    break;

                case API_LineID:
                    if (hasContourPen) {
                        element.line.linePen.penIndex = static_cast<short> (contourPen);
                        element.line.linePen.colorOverridePenIndex = 0;
                        ACAPI_ELEMENT_MASK_SET (mask, API_LineType, linePen);
                        changed = true;
                    }
                    break;

                case API_PolyLineID:
                    if (hasContourPen) {
                        element.polyLine.linePen.penIndex = static_cast<short> (contourPen);
                        element.polyLine.linePen.colorOverridePenIndex = 0;
                        ACAPI_ELEMENT_MASK_SET (mask, API_PolyLineType, linePen);
                        changed = true;
                    }
                    break;

                case API_ArcID:
                    if (hasContourPen) {
                        element.arc.linePen.penIndex = static_cast<short> (contourPen);
                        element.arc.linePen.colorOverridePenIndex = 0;
                        ACAPI_ELEMENT_MASK_SET (mask, API_ArcType, linePen);
                        changed = true;
                    }
                    break;

                case API_CircleID:
                    if (hasContourPen) {
                        element.circle.linePen.penIndex = static_cast<short> (contourPen);
                        element.circle.linePen.colorOverridePenIndex = 0;
                        ACAPI_ELEMENT_MASK_SET (mask, API_CircleType, linePen);
                        changed = true;
                    }
                    break;

                case API_SplineID:
                    if (hasContourPen) {
                        element.spline.linePen.penIndex = static_cast<short> (contourPen);
                        element.spline.linePen.colorOverridePenIndex = 0;
                        ACAPI_ELEMENT_MASK_SET (mask, API_SplineType, linePen);
                        changed = true;
                    }
                    break;

                case API_TextID:
                    if (hasContourPen) {
                        element.text.pen = static_cast<short> (contourPen);
                        ACAPI_ELEMENT_MASK_SET (mask, API_TextType, pen);
                        changed = true;
                    }
                    break;

                default:
                    executionResults (CreateFailedExecutionResult (APIERR_BADELEMENTTYPE, "Elementtyp wird nicht unterstützt (nur 2D: Hatch, Line, PolyLine, Arc, Circle, Spline, Text)"));
                    continue;
            }

            if (!changed) {
                executionResults (CreateFailedExecutionResult (APIERR_BADPARS, "Für diesen Elementtyp war kein passender Stift-Parameter gesetzt"));
                continue;
            }

            err = ACAPI_Element_Change (&element, &mask, nullptr, 0, true);
            if (err != NoError) {
                executionResults (CreateFailedExecutionResult (err, "ACAPI_Element_Change fehlgeschlagen"));
                continue;
            }

            executionResults (CreateSuccessfulExecutionResult ());
        }
        return NoError;
    });

    return response;
}
