/*
  Kreuzstich
  Copyright (c) 2013, 2026 Fabien Pollet <polletfa@posteo.de>
  MIT License, see LICENSE file.
*/

import type { FastifyReply } from 'fastify';
import bcrypt from 'bcryptjs';

import { Helpers } from './Helpers';
import type { Server, Database } from './Application';
import { AuthHelper } from './AuthHelper';
import * as api from '@datatypes/api/User';
import * as db from '@datatypes/db';

import getUser from '@sql/getUser.sql';

/**
 * Authentication and user service: login, logout, manage users
 */
export class UserService {
    constructor(private server: Server, private db: Database) {}

    /**
     * Register routes for the service
     */
    public async routes(server: Server) {
        // public
        server.post('/login', { schema: { body: api.PostUserLoginRequestSchema } }, (request, response) => this.login(request.body, response));
        server.get('/logout', (_, response) => this.logout(response));

        // protected
        server.get('/status', { onRequest: AuthHelper.authenticate }, (request) => request.user);
    }

    /**
     * Login.
     * A HTTP-only cookie is created if the user credentials are valid.
     */
    private async login(request: api.PostUserLoginRequest, response: FastifyReply): Promise<api.PostUserLoginResponse> {
        try {
            const user = await this.db.oneOrNone<db.User>(getUser, [request.email]);
            if(user && await bcrypt.compare(request.password, user.password)) {
                const { password, ...tokenPayload} = user;
                const token = await response.jwtSign(tokenPayload, { expiresIn: request.persist ? '30d' : '1d' });
                response.setCookie('access-token', token, {
                    httpOnly: true,
                    secure: true,
                    sameSite: 'strict',
                    path: '/',
                    maxAge: request.persist ? 60*60*24*30 : undefined
                });
                return tokenPayload;
            } else {
                response.code(401).send({ error: 'Unauthorized' });
            }
        } catch(error) {
            this.server.log.error(Helpers.errorToString(error));
            response.code(500).send({ error: Helpers.errorToString(error) });
        }
        return undefined;
    }

    /**
     * Logout and clear cookie.
     */
    private async logout(response: FastifyReply): Promise<api.GetUserLogoutResponse> {
        response.clearCookie('access-token');
        return {success: true};
    }
}
