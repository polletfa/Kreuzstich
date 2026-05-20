/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import * as z from 'zod/v4';


/**
 * Schema for users table row
 */
export const UserSchema = z.object({
    id: z.number(),
    email: z.string(),
    name: z.string(),
    password: z.string()
});
export type User = z.infer<typeof UserSchema>;

/**
 * Schema for threads table row
 */
export const ThreadSchema = z.object({
    id: z.number(),
    list_id: z.number(),
    name: z.string(),
    color: z.string()
});
export type Thread = z.infer<typeof ThreadSchema>;

/**
 * Schema for threadlists table row
 */
export const ThreadListSchema = z.object({
    id: z.number(),
    user_id: z.number().nullable(),
    name: z.string()
});
export type ThreadList = z.infer<typeof ThreadListSchema>;

/**
 * Schema for threadlists table row with actual list of threads.
 * @see getThreadLists.sql
 */
export const ThreadListFullSchema = ThreadListSchema.extend({
    threads: z.array(ThreadSchema)
});
export type ThreadListFull = z.infer<typeof ThreadListFullSchema>;
