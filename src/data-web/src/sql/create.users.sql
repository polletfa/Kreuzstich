-- Kreuzstich
-- Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
-- MIT License, see LICENSE file.

CREATE TABLE IF NOT EXISTS users (
       id       SERIAL PRIMARY KEY,
       email    TEXT   NOT NULL UNIQUE CHECK (email <> ''),
       name     TEXT   NOT NULL CHECK (name <> ''),
       password TEXT   NOT NULL CHECK (password <> '')
);
