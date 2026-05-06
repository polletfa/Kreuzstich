#!/usr/bin/env bash

#
# Request a certificate for:
# - kreuzstich.art
# - int.kreuzstich.art
#
sudo certbot certonly --webroot -w /etc/letsencrypt/acme-challenge -d kreuzstich.art -d int.kreuzstich.art
