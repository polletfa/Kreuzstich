/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

/**
 * Get user
 * @param $1 User email
 */
SELECT * FROM users WHERE email = $1;
