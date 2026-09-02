# 本地构建入口

本目录同时保存可提交的 Windows 构建脚本和被忽略的构建产物。

## 编译

在项目根目录执行：

```bat
build\build.bat
build\build.bat baremetal-release
build\build.bat rtt-debug
build\build.bat freertos-debug
build\build.bat all
```

不传参数时默认编译 `baremetal-debug`。固件位于
`build\out\<preset>\`。

## 清除

```bat
build\clean.bat
build\clean.bat baremetal-debug
```

不传参数时清除 `build\out\` 中的全部编译产物。清除脚本不会删除本目录中的
脚本，也不会删除 `build\generated\autoconf.h`。

## 可用预设

- `baremetal-debug`
- `baremetal-release`
- `rtt-debug`
- `freertos-debug`
- `all`（仅脚本参数）
