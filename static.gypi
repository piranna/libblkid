{
    "variables":
    {
        "ensure_deps%": "<!(static/ensure_deps.sh)"
    },
    "targets":
    [{
        "include_dirs": ["deps/util-linux/libblkid/src"],
        "includes": ["libblkid.gypi"],
        "dependencies":
        [
            "static/util-linux.gyp:libblkid"
        ]
    }]
}
