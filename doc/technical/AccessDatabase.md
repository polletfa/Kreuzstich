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
Database and username are `kreuzstich`. The password is defined in the secrets.env file
on the server.

```
PGPASSWORD=database-password psql -h localhost -p 5432 -U kreuzstich -d kreuzstich
```
