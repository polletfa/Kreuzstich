#!/usr/bin/env bash

# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

# Install requirements
apt install -y docker.io certbot

# Create users
id -u server-manager &>/dev/null || useradd -m -d /home/server-manager -G docker -s /sbin/nologin server-manager
id -u github &>/dev/null || useradd -m -d /home/github -G docker -s /bin/bash github

mkdir -p /home/github/.ssh
chmod 700 /home/github/.ssh
[ -f /srv/github_key.pub ] && mv /srv/github_key.pub /home/github/.ssh/authorized_keys
chmod 600 /home/github/.ssh/authorized_keys
chown -R github:github /home/github/.ssh

# Request Let's Encrypt certificate
certbot certonly --webroot -w /etc/letsencrypt/acme-challenge -d kreuzstich.art -d int.kreuzstich.art

# Configure systemd and launch
cp -f /srv/systemd/* /etc/systemd/system
systemctl reenable --now certbot.timer
systemctl enable --now server.service
