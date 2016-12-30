{
    'variables':
    {
        'has_libblkid%': '<!(static/has_lib.sh blkid)'
    },
    'conditions':
    [
        ['has_libblkid=="true"', {
            'includes': ['shared.gypi']
        }, {
            'includes': ['static.gypi']
        }]
    ]
}
