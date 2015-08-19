# effective

[![Build Status](https://travis-ci.org/evanlucas/effective.svg)](https://travis-ci.org/evanlucas/effective)
[![Coverage Status](https://coveralls.io/repos/evanlucas/effective/badge.svg?branch=master&service=github)](https://coveralls.io/github/evanlucas/effective?branch=master)

polyfill for [get|set]e[uid|gid]

## Install

```bash
$ npm install --save effective
```

## Usage

```js
var effective = require('effective')
effective.geteuid()
// => 501
effective.getegid()
// => 20
effective.seteuid()
// => Throws
effective.seteuid(501)
// => undefined
effective.seteuid('evan')
// => undefined
```

## Author

Evan Lucas

## License

MIT (See `LICENSE` for more info)
