/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { z } from 'zod';

export const UserSchema = z.object({
    id: z.number(),
    email: z.string(),
    name: z.string(),
    password: z.string()
});
export type User = z.infer<typeof UserSchema>;

export const ThreadSchema = z.object({
    id: z.number(),
    list_id: z.number(),
    name: z.string(),
    color: z.string()
});
export type Thread = z.infer<typeof ThreadSchema>;

export const ThreadListSchema = z.object({
    id: z.number(),
    user_id: z.number().nullable(),
    name: z.string()
});
export type ThreadList = z.infer<typeof ThreadListSchema>;
