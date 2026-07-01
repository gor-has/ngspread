{
    "daemon": {
        "name": "localhost",
        "runtime_dir": "/tmp",
        "pid_file": "/var/run/ngspread.pid"
    },

    "segments": [
        {
            "address": "127.0.0.255",
            "port": 4803,
            "nodes": [
                {
                    "name": "localhost",
                    "address": "127.0.0.1"
                }
            ]
        }
    ],

    "logging": {
        "level": "info",
        "file": "spread.log"
    }
}
