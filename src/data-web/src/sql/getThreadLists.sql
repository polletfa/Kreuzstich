/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

/**
 * Get full data for all threadlists
 *
 * @tparam user If 'true', add selection for user_id=$1
 * @param $1 user_id (if user == 'true')
 */
SELECT tl.*, COALESCE(JSON_AGG(t.*) FILTER (WHERE t.id IS NOT NULL), '[]'::json) AS threads
FROM threadlists tl
LEFT JOIN threads t ON t.list_id = tl.id
WHERE tl.user_id IS NULL @with(user) { OR user_id = $1 }
GROUP BY tl.id
;
