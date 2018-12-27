{
    "targets": [{
        "target_name": "node_pulse_simple",
        "sources": [
          "src/addon.cc",
          "src/node_pulse_simple.cc"
        ],
        "include_dirs": [
            "<!(node -e \"require('nan')\")",
            "src"
        ],
        "libraries": ["-lpulse", "-lpulse-simple" ]
    }]
}
