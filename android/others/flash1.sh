#需要*.mbn
#需要*.img
#需要*.elf
#需要*.bin
#需要*.dat
#需要*.tar
#find . -type f -name "*.mbn" -exec cp {} tmep  \;
#find . -type f -name "*.img" -exec cp {} tmep  \;
#find . -type f -name "*.elf" -exec cp {} tmep  \;
#find . -type f -name "*.bin" -exec cp {} tmep  \;
#find . -type f -name "*.dat" -exec cp {} tmep  \;
#find . -type f -name "*.tar" -exec cp {} tmep  \;


find . -type f -name "*.mbn" -o -name "*.img"-o -name "*.elf"-o -name "*.bin" -o -name "*.dat" -o -name "*.tar" -exec cp {} tmep  \; 
OUT=install
IN=./tmep
VersionCode=111
VersionBCode=555
VersionZZCode=333
svnnumber=222
verprefix=444
echo "cp ${IN}/cmnlib.mbn ${OUT}/A${VersionCode}.mbn"
cp ${IN}/cmnlib.mbn ${OUT}/A${VersionCode}.mbn #A
cp ${IN}/boot.img ${OUT}/B${VersionBCode}.mbn  #B

# cp sbl1.mbn ${OUT}/C${VersionCode}.mbn

cp ${IN}/xbl.elf ${OUT}/C${VersionBCode}.mbn #C

cp ${IN}/hyp.mbn ${OUT}/D${VersionCode}.mbn #D

#cp ${IN}/splash.img ${OUT}/E${VersionCode}.mbn

#cp ${IN}/tctpersist.img ${OUT}/F${VersionCode}.mbn

#cp ${IN}/vpersist.img ${OUT}/F${VersionCode}.mbn

cp ${IN}/gpt_backup0.bin ${OUT}/G${VersionCode}.mbn #G0

#cp ${IN}/hdcp.img ${OUT}/H${VersionCode}.mbn

# cp ${IN}/cache.img ${OUT}/I${VersionCode}.mbn

cp ${IN}/persist.img ${OUT}/J${VersionCode}.mbn #J

cp ${IN}/sec.dat ${OUT}/K${VersionCode}.mbn   #K

# cp ${IN}/emmc_appsboot.mbn ${OUT}/L${VersionCode}.mbn

cp ${IN}/abl.elf ${OUT}/L${VersionCode}.mbn #L

cp ${IN}/mdtp.img ${OUT}/M${VersionCode}.mbn   #M

cp ${IN}/NON-HLOS.bin ${OUT}/N${VersionCode}.mbn #N

cp ${IN}/gpt_main0.bin ${OUT}/O${VersionCode}.mbn #O0

cp ${IN}/rawprogram0.xml ${OUT}/P${VersionCode}.mbn #P

cp ${IN}/keymaster.mbn ${OUT}/Q${VersionCode}.mbn #Q

# cp ${IN}/recovery.img ${OUT}/R${VersionCode}.mbn

cp ${IN}/study.tar ${OUT}/S${VersionCode}.mbn     #S

cp ${IN}/tz.mbn ${OUT}/T${VersionCode}.mbn #T

cp ${IN}/userdata.img ${OUT}/U${VersionCode}.mbn #U

# cp ${IN}/adspso.bin ${OUT}/V${verprefix}0${svnnumber}.mbn

cp ${IN}/dspso.bin ${OUT}/V${verprefix}0${svnnumber}.mbn #V0

cp ${IN}/BTFM.bin ${OUT}/V${verprefix}1${svnnumber}.mbn #V1

cp ${IN}/cmnlib64.mbn ${OUT}/V${verprefix}2${svnnumber}.mbn #V2

cp ${IN}/devcfg.mbn ${OUT}/V${verprefix}3${svnnumber}.mbn  #V3

cp ${IN}/pmic.elf ${OUT}/V${verprefix}4${svnnumber}.mbn #V4

# cp ${IN}/devinfo.img ${OUT}/V${verprefix}5${svnnumber}.mbn

# cp ${IN}/lksecapp.mbn ${OUT}/V${verprefix}9${svnnumber}.mbn

# cp ${IN}/oempersist.img ${OUT}/V${verprefix}A${svnnumber}.mbn

cp ${IN}/mdtpsecapp.mbn ${OUT}/V${verprefix}B${svnnumber}.mbn #VB

cp ${IN}/storsec.mbn ${OUT}/V${verprefix}C${svnnumber}.mbn #VC

cp ${IN}/rpm.mbn ${OUT}/W${VersionCode}.mbn #W

# cp ${IN}/simlock.img ${OUT}/X${VersionCode}.mbn

cp ${IN}/system.img ${OUT}/Y${VersionZZCode}.mbn #Y

cp ${IN}/patch0.xml ${OUT}/Z${VersionCode}.mbn  #Z

# cp ${IN}/oem.img ${OUT}/V${verprefix}8${svnnumber}.mbn

cp ${IN}/vendor.img ${OUT}/V${verprefix}D${svnnumber}.mbn #VD
