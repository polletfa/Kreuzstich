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

You can either use a local PostgreSQL database or use the database from the server by creating an SSH tunnel to it, as explained in [Access the database](AccessDatabase.md).

For local development, configure the database connection with:

- Host: `localhost`
- Port: `5432`
- Database: `kreuzstich`
- User: `kreuzstich`

## Backend

### Configure

Create the file `src/data-web/.env` with the following content:

```bash
KREUZSTICH_DATA_WEB_PORT=8080

# For the remote database through a SSH tunnel:
KREUZSTICH_DATA_WEB_DB_HOST=localhost
KREUZSTICH_DATA_WEB_DB_DB=kreuzstich
KREUZSTICH_DATA_WEB_DB_PORT=5432
KREUZSTICH_DATA_WEB_DB_USER=kreuzstich

# Set the correct password
KREUZSTICH_DATA_WEB_DB_PASSWORD=

# Set a random JWT secret
KREUZSTICH_DATA_WEB_JWT_SECRET=
```

You can find the password for the remote database on the server in the file `/srv/services/kreuzstich-int/secrets.env`.

For the JWT secret, generate a random hexadecimal value with:

```bash
openssl rand -hex 64
```

Use the generated value for `KREUZSTICH_DATA_WEB_JWT_SECRET`.

### Run

```bash
cd src/data-web
npm run start
```

The backend listens on port `8080`, as configured by `KREUZSTICH_DATA_WEB_PORT`.

## Frontend

```bash
cd src/gui-web
npm run start
```

The Angular development server proxies `/api` requests to `http://localhost:8080`, as configured in [`src/gui-web/proxy.conf.json`](https://github.com/polletfa/Kreuzstich/blob/feature/wasm/src/gui-web/proxy.conf.json).

After both services are running, open the website at:

```text
http://localhost:4200
```

If you change `KREUZSTICH_DATA_WEB_PORT`, update `src/gui-web/proxy.conf.json` accordingly.
