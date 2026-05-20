-- Kreuzstich
-- Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
-- MIT License, see LICENSE file.

CREATE TABLE IF NOT EXISTS threadlists (
       id      SERIAL  PRIMARY KEY,
       user_id INTEGER REFERENCES users,
       name    TEXT    NOT NULL,
       UNIQUE(user_id,name)
);
