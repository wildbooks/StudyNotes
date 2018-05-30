#/usr/bin/bash
username=n009646

function ProjectToPath() {
    case "$1" in
        sku1-ZC600KL-dev)
            name="sku1"
            ;;
        sku2-4-ZD553KL-dev)
            name="sku2-4"
            ;;
        sku5-ZC553KL-dev)
            name="sku5"
            ;;
        sku6-8-ZC554KL-dev)
            name="sku6-8"
            ;;
        sku9-12-ZC520KL-dev)
            name="sku9-12"
            ;;
        *)
            echo "$1 Didn't match anything"
    esac
    echo $name
}

function RepoSync() {

    Project=$1
    PathName=$(ProjectToPath $Project)
    if [ ! -d $PathName ]; then
        mkdir $PathName
        cd $PathName
        repo init -u ssh://$username@gerritnj01.archermind.com:29418/msm8940/platform/manifest -b $Project
        echo "repo init -u ssh://$username@gerritnj01.archermind.com:29418/msm8940/platform/manifest -b $Project"
        cd -
    fi
    cd $PathName
    #repo forall -c "git clean -df && git reset --hard" 2>&1 > /dev/null
    repo sync -c --no-tags -j20
    source build/envsetup.sh
    lunch msm8937_64-userdebug
    make 2>&1 > ${PathName}_build_log
    cd -
}

RepoSync  sku1-ZC600KL-dev
echo "sku1 return $?"
RepoSync  sku2-4-ZD553KL-dev
echo "sku2 return $?"
RepoSync  sku5-ZC553KL-dev
echo "sku3 return $?"
RepoSync  sku6-8-ZC554KL-dev
echo "sku4 return $?"
RepoSync  sku9-12-ZC520KL-dev
echo "sku5 return $?"
