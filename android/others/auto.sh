# android自动编译脚步
repo sync
repo start master --all
repo forall -c 'git checkout MSM8909_KAIOS_GFLIP2_DEV'
cd amss_8909/
./linux_build.sh -a gflip2 ATT
cd ../
source build/envsetup.sh 
choosecombo 1 gflip2 eng false ATT
make -j8
