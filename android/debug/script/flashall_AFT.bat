::
:: file create by liunianliang for windows fastboot flash image
::
:: 20170315
::
@echo off
@echo ------------------------
@echo Begin fastboot flashall
@echo ------------------------

@setlocal enabledelayedexpansion

:: get platform
@set platform=8937
@set buildtype=eng
@set input=%1%
@set deviceId=%2%
@set flashtype=%3%

if !input! == 0 (
    @echo Earse Data: No
) else (
    @echo Earse Data: Yes
)

if "!deviceId!" == "" (
    @echo Support All device !
) else (
    @echo Support one device: !deviceId!
)

if "!deviceId!" == "" (
echo platform:8937 2>&1 | findstr platform > %~dp0\platform.txt
@fastboot getvar build-type 2>&1 | findstr build-type > %~dp0\build-type.txt
@fastboot getvar secret-key-opt 2>&1 | findstr secret-key-opt > %~dp0\secret-key-opt.txt
) else (
@fastboot -s !deviceId! getvar platform 2>&1 | findstr platform > %~dp0\platform.txt
@fastboot -s !deviceId! getvar build-type 2>&1 | findstr build-type > %~dp0\build-type.txt
@fastboot -s !deviceId! getvar secret-key-opt 2>&1 | findstr secret-key-opt > %~dp0\secret-key-opt.txt
)

@for /f "tokens=2 delims=: " %%i in (%~dp0\platform.txt) do @(
    set "platform=%%i"
    @echo platform is !platform!

    @for /f "tokens=2 delims=: " %%a in (%~dp0\build-type.txt) do (
        set "buildtype=%%a"
    )

    @for /f "tokens=2 delims=: " %%k in (%~dp0\secret-key-opt.txt) do (
        set "secret_key=%%k"
        set /p =!secret_key!<nul> %~dp0\default_key.bin
    )
    @echo buildtype is !buildtype!
    if !buildtype! == user (
        if "!deviceId!" == "" (
            fastboot flash frp-unlock %~dp0\default_key.bin
            fastboot flashing unlock
            fastboot flashing unlock_critical
        ) else (
            fastboot -s !deviceId! flash frp-unlock %~dp0\default_key.bin
            fastboot -s !deviceId! flashing unlock
            fastboot -s !deviceId! flashing unlock_critical
        )
    )

    :: partition and file name
    call:flash_one_image modem  NON-HLOS.bin !platform!
    call:flash_one_image cmnlib cmnlib.mbn !platform!
    call:flash_one_image cmnlibbak cmnlib.mbn !platform!
    call:flash_one_image cmnlib64 cmnlib64.mbn !platform!
    call:flash_one_image cmnlib64bak cmnlib64.mbn !platform!
    call:flash_one_image keymaster keymaster.mbn !platform!
    call:flash_one_image keymasterbak keymaster.mbn !platform!
    call:flash_one_image aboot emmc_appsboot.mbn !platform!
    call:flash_one_image abootbak emmc_appsboot.mbn !platform!
    call:flash_one_image boot boot.img !platform!
    call:flash_one_image sec sec.dat !platform!
    call:flash_one_image sbl1 sbl1.mbn !platform!
    call:flash_one_image sbl1bak sbl1.mbn !platform!
    call:flash_one_image rpm rpm.mbn !platform!
    call:flash_one_image rpmbak rpm.mbn !platform!
    call:flash_one_image tz tz.mbn !platform!
    call:flash_one_image tzbak tz.mbn !platform!
    call:flash_one_image devcfg devcfg.mbn !platform!
    call:flash_one_image devcfgbak devcfg.mbn !platform!
    call:flash_one_image dsp adspso.bin !platform!
    call:flash_one_image cache cache.img !platform!
    call:flash_one_image mdtp mdtp.img !platform!
    call:flash_one_image APD APD.img !platform!
    call:flash_one_image ADF ADF.img !platform!
    call:flash_one_image splash splash.img !platform!
    if !input! == 0 (
        @echo not earse data partition...
    ) else (
        call:flash_one_image userdata userdata.img !platform!
    )
    call:flash_one_image system system.img !platform!


    if "!deviceId!" == "" (
        if !input! == 0 (
            @echo not do factory reset...
        ) else (
            fastboot oem recovery_and_reboot
        )
    ) else (
        if !input! == 0 (
            @echo not do factory reset...
        ) else (
            fastboot -s !deviceId! oem recovery_and_reboot
        )
    )
)

@echo All is download
goto:eof

:: function for download
:flash_one_image
@echo --------------------------------
@echo begin to flash partition %1
@if exist %~dp0%3_%2 (
    if "!deviceId!" == "" (
        fastboot erase %1
        fastboot flash %1 %~dp0%3_%2
    ) else (
        fastboot -s !deviceId! erase %1
        fastboot -s !deviceId! flash %1 %~dp0%3_%2
    )
) else (
    if exist %~dp0%2 (
        if "!deviceId!" == "" (
            fastboot erase %1
            fastboot flash %1 %~dp0%2
        ) else (
            fastboot -s !deviceId! erase %1
            fastboot -s !deviceId! flash %1 %~dp0%2
        )
    ) else (
        @echo can't flash partion %1
    )
)
@echo done!
@echo --------------------------------
