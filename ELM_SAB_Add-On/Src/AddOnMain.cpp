// ELM_SAB_Add-On — SAB-eigene JSON-Befehle für Archicad.
// Registriert Add-On-Commands im Namespace "ELM_SAB", erreichbar über die
// JSON-API (ExecuteAddOnCommand) und damit über den tapir-archicad-mcp-Server.
#include "APIEnvir.h"
#include "ACAPinc.h"

#include "ResourceIds.hpp"

#include "ELMCommandBase.hpp"
#include "SetPenOfElementsCommand.hpp"
#include "GetPenOfElementsCommand.hpp"

static const GSResID AddOnInfoID          = ID_ADDON_INFO;
    static const Int32 AddOnNameID        = 1;
    static const Int32 AddOnDescriptionID = 2;

// ---------------------------------------------------------------------------
// Command-Registrierung
// ---------------------------------------------------------------------------

template <typename CommandType>
static GSErrCode RegisterJsonCommand ()
{
    GS::Owner<CommandType> command (new CommandType ());
    return ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler (command.Pass ());
}

// ---------------------------------------------------------------------------
// Add-On-Lifecycle
// ---------------------------------------------------------------------------

API_AddonType CheckEnvironment (API_EnvirParams* envir)
{
    RSGetIndString (&envir->addOnInfo.name, AddOnInfoID, AddOnNameID, ACAPI_GetOwnResModule ());
    RSGetIndString (&envir->addOnInfo.description, AddOnInfoID, AddOnDescriptionID, ACAPI_GetOwnResModule ());

    return APIAddon_Preload;
}

GSErrCode RegisterInterface (void)
{
    return NoError;
}

GSErrCode Initialize (void)
{
    GSErrCode err = NoError;

    err |= RegisterJsonCommand<SetPenOfElementsCommand> ();
    err |= RegisterJsonCommand<GetPenOfElementsCommand> ();

    return err;
}

GSErrCode FreeData (void)
{
    return NoError;
}
