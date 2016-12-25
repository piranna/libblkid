{
    "targets": [{
        "target_name": "libblkid",
#        "dependencies": [
#            "static/util-linux.gyp:libblkid"
#        ],
        "include_dirs": [
            "<!(node -e \"require('nan')\")"
        ],
        "libraries": [
            "-lblkid"
        ],
        "sources": [
            "libblkid.cc"
        ]
    }]
}
