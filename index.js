'use strict'

var binding = require('bindings')('effective')

exports.geteuid = process.geteuid || binding.geteuid
exports.getegid = process.getegid || binding.getegid
exports.seteuid = process.seteuid || binding.seteuid
exports.setegid = process.setegid || binding.setegid
