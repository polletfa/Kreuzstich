# Run the website locally

To run the website locally, you need:
* A database
* The backend `data-web`
* The frontend `gui-web`

## Build

You first need to build all required components:

```bash
./make debug build-web
```

## Database

You can either use a local PostgreSQL database or use the database from the server by creating a SSH tunnel to it, as explained [here](AccessDatabase.md).

## Backend

### Configure

You must first configure the backend by creating the file `src/data-web/.env` with the following content:

```
KREUZSTICH_DATA_WEB_PORT=8080

# For the remote database through a SSH tunnel:
KREUZSTICH_DATA_WEB_DB_HOST=localhost
KREUZSTICH_DATA_WEB_DB_DB=kreuzstich
KREUZSTICH_DATA_WEB_DB_PORT=5432
KREUZSTICH_DATA_WEB_DB_USER=kreuzstich

# Set the correct password
KREUZSTICH_DATA_WEB_DB_PASSWORD=

# Set a random JWT key
KREUZSTICH_DATA_WEB_JWT_SECRET=
```

You can find the password for the remote database on the server in the file `/srv/services/kreuzstich-int/secrets.env`.

For the JWT key, you can generate a value with:

```bash
openssl rand -hex 64
```

### Run

```bash
cd src/data-web
npm run start
```

## Frontend

```bash
cd src/gui-web
npm run start
```
