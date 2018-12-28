{
    "targets": [{
        "target_name": "node_pulse_simple",
        "sources": [
          "src/addon.cc",
          "src/pulse_simple.cc",
          "src/connection.cc"
        ],
        "include_dirs": [
            "<!(node -e \"require('nan')\")",
            "src"
        ],
        "libraries": ["-lpulse", "-lpulse-simple" ]
    }]
}
