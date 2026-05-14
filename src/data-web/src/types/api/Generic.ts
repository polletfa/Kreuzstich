/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { z } from 'zod';

/**
 * Generic response schema
 */
export const GenericResponseSchema = z.object({
    success: z.boolean()
});
/**
 * Generic response
 */
export type GenericResponse = z.infer<typeof GenericResponseSchema>;
