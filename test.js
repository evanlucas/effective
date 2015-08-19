'use strict'

var test = require('tap').test
var effective = require('./')

test('geteuid', function(t) {
  t.type(effective.geteuid, 'function')
  t.end()
})

test('getegid', function(t) {
  t.type(effective.getegid, 'function')
  t.end()
})

test('seteuid', function(t) {
  t.type(effective.seteuid, 'function')
  t.throws(function() {
    effective.seteuid('root')
  }, /EPERM/)
  t.end()
})

test('setegid', function(t) {
  t.type(effective.setegid, 'function')
  t.throws(function() {
    effective.setegid('wheel')
  }, /EPERM/)
  t.end()
})
