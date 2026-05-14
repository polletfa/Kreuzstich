/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import { z } from 'zod';

import type { GenericResponse } from '@datatypes/api/Generic';
import { GenericResponseSchema } from '@datatypes/api/Generic';
import * as db from '@datatypes/db';

export const UserSchema = db.UserSchema.omit({password: true});
export type User = z.infer<typeof UserSchema>;

// ------------------------------------------------------------------------- GET /user/status

export const GetUserStatusResponseSchema = UserSchema.optional();
export type GetUserStatusResponse = z.infer<typeof GetUserStatusResponseSchema>;

// ------------------------------------------------------------------------- POST /user/login

export const PostUserLoginRequestSchema = db.UserSchema
    .pick({email: true, password: true})
    .extend({persist: z.boolean()});
export type PostUserLoginRequest = z.infer<typeof PostUserLoginRequestSchema>;

export const PostUserLoginResponseSchema = GetUserStatusResponseSchema;
export type PostUserLoginResponse = GetUserStatusResponse;

// ------------------------------------------------------------------------- GET /user/logout

export const GetUserLogoutResponseSchema = GenericResponseSchema;
export type GetUserLogoutResponse = GenericResponse;
