#!/usr/bin/env node

const libblkid = require('.')


console.log(libblkid.evaluate_tag('UUID', '4aef932b-ab17-471f-8e80-4901d96495d9'))
console.log(libblkid.evaluate_tag('UUID=4aef932b-ab17-471f-8e80-4901d96495d9'))

console.log(libblkid.evaluate_spec('UUID=4aef932b-ab17-471f-8e80-4901d96495d9'))
console.log(libblkid.evaluate_spec('/dev/sda2'))
