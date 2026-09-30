/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

/**
 * Check if a threadlist exists (by name - no result rows if the list doesn't exist)
 * @param $1 Threadlist name
 */
SELECT 1 FROM threadlists WHERE name = $1;
