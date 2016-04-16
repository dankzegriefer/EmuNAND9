#include "common.h"
#include "draw.h"
#include "fs.h"
#include "menu.h"
#include "i2c.h"
#include "emunand9.h"

#define SUBMENU_START 1


MenuInfo menu[] =
{
    {
        #ifndef BUILD_NAME
        "EmuNAND9 Main Menu", 4,
        #else
        BUILD_NAME, 4,
        #endif
        {
            { "Complete EmuNAND Setup",       &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Complete RedNAND Setup",       &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "SD Format Options...",         &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "EmuNAND Manager Options...",   &InjectNand,            N_EMUNAND | N_DIRECTCOPY }
        }
    },
    {
        "SD Format Options", 4,
        {
            { "Format SD (no EmuNAND)",       &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Format SD (EmuNAND default)",  &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Format SD (EmuNAND minsize)",  &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Format SD (EmuNAND legacy)",   &InjectNand,            N_EMUNAND | N_DIRECTCOPY }
        }
    },
    {
        "EmuNAND Manager Options", 8,
        {
            { "Clone SysNAND to EmuNAND",     &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Clone SysNAND to RedNAND",     &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Restore file to EmuNAND",      &InjectNand,            N_EMUNAND | N_DIRECTCOPY},
            { "Restore file to RedNAND",      &InjectNand,            N_EMUNAND | N_WREDNAND},
            { "Backup SysNAND to file",       &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Backup EmuNAND to file",       &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Convert EmuNAND -> RedNAND",   &InjectNand,            N_EMUNAND | N_DIRECTCOPY },
            { "Convert RedNAND -> EmuNAND",   &InjectNand,            N_EMUNAND | N_DIRECTCOPY }
        }
    },
    {
        NULL, 0, { { 0 } }, // empty menu to signal end
    }
};


void Reboot()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2);
    while(true);
}


void PowerOff()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
    while (true);
}


int main()
{
    ClearScreenFull(true, true);
    InitFS();

    u32 menu_exit = ProcessMenu(menu, SUBMENU_START);
    
    DeinitFS();
    (menu_exit == MENU_EXIT_REBOOT) ? Reboot() : PowerOff();
    return 0;
}
