pkgname=koompi-theme-manager-qt5
pkgver=1.0.0
pkgrel=1
arch=('any')
pkgdesc="Theme Manager for KOOMPI OS with Plasma and Kvantum"
url=https://github.com/koompi/theme-manager-qt5
source=("${pkgname}::git+https://github.com/koompi/theme-manager-qt5.git")
md5sums=('SKIP')

build() {
    mkdir -p ${srcdir}/build
    cd ${srcdir}/build
    cmake ${srcdir}/${pkgname}
    make
}

package() {
    mkdir -p ${pkgdir}/usr/bin
    mkdir -p ${pkgdir}/usr/share/org.koompi.theme.manager
    mkdir -p ${pkgdir}/usr/share/applications
    install -Dm755 ${srcdir}/build/ThemeManager ${pkgdir}/usr/bin/theme-manager
    install -Dm755 ${srcdir}/${pkgname}/update_menu_key.sh ${pkgdir}/usr/share/org.koompi.theme.manager/update_menu_key.sh
    install -Dm755 ${srcdir}/${pkgname}/theme-manager.desktop ${pkgdir}/usr/share/applications/theme-manager.desktop
}
