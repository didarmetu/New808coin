[Unit]
Description=New808coin's distributed currency daemon
After=network.target

[Service]
User=new808coin
Group=new808coin

Type=forking
PIDFile=/var/lib/new808coind/new808coind.pid

ExecStart=/usr/bin/new808coind -daemon -pid=/var/lib/new808coind/new808coind.pid \
          -conf=/etc/new808coin/new808coin.conf -datadir=/var/lib/new808coind

ExecStop=-/usr/bin/new808coin-cli -conf=/etc/new808coin/new808coin.conf \
         -datadir=/var/lib/new808coind stop

Restart=always
PrivateTmp=true
TimeoutStopSec=60s
TimeoutStartSec=2s
StartLimitInterval=120s
StartLimitBurst=5

[Install]
WantedBy=multi-user.target
