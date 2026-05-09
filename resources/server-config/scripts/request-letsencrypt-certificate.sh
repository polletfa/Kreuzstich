#!/usr/bin/env bash

# Kreuzstich
# Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
# MIT License, see LICENSE file.

#
# Request a certificate for:
# - kreuzstich.art
# - int.kreuzstich.art
#
sudo certbot certonly --webroot -w /etc/letsencrypt/acme-challenge -d kreuzstich.art -d int.kreuzstich.art
