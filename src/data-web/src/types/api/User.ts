/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { z } from 'zod';

import type { GenericResponse } from '@api/Generic';
import { GenericResponseSchema } from '@api/Generic';

export const UserSchema = z.object({
    id: z.number(),
    email: z.string(),
    name: z.string()
});
export type User = z.infer<typeof UserSchema>;

// ------------------------------------------------------------------------- GET /user/status

export const GetUserStatusResponseSchema = UserSchema.optional();
export type GetUserStatusResponse = z.infer<typeof GetUserStatusResponseSchema>;

// ------------------------------------------------------------------------- POST /user/login

export const PostUserLoginRequestSchema = z.object({
    email: z.string(),
    password: z.string(),
    persist: z.boolean()
});
export type PostUserLoginRequest = z.infer<typeof PostUserLoginRequestSchema>;

export const PostUserLoginResponseSchema = GetUserStatusResponseSchema;
export type PostUserLoginResponse = GetUserStatusResponse;

// ------------------------------------------------------------------------- GET /user/logout

export const GetUserLogoutResponseSchema = GenericResponseSchema;
export type GetUserLogoutResponse = GenericResponse;
