#!/usr/bin/env node

const strictEqual = require('assert').strictEqual

const libblkid = require('.')


const UUID = '4aef932b-ab17-471f-8e80-4901d96495d9'
const DEV = '/dev/sda2'


strictEqual(libblkid.evaluate_tag(), null)
strictEqual(libblkid.evaluate_tag(null), null)
strictEqual(libblkid.evaluate_tag(undefined), null)
strictEqual(libblkid.evaluate_spec(), null)
strictEqual(libblkid.evaluate_spec(null), null)
strictEqual(libblkid.evaluate_spec(undefined), null)

strictEqual(libblkid.evaluate_tag('UUID', UUID), DEV)
strictEqual(libblkid.evaluate_tag('UUID='+UUID), DEV)

strictEqual(libblkid.evaluate_spec('UUID='+UUID), DEV)
strictEqual(libblkid.evaluate_spec(DEV), DEV)
