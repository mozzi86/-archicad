// ELM_SAB_Add-On — SAB-eigene JSON-Befehle für Archicad.
// Registriert Add-On-Commands im Namespace "ELM_SAB" (JSON-API / MCP) und
// einen Menüpunkt "ELM_SAB Status" zur Sichtbarkeit + Diagnose.
#include "APIEnvir.h"
#include "ACAPinc.h"

#include "ResourceIds.hpp"

#include "ELMCommandBase.hpp"
#include "SetPenOfElementsCommand.hpp"
#include "GetPenOfElementsCommand.hpp"
#include "CreatePolygonWallsCommand.hpp"
#include "Get2DGeometryCommand.hpp"

#include <cstdio>

static const GSResID AddOnInfoID          = ID_ADDON_INFO;
    static const Int32 AddOnNameID        = 1;
    static const Int32 AddOnDescriptionID = 2;

// ---------------------------------------------------------------------------
// Diagnose-Log (bewusst simpel: /tmp, append)
// ---------------------------------------------------------------------------

static void ELMLog (const char* fmt, long v = 0)
{
    std::FILE* f = std::fopen ("/tmp/ELM_SAB_AddOn.log", "a");
    if (f != nullptr) {
        std::fprintf (f, fmt, v);
        std::fprintf (f, "\n");
        std::fclose (f);
    }
}

// ---------------------------------------------------------------------------
// Command-Registrierung
// ---------------------------------------------------------------------------

template <typename CommandType>
static GSErrCode RegisterJsonCommand (const char* name)
{
    GS::Owner<CommandType> command (new CommandType ());
    GSErrCode err = ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler (command.Pass ());
    ELMLog (name, 0);
    ELMLog ("  InstallAddOnCommandHandler err=%ld", (long) err);
    return err;
}

// ---------------------------------------------------------------------------
// Menü
// ---------------------------------------------------------------------------

static GSErrCode MenuCommandHandler (const API_MenuParams* menuParams)
{
    if (menuParams->menuItemRef.menuResID == ID_ADDON_MENU) {
        ACAPI_WriteReport ("ELM_SAB_Add-On v0.1.0 aktiv.\nBefehle: ELM_SAB.GetPenOfElements, ELM_SAB.SetPenOfElements\nLog: /tmp/ELM_SAB_AddOn.log", true);
    }
    return NoError;
}

// ---------------------------------------------------------------------------
// Add-On-Lifecycle
// ---------------------------------------------------------------------------

API_AddonType CheckEnvironment (API_EnvirParams* envir)
{
    ELMLog ("CheckEnvironment aufgerufen");
    RSGetIndString (&envir->addOnInfo.name, AddOnInfoID, AddOnNameID, ACAPI_GetOwnResModule ());
    RSGetIndString (&envir->addOnInfo.description, AddOnInfoID, AddOnDescriptionID, ACAPI_GetOwnResModule ());

    return APIAddon_Preload;
}

GSErrCode RegisterInterface (void)
{
    GSErrCode err = ACAPI_MenuItem_RegisterMenu (ID_ADDON_MENU, 0, MenuCode_Tools, MenuFlag_Default);
    ELMLog ("RegisterInterface err=%ld", (long) err);
    return err;
}

GSErrCode Initialize (void)
{
    ELMLog ("Initialize aufgerufen");
    GSErrCode err = NoError;

    err |= ACAPI_MenuItem_InstallMenuHandler (ID_ADDON_MENU, MenuCommandHandler);
    ELMLog ("MenuHandler err=%ld", (long) err);

    err |= RegisterJsonCommand<SetPenOfElementsCommand> ("Registriere SetPenOfElements");
    err |= RegisterJsonCommand<GetPenOfElementsCommand> ("Registriere GetPenOfElements");
    err |= RegisterJsonCommand<CreatePolygonWallsCommand> ("Registriere CreatePolygonWalls");
    err |= RegisterJsonCommand<Get2DGeometryCommand> ("Registriere Get2DGeometryOfElements");

    ELMLog ("Initialize fertig err=%ld", (long) err);
    return err;
}

GSErrCode FreeData (void)
{
    return NoError;
}
