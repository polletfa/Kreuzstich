# Install the backend server

## Prepare

On your local machine, execute the following steps:

1. Copy the files to the server:

   ```
   scp -r resources/server-config/* root@server:/srv
   ```

2. Create a SSH key pair:
   ```
   ssh-keygen -t ed25519 -f id_ed25519 -N "" -C "github"
   scp id_ed25519.pub root@server:/srv/github_key.pub
   ```

3. On GitHub: Copy the content of the private key (id_ed25519) in the repository secret SSH_PRIVATE_KEY.

4. Delete the key:
   ```
   rm id_ed25519 id_ed25519.pub
   ```

## Install

1. Log into the server

2. Create /srv/services/kreuzstich-int/secrets.env and /srv/services/kreuzstich-prod/secrets.env.
   Use different passwords/tokens for INT and PROD:
   ```
   #
   # For the database container
   #
   POSTGRES_PASSWORD=random-password-for-database

   #
   # For the api container
   #
   KREUZSTICH_DATA_WEB_DB_PASSWORD=random-password-for-database
   KREUZSTICH_DATA_WEB_JWT_SECRET=random-token
   ```

3. Install and launch:
   ```
   /srv/install.sh
   ```
