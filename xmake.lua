-- set xmake version
set_xmakever("2.9.4")

-- include local folders
includes("lib/commonlibf4")

-- set project
set_project("BakaPowerArmorStorage")
set_version("2.0.0")
set_license("GPL-3.0")

-- set defaults
set_arch("x64")
set_languages("c++23")
set_optimize("faster")
set_warnings("allextra", "error")
set_defaultmode("releasedbg")

-- enable lto
set_policy("build.optimization.lto", true)

-- add rules
add_rules("mode.debug", "mode.releasedbg")
add_rules("plugin.vsxmake.autoupdate")

-- add config
set_config("rex_ini", true)
set_config("rex_json", true)

-- setup targets
target("BakaPowerArmorStorage")
    -- bind local dependencies
    add_deps("commonlibf4")

    -- add commonlibf4 plugin
    add_rules("commonlibf4.plugin", {
        name = "BakaPowerArmorStorage",
        author = "shad0wshayd3"
    })

    -- add source files
    add_files("src/**.cpp")
    add_headerfiles("src/**.h")
    add_includedirs("src")
    set_pcxxheader("src/PCH.h")

    -- add extra files
    add_extrafiles(".clang-format")
