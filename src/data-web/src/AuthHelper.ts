/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type { FastifyReply, FastifyRequest } from 'fastify';

import { UserSchema } from '@api/User';

export class AuthHelper {
    /**
     * Authenticate and reject (HTTP 401) if the user is not authenticated. Use with onRequest hook.
     */
    public static async authenticate(request: FastifyRequest, response: FastifyReply): Promise<void> {
        try {
            await AuthHelper.decodeJwt(request);
        } catch (err) {
            response.code(401).send({ error: 'Unauthorized' });
        }
    }

    /**
     * Authenticate but don't reject
     */
    public static async authenticateNoFail(request: FastifyRequest): Promise<void> {
        try {
            await AuthHelper.decodeJwt(request);
        } catch {
        }
    }

    private static async decodeJwt(request: FastifyRequest): Promise<void> {
        await request.jwtVerify();
        const res = UserSchema.safeParse(request.user);
        if(!res.success) {
            console.error('Invalid JWT token', res.error);
            (request as any).user = undefined; // FastityRequest type definition doesn't allow user to be undefined, even if it can be undefined in practice
            throw new Error('Invalid JWT token');
        }
    }
};
