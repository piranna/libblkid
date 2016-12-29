{
    'variables':
    {
        'has_libblkid%': '<!(static/has_lib.sh blkid)'
    },
    'conditions':
    [
        ['has_libblkid=="true"', {
            'includes': ['shared.gyp']
        }, {
            'includes': ['static.gyp']
        }]
    ]
}
