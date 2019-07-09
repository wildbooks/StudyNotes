DCC_PARSER_PATH=/work1/AOSP_pie_sku6-8_ZC554KL_dev/vendor/qcom/opensource/tools/dcc_parser

shell()
{
    adb shell "echo $1"
}

# Function MSM8996 DCC configuration
enable_dcc_config()
{
    DCC_PATH="/sys/bus/platform/devices/b3000.dcc"

    shell "0 > $DCC_PATH/enable"
    shell "cap > $DCC_PATH/func_type"
    shell "sram > $DCC_PATH/data_sink"
    shell "1 > $DCC_PATH/config_reset"

    #SPM Registers
    shell "0x00448500 8 > $DCC_PATH/config"
    shell "0x0044D070 2 > $DCC_PATH/config"

    shell "1 > $DCC_PATH/enable"
}

capture_dcc_data()
{
    shell "echo  1 > $DCC_PATH/trigger"
    adb pull /dev/dcc_sram sram.bin
}

DCC_data_parser()
{
    if [ ! -f $DCC_PARSER_PATH/dcc_parser.py ]; then
        echo "dcc_parser.py don't exist on this build."
        return
    fi
    python $DCC_PARSER_PATH/dcc_parser.py --sram-file sram.bin  --out-dir dcc -f  dcc_captured_data.xml
}


enable_dcc_config
capture_dcc_data
DCC_data_parser
