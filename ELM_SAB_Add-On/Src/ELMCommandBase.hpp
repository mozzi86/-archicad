// ELM_SAB_Add-On — schlanke Basis für JSON-Commands.
// Muster übernommen von Tapir (github.com/ENZYME-APD/tapir-archicad-automation, MIT).
#pragma once

#include "APIEnvir.h"
#include "ACAPinc.h"

#include "ObjectState.hpp"

class ELMCommandBase : public API_AddOnCommand
{
public:
    ELMCommandBase () = default;

    virtual GS::String GetNamespace () const override final
    {
        return "ELM_SAB";
    }

    virtual API_AddOnCommandExecutionPolicy GetExecutionPolicy () const override final
    {
        return API_AddOnCommandExecutionPolicy::ScheduleForExecutionOnMainThread;
    }

    virtual void OnResponseValidationFailed (const GS::ObjectState& /*response*/) const override final
    {
    }

#ifdef ServerMainVers_2600
    virtual bool IsProcessWindowVisible () const override final
    {
        return false;
    }
#endif

    virtual GS::Optional<GS::UniString> GetSchemaDefinitions () const override
    {
        return GS::NoValue;
    }

    virtual GS::Optional<GS::UniString> GetInputParametersSchema () const override
    {
        return GS::NoValue;
    }

    virtual GS::Optional<GS::UniString> GetResponseSchema () const override
    {
        return GS::NoValue;
    }
};

// Kleine Helfer (Tapir-kompatible Response-Formate)
GS::ObjectState CreateErrorResponse (GSErrCode errorCode, const GS::UniString& errorMessage);
GS::ObjectState CreateFailedExecutionResult (GSErrCode errorCode, const GS::UniString& errorMessage);
GS::ObjectState CreateSuccessfulExecutionResult ();
API_Guid        GetGuidFromObjectState (const GS::ObjectState& os);
