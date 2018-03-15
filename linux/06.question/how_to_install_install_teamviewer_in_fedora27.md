# install
    sudo rpm -i  teamviewer-13.0.9865-0.x86_64
# 解决依赖
    sudo dnf install qt5-qtwebkit.x86_64  #解决库依赖libQt5WebKitWidgets.so.5()(64bit) >= 5.5
    sudo dnf install qt5-qtx11extras.x86_64 #解决库依赖libQt5X11Extras.so.5()(64bit) >= 5.5
    sudo dnf install qt5-qtquickcontrols.x86_64 #解决库依赖/usr/lib64/qt5/qml/QtQuick/Controls/qmldir
    sudo dnf install qt5-qtgraphicaleffects.x86_64 #解决库依赖/usr/lib64/qt5/qml/QtGraphicalEffects/qmldir
