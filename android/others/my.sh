# repo forall -c "git clean -df" && repo forall -c "git checkout ." && repo sync -j8 && source build/envsetup.sh &&choosecombo 1 1 2 2 2 2 && make -j8>make_all.log&
repo forall -c "git clean -df" && repo forall -c "git checkout ." && repo sync -j4 | tee sync.log
