-- Kreuzstich
-- Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
-- MIT License, see LICENSE file.

CREATE TABLE IF NOT EXISTS users (
       id    SERIAL PRIMARY KEY,
       name  TEXT   NOT NULL UNIQUE CHECK (id = 1 OR name <> ''),
       email TEXT   NOT NULL UNIQUE CHECK (id = 1 OR email <> '')
);
INSERT INTO users(name, email) SELECT '', '' WHERE NOT EXISTS (SELECT 1 FROM users); -- system user
