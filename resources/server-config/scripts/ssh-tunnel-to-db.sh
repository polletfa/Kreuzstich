#!/usr/bin/env bash

# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Use this script to open a SSH tunnel to the database container
# for testing/debugging purposes.
#
# ./ssh-tunnel-to-db.sh user@server [int|prod] [port]
# ./ssh-tunnel-to-db.sh ssh://user@server:port [int|prod] [port]
#
#     [int|prod]  Select which container to connect to.
#                 Default: int
#     [port]      Port to use on localhost to tunnel through
#                 Default: 5432
#
# You can then connect to the database through localhost:port
# Shut down the script to close the tunnel.

connection_string="$1"
environment="${2:-int}"
port="${3:-5432}"

if [ "$connection_string" = "" ]; then
    echo "You must specify the connection string." >&2
    exit 1
fi

container_ip="$(ssh "$connection_string" 'docker inspect --format "{{range .NetworkSettings.Networks}}{{.IPAddress}}{{end}}" kreuzstich-'"$environment"'-database' 2>/dev/null)"

if [ "$container_ip" = "" ]; then
    echo "Unable to get the IP of the container." >&2
    exit 1
fi

ssh -T -L "$port":"$container_ip":5432 "$connection_string" '
echo "You can now connect to kreuzstich-'"$environment"'-database with:"
echo -e "\033[33;1m     PGPASSWORD=kreuzstich psql -h localhost -p '"$port"' -U kreuzstich -d kreuzstich\033[0m"
echo "Terminate this session (CTRL+C) to close the connection."
sleep infinity'
