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

Log into the server as root and execute:

```
/srv/install.sh
```
