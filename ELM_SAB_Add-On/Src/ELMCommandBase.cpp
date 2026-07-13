#include "ELMCommandBase.hpp"

GS::ObjectState CreateErrorResponse (GSErrCode errorCode, const GS::UniString& errorMessage)
{
    GS::ObjectState error;
    error.Add ("code", errorCode);
    error.Add ("message", errorMessage.ToCStr ().Get ());
    return GS::ObjectState ("error", error);
}

GS::ObjectState CreateFailedExecutionResult (GSErrCode errorCode, const GS::UniString& errorMessage)
{
    GS::ObjectState result;
    result.Add ("success", false);
    result.Add ("error", CreateErrorResponse (errorCode, errorMessage));
    return result;
}

GS::ObjectState CreateSuccessfulExecutionResult ()
{
    GS::ObjectState result;
    result.Add ("success", true);
    return result;
}

API_Guid GetGuidFromObjectState (const GS::ObjectState& os)
{
    GS::String guidStr;
    if (!os.Get ("guid", guidStr)) {
        return APINULLGuid;
    }
    return APIGuidFromString (guidStr.ToCStr ());
}
