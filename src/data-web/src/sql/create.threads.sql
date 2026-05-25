-- Kreuzstich
-- Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
-- MIT License, see LICENSE file.

CREATE TABLE IF NOT EXISTS threads (
       id      SERIAL  PRIMARY KEY,
       list_id INTEGER NOT NULL REFERENCES threadlists,
       name    TEXT    NOT NULL,
       color   CHAR(6) NOT NULL CHECK (color ~ '^[0-9a-fA-F]{6}$'),
       UNIQUE(list_id,name)
);
