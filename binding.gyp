{
  "targets": [{
    "target_name": "effective",
    "include_dirs": [
      "<!(node -e \"require('nan')\")"
    ],
    "sources": [
      "src/effective.cc"
    ]
  }]
}
