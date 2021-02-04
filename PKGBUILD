pkgname=koompi-theme-manager-qt5
pkgver=1.0.1
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
    mkdir -p ${pkgdir}/usr/share/polkit-1/actions
    mkdir -p ${pkgdir}/etc/polkit-1/rules.d
    install -Dm755 ${srcdir}/build/ThemeManager ${pkgdir}/usr/bin/theme-manager
    install -Dm755 ${srcdir}/${pkgname}/theme-manager.desktop ${pkgdir}/usr/share/applications/theme-manager.desktop
    install -Dm755 ${srcdir}/${pkgname}/kmp-dark.sh ${pkgdir}/usr/share/org.koompi.theme.manager/kmp-dark.sh
    install -Dm755 ${srcdir}/${pkgname}/kmp-light.sh ${pkgdir}/usr/share/org.koompi.theme.manager/kmp-light.sh
    install -Dm755 ${srcdir}/${pkgname}/mosx-dark.sh ${pkgdir}/usr/share/org.koompi.theme.manager/mosx-dark.sh
    install -Dm755 ${srcdir}/${pkgname}/mosx-light.sh ${pkgdir}/usr/share/org.koompi.theme.manager/mosx-light.sh
    install -Dm755 ${srcdir}/${pkgname}/winx-dark.sh ${pkgdir}/usr/share/org.koompi.theme.manager/winx-dark.sh
    install -Dm755 ${srcdir}/${pkgname}/winx-light.sh ${pkgdir}/usr/share/org.koompi.theme.manager/winx-light.sh
    cp ${srcdir}/${pkgname}/org.koompi.theme.manager.policy ${pkgdir}/usr/share/polkit-1/actions/
    cp ${srcdir}/${pkgname}/theme-manager-policy.rules ${pkgdir}/etc/polkit-1/rules.d/
}
