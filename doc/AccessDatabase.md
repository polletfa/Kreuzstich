# Access the database

The database runs in a docker container that is not exposed to the outside.
To access the database, you need to create a SSH tunnel to the container.
To that extent, use the script `tools/ssh-tunnel-to-db.sh`:

```
./tools/ssh-tunnel-to-db.sh user@server [int|prod] [port]
./tools/ssh-tunnel-to-db.sh ssh://user@server:port [int|prod] [port]
```

- `int` or `prod`: Select which container to connect to. Default: `int`.
- port: Port to use on localhost to tunnel through. Default: 5432.

You can then connect to the database at `localhost:port`.
Database, username and password are `kreuzstich`.

```
PGPASSWORD=kreuzstich psql -h localhost -p 5432 -U kreuzstich -d kreuzstich
```

Note: We don't treat the database credentials as critical because the database
      is not accessible from the internet and requires SSH access to the server.
