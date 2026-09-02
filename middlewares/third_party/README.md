# 三方开源库管理规范

本目录用于接入第三方开源库（如 cJSON、EasyLogger、SEGGER RTT、Letter Shell、LittlevGL 等）。

## 接入步骤
1. 将三方库源码目录放置在本文件夹下（例如 `third_party/cJSON/`）。
2. 在 `cmake/stm32f103_options.cmake` 中增加对应的开关选项（例如 `option(ENABLE_CJSON "Enable cJSON" OFF)`）。
3. 在 `middlewares/third_party/CMakeLists.txt` 中配置对应的条件编译和头文件包含：
   ```cmake
   if(ENABLE_CJSON)
       target_include_directories(third_party_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/cJSON)
       list(APPEND THIRD_PARTY_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/cJSON/cJSON.c)
   endif()
   ```
4. 编译时通过 `-DENABLE_CJSON=ON` 或在 `CMakePresets.json` 中按需开启。
